#!/usr/bin/env python3
"""
Scan a comma route segment for candidate BSM source messages.

Goal: with ADAS_DRV disabled, find any (bus, address) on the CAN buses whose
payload changes during the segment in a way consistent with a BSM lamp toggle
(short message, few bits, sustained on/off transitions). Rules out static
config broadcasts and high-entropy data streams (radar tracks, IMU, video sync).

Usage:
    python scripts/bsm_bus_scan.py <segment_range>
    e.g.: python scripts/bsm_bus_scan.py 78511c37de32c375/00000725--1b47baf2f1/54/60

Filters openpilot-spoofed TX (src=128+) from genuine RX.
"""

import sys
from collections import defaultdict

from openpilot.tools.lib.logreader import LogReader

# Address ranges that are definitely not BSM (radar tracks, IMU, etc.) — skip to keep output tight.
BORING_RANGES = [
    (0x3A5, 0x3C4),  # MRR35 radar tracks
    (0x3D0, 0x3D4),  # MRR35 radar extras
]


def is_boring(addr: int) -> bool:
    return any(lo <= addr <= hi for lo, hi in BORING_RANGES)


def scan(route: str):
    print(f"Loading {route} ...")
    lr = LogReader(route)

    # (bus, addr) -> list of (t, payload_bytes)
    samples: dict[tuple[int, int], list[tuple[float, bytes]]] = defaultdict(list)
    first_t = None

    n_can_msgs = 0
    for msg in lr:
        if msg.which() != "can":
            continue
        for c in msg.can:
            # filter spoofed TX (panda src 128+ is openpilot-originated)
            if c.src >= 128:
                continue
            if is_boring(c.address):
                continue
            t = msg.logMonoTime / 1e9
            if first_t is None:
                first_t = t
            samples[(c.src, c.address)].append((t - first_t, bytes(c.dat)))
            n_can_msgs += 1

    print(f"Collected {n_can_msgs} CAN frames across {len(samples)} (bus, addr) pairs")
    print()

    candidates = []
    for (bus, addr), frames in samples.items():
        n = len(frames)
        if n < 5:
            continue

        # message length (use mode-ish via first frame; if they vary, that's its own anomaly)
        msg_len = len(frames[0][1])

        # rate in Hz
        duration = frames[-1][0] - frames[0][0]
        rate = n / duration if duration > 0 else 0

        # find bytes that vary at all
        per_byte_values = [set() for _ in range(msg_len)]
        for _, dat in frames:
            for i in range(msg_len):
                per_byte_values[i].add(dat[i])

        # which bytes vary, and how many distinct values they take
        varying_bytes = [(i, len(vals)) for i, vals in enumerate(per_byte_values) if len(vals) > 1]

        if not varying_bytes:
            continue  # totally static — not BSM

        # we want to ignore bytes that are obviously COUNTER (cycling through ~all 256 values
        # at high rate) or CHECKSUM (varies every frame, high entropy). The rest is the signal.
        signal_bytes = []
        for i, distinct in varying_bytes:
            # COUNTER-like: more than half the distinct possible values across the window
            counter_like = distinct > min(64, n // 4)
            if counter_like:
                continue
            signal_bytes.append((i, distinct))

        if not signal_bytes:
            continue  # everything is counter/checksum-like

        # bit-flip count: how many distinct payload "states" exist if we ignore counter/checksum bytes?
        signal_indices = [i for i, _ in signal_bytes]
        distinct_states = set()
        for _, dat in frames:
            distinct_states.add(tuple(dat[i] for i in signal_indices))

        # We want messages with a small number of distinct states (BSM lamp is on or off
        # or warning-tier 1/2/3 — likely <= 8 states). And the message should be reasonably
        # short and on a normal control bus.
        candidates.append({
            "bus": bus,
            "addr": addr,
            "addr_hex": f"0x{addr:X}",
            "len": msg_len,
            "rate_hz": rate,
            "frames": n,
            "signal_bytes": signal_bytes,
            "distinct_states": len(distinct_states),
            "states_sample": sorted(distinct_states)[:6],
        })

    # rank: prefer low distinct_states (lamp-like), short messages, on bus 0 or 1
    candidates.sort(key=lambda c: (c["distinct_states"], c["len"], c["bus"]))

    print(f"{'bus':<4} {'addr':<8} {'len':<4} {'rate':<7} {'n_frames':<9} {'states':<7} signal_bytes")
    print("-" * 100)
    shown = 0
    for c in candidates:
        if c["distinct_states"] > 16:
            continue  # too many states to look like a lamp
        sb = ",".join(f"b{i}({d})" for i, d in c["signal_bytes"][:6])
        print(f"{c['bus']:<4} {c['addr_hex']:<8} {c['len']:<4} {c['rate_hz']:6.1f}  {c['frames']:<9} {c['distinct_states']:<7} {sb}")
        shown += 1
        if shown >= 50:
            print(f"... (truncated; {len(candidates) - shown} more candidates)")
            break

    print()
    print("Interpretation:")
    print("  - 'states' = distinct payload patterns ignoring counter/checksum-like bytes")
    print("  - A genuine BSM lamp candidate looks like: short msg, low rate (5-50 Hz),")
    print("    2-8 distinct states, 1-3 signal bytes flipping.")
    print("  - On Hyundai LKA-steering Ioniq 6, ECAN=1, PT=0.")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    scan(sys.argv[1])
