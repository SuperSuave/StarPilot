#!/usr/bin/env python3
"""
Detailed view of a single (bus, addr) message across a route segment.

Shows every transition: timestamp + payload bytes. Lets you eyeball which
message's state changes line up with a known BSM event (e.g., a car passing
on your left at a known time in the route).

Usage:
    python scripts/bsm_bus_detail.py <segment_range> <bus> <addr_hex>
    e.g.: python scripts/bsm_bus_detail.py 78511c37de32c375/00000725--1b47baf2f1/0 1 0x36A
"""

import os
import sys
from collections import defaultdict

from openpilot.tools.lib.logreader import LogReader


def resolve_source(arg: str) -> str:
    if os.path.isdir(arg):
        for name in ("rlog.zst", "rlog.bz2", "rlog"):
            p = os.path.join(arg, name)
            if os.path.isfile(p):
                return p
        raise FileNotFoundError(f"No rlog.* found in directory {arg}")
    return arg


def main(route: str, target_bus: int, target_addr: int):
    src = resolve_source(route)
    print(f"Loading {src} ...")
    lr = LogReader(src)

    samples = []  # (t, payload)
    first_t = None

    for msg in lr:
        if msg.which() != "can":
            continue
        for c in msg.can:
            if c.src != target_bus or c.address != target_addr:
                continue
            t = msg.logMonoTime / 1e9
            if first_t is None:
                first_t = t
            samples.append((t - first_t, bytes(c.dat)))

    if not samples:
        print(f"No frames for bus={target_bus} addr=0x{target_addr:X}")
        return

    msg_len = len(samples[0][1])
    print(f"Got {len(samples)} frames over {samples[-1][0]:.1f}s "
          f"(rate {len(samples)/samples[-1][0]:.1f} Hz, len {msg_len} bytes)")
    print()

    # Find bytes that vary, ignoring obvious counter/checksum byes.
    per_byte = [set() for _ in range(msg_len)]
    for _, dat in samples:
        for i in range(msg_len):
            per_byte[i].add(dat[i])

    # Print only transitions on signal bytes (small set of distinct values)
    signal_bytes = [i for i in range(msg_len) if 1 < len(per_byte[i]) < 16]
    print(f"Signal byte positions (distinct values < 16): {signal_bytes}")
    for i in signal_bytes:
        vals = sorted(per_byte[i])
        print(f"  byte {i}: values seen = {vals}")
    print()

    # Walk samples and print transitions on signal bytes
    last_state = None
    print(f"{'t(s)':>8}  {'payload (signal bytes only)':<30}  full payload")
    print("-" * 100)
    for t, dat in samples:
        state = tuple(dat[i] for i in signal_bytes)
        if state != last_state:
            sig = " ".join(f"b{i}={dat[i]:02x}" for i in signal_bytes)
            full = dat.hex()
            print(f"{t:8.2f}  {sig:<30}  {full}")
            last_state = state


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print(__doc__)
        sys.exit(1)
    main(sys.argv[1], int(sys.argv[2]), int(sys.argv[3], 16))
