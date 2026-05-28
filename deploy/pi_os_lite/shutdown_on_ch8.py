#!/usr/bin/env python3
"""Shut down the Pi when RC channel 8 is held high."""

from __future__ import annotations

import os
import subprocess
import time

from pymavlink import mavutil


UDP_PORT = int(os.getenv("MAVLINK_SHUTDOWN_PORT", "14552"))
CH_OFF_THRESH = int(os.getenv("RC_CH8_SHUTDOWN_HIGH", "1900"))
CH_ON_THRESH = int(os.getenv("RC_CH8_RESET_LOW", "1500"))
HOLD_SEC = float(os.getenv("RC_CH8_HOLD_SEC", "1.0"))
SUDO_COMMAND = os.getenv("SHUTDOWN_SUDO", "sudo").split()
SHUTDOWN_COMMAND = os.getenv("SHUTDOWN_COMMAND", "/sbin/shutdown -h now").split()


def get_ch8(msg):
    if msg.get_type() in {"RC_CHANNELS", "RC_CHANNELS_RAW"}:
        return getattr(msg, "chan8_raw", None)
    return None


def main() -> int:
    mav = mavutil.mavlink_connection(f"udpin:127.0.0.1:{UDP_PORT}", autoreconnect=True)

    last_low = True
    high_since = None

    while True:
        msg = mav.recv_match(type=["RC_CHANNELS", "RC_CHANNELS_RAW"], blocking=True, timeout=2.0)
        if msg is None:
            continue

        ch8 = get_ch8(msg)
        if ch8 is None:
            continue

        is_high = ch8 >= CH_OFF_THRESH
        is_low = ch8 <= CH_ON_THRESH

        if is_low:
            last_low = True
            high_since = None
            continue

        if is_high and last_low:
            if high_since is None:
                high_since = time.monotonic()

            if time.monotonic() - high_since >= HOLD_SEC:
                subprocess.run([*SUDO_COMMAND, *SHUTDOWN_COMMAND], check=False)
                return 0

        if not is_high:
            high_since = None


if __name__ == "__main__":
    raise SystemExit(main())
