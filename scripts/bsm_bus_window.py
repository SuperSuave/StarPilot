#!/usr/bin/env python3
"""
Find every (bus, addr) whose state changes within a target time window.

This is the killer scan: given a known BSM event between t=54s and t=60s in a
segment, find every CAN message whose payload changed during that window in a
way it didn't change outside the window. That's the signal we're hunting.

Usage:
    python scripts/bsm_bus_window.py <segment_range> <t_start> <t_end>
    e.g.: python scripts/bsm_bus_window.py 78511c37de32c375/00000725--1b47baf2f1/0 54 60
"""

import os
import sys
from collections import defaultdict

from openpilot.tools.lib.logreader import LogReader

BORING_RANGES = [
    (0x3A5, 0x3C4),  # MRR35 radar tracks
    (0x3D0, 0x3D4),  # MRR35 radar extras
]


def is_boring(addr: int) -> bool:
    return any(lo <= addr <= hi for lo, hi in BORING_RANGES)


def resolve_source(arg: str) -> str:
    if os.path.isdir(arg):
        for name in ("rlog.zst", "rlog.bz2", "rlog"):
            p = os.path.join(arg, name)
            if os.path.isfile(p):
                return p
        raise FileNotFoundError(f"No rlog.* found in directory {arg}")
    return arg


def main(route: str, t_start: float, t_end: float):
    src = resolve_source(route)
    print(f"Loading {src} ...")
    print(f"Looking for messages whose state changes inside [{t_start}s, {t_end}s] "
          f"but not outside.")
    print()
    lr = LogReader(src)

    # (bus, addr) -> list of (t, payload)
    samples: dict[tuple[int, int], list[tuple[float, bytes]]] = defaultdict(list)
    first_t = None

    for msg in lr:
        if msg.which() != "can":
            continue
        for c in msg.can:
            if c.src >= 128:
                continue
            if is_boring(c.address):
                continue
            t = msg.logMonoTime / 1e9
            if first_t is None:
                first_t = t
            samples[(c.src, c.address)].append((t - first_t, bytes(c.dat)))

    print(f"Collected {sum(len(v) for v in samples.values())} frames across "
          f"{len(samples)} (bus, addr) pairs")
    print()

    # For each (bus, addr), find signal bytes (varying, not counter/checksum)
    # and check whether state transitions happen inside vs outside the window.
    candidates = []
    for (bus, addr), frames in samples.items():
        if len(frames) < 10:
            continue
        msg_len = len(frames[0][1])

        per_byte = [set() for _ in range(msg_len)]
        for _, dat in frames:
            for i in range(msg_len):
                per_byte[i].add(dat[i])

        # Filter to signal bytes: vary, but not too much (rules out counter/checksum)
        signal_idx = [i for i in range(msg_len) if 1 < len(per_byte[i]) < 16]
        if not signal_idx:
            continue

        # Look at unique states on signal bytes seen INSIDE vs OUTSIDE the window
        inside = set()
        outside = set()
        # Also find the transitions IN the window for reporting
        in_window_transitions = []
        last_state = None
        for t, dat in frames:
            state = tuple(dat[i] for i in signal_idx)
            in_win = t_start <= t <= t_end
            if in_win:
                inside.add(state)
            else:
                outside.add(state)
            if state != last_state:
                if in_win:
                    in_window_transitions.append((t, state, dat))
                last_state = state

        # Interesting if: states are seen inside that aren't seen outside,
        # OR transitions happen during the window
        unique_inside = inside - outside
        if unique_inside or in_window_transitions:
            candidates.append({
                "bus": bus,
                "addr": addr,
                "len": msg_len,
                "signal_idx": signal_idx,
                "inside_states": inside,
                "outside_states": outside,
                "unique_inside": unique_inside,
                "in_window_transitions": in_window_transitions,
            })

    # Sort: prefer signals that look most BSM-like
    # - has states unique to the window (perfect lamp behavior)
    # - few signal bytes
    # - transition count is small (a lamp goes on a few times, not constantly)
    candidates.sort(key=lambda c: (
        -len(c["unique_inside"]),
        len(c["signal_idx"]),
        len(c["in_window_transitions"]),
    ))

    for c in candidates[:30]:
        sig = ",".join(f"b{i}" for i in c["signal_idx"])
        print(f"bus={c['bus']} addr=0x{c['addr']:X} len={c['len']}  signal_bytes=[{sig}]")
        print(f"  inside states ({len(c['inside_states'])}): "
              f"{sorted(c['inside_states'])[:4]}")
        print(f"  outside states ({len(c['outside_states'])}): "
              f"{sorted(c['outside_states'])[:4]}")
        if c["unique_inside"]:
            print(f"  *** {len(c['unique_inside'])} state(s) ONLY seen during window: "
                  f"{sorted(c['unique_inside'])[:4]}")
        if c["in_window_transitions"]:
            print(f"  transitions during window ({len(c['in_window_transitions'])}):")
            for t, state, dat in c["in_window_transitions"][:6]:
                print(f"    t={t:.2f}s state={state} hex={dat.hex()}")
        print()


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print(__doc__)
        sys.exit(1)
    main(sys.argv[1], float(sys.argv[2]), float(sys.argv[3]))
