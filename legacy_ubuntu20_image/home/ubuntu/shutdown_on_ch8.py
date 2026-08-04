#!/usr/bin/env python3
import time
import subprocess
from pymavlink import mavutil

# CH8 values (your numbers)
CH_OFF_THRESH = 1900   # switch high -> shutdown request (e.g. 2006)
CH_ON_THRESH  = 1500   # below this counts as "not requesting shutdown"
HOLD_SEC      = 1.0    # must be held high for this long to avoid accidental bumps

UDP_PORT = 14552       # must match the extra --out port in MAVProxy

def get_ch8(msg):
    # Prefer RC_CHANNELS (has chan8_raw on ArduPilot)
    if msg.get_type() == "RC_CHANNELS":
        return getattr(msg, "chan8_raw", None)

    # Some setups emit RC_CHANNELS_RAW instead
    if msg.get_type() == "RC_CHANNELS_RAW":
        return getattr(msg, "chan8_raw", None)

    return None

def main():
    # Listen for MAVProxy's local UDP stream
    m = mavutil.mavlink_connection(f"udpin:127.0.0.1:{UDP_PORT}", autoreconnect=True)

    last_low = True
    high_since = None

    while True:
        msg = m.recv_match(type=["RC_CHANNELS", "RC_CHANNELS_RAW"], blocking=True, timeout=2.0)
        if msg is None:
            continue

        ch8 = get_ch8(msg)
        if ch8 is None:
            continue

        is_high = (ch8 >= CH_OFF_THRESH)
        is_low  = (ch8 <= CH_ON_THRESH)

        # Arm the edge detector when we see low
        if is_low:
            last_low = True
            high_since = None
            continue

        # Only start timing after a clean low -> high transition
        if is_high and last_low:
            if high_since is None:
                high_since = time.monotonic()

            if (time.monotonic() - high_since) >= HOLD_SEC:
                # Trigger once
                subprocess.run(["sudo", "/sbin/shutdown", "-h", "now"], check=False)
                return

        # If it's in-between, don't trigger; require clean low->high and hold
        if not is_high:
            high_since = None

if __name__ == "__main__":
    main()