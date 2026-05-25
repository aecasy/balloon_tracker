#!/usr/bin/env python3
import time
from pymavlink import mavutil

PORT = "/dev/ttyAMA0"
BAUD = 115200
TARGET_SYS  = 1
TARGET_COMP = 1

mav = mavutil.mavlink_connection(
    PORT,
    baud=BAUD,
    source_system=255,
    dialect="ardupilotmega",
)

# Optional: try to force MAVLink2 framing (harmless if ignored)
try:
    mav.mav.set_proto_version(2)
except Exception:
    try:
        mav.mavlink20 = True
    except Exception:
        pass

print("[INFO] Sending RC override: CH1(roll)=1600 @ 20Hz (others ignored)")

while True:
    mav.mav.rc_channels_override_send(
        TARGET_SYS,
        TARGET_COMP,
        1600,  # ch1 roll
        0,     # ch2 pitch ignore
        0,     # ch3 throttle ignore
        0,     # ch4 yaw ignore
        0,     # ch5 ignore
        0,     # ch6 ignore
        0,     # ch7 ignore
        0      # ch8 ignore
    )
    print("Sending")
    time.sleep(0.05)