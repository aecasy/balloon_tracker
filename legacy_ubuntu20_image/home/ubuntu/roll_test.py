from pymavlink import mavutil
import time

# Connect to MAVProxy local UDP output
mav = mavutil.mavlink_connection('udp:127.0.0.1:14551')

# Wait for heartbeat
mav.wait_heartbeat()
print("Heartbeat received")
IGNORE = 65535

while True:
    mav.mav.rc_channels_override_send(
        mav.target_system,
        mav.target_component,
        1600,      # CH1: Roll
        IGNORE,         # CH2: ignore
        IGNORE,         # CH3: ignore
        IGNORE,         # CH4: ignore
        IGNORE, IGNORE, IGNORE, IGNORE
    )
    time.sleep(0.02)  # 50 Hz
