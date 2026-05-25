#!/usr/bin/env python3
import time
import threading

import rospy
from std_msgs.msg import UInt16MultiArray
from pymavlink import mavutil

# ---------------- Config ----------------
TOPIC_NAME = "quad_commands"
MAV_ENDPOINT = "udp:127.0.0.1:14552"

RATE_HZ = 50.0

DATA_OFFSET = 0   # msg.data[0..]

PWM_MIN = 1000
PWM_MAX = 2000

IGNORE = 65535    # MAVLink-defined ignore value
# ----------------------------------------

lock = threading.Lock()

# roll, pitch, thr/climb, yaw, ch6
cmd_pwm = [IGNORE, IGNORE, IGNORE, IGNORE, IGNORE]


def clamp_pwm(x: int) -> int:
    if x < PWM_MIN:
        return PWM_MIN
    if x > PWM_MAX:
        return PWM_MAX
    return x


def sanitize_pwm(v: int) -> int:
    # Simulink uses 0 to mean "no command" -> don't override
    if v == 0:
        return IGNORE
    if v == IGNORE:
        return IGNORE
    return clamp_pwm(v)


def on_cmd(msg: UInt16MultiArray):
    global cmd_pwm

    if msg.data is None:
        return

    # Need at least up to CH6 -> index 5
    if len(msg.data) < DATA_OFFSET + 6:
        return

    raw = [
        int(msg.data[DATA_OFFSET + 0]),  # CH1 roll
        int(msg.data[DATA_OFFSET + 1]),  # CH2 pitch
        int(msg.data[DATA_OFFSET + 2]),  # CH3 thr/climb
        int(msg.data[DATA_OFFSET + 3]),  # CH4 yaw
        int(msg.data[DATA_OFFSET + 5]),  # CH6 flight mode
    ]

    vals = [sanitize_pwm(v) for v in raw]

    with lock:
        cmd_pwm = vals


def main():
    rospy.init_node("ros_rc_bridge", anonymous=False)
    rospy.Subscriber(TOPIC_NAME, UInt16MultiArray, on_cmd, queue_size=1)

    rospy.loginfo("Connecting to MAVProxy at %s", MAV_ENDPOINT)
    mav = mavutil.mavlink_connection(MAV_ENDPOINT, autoreconnect=True)

    rospy.loginfo("Waiting for heartbeat...")
    mav.wait_heartbeat()
    rospy.loginfo(
        "Heartbeat from sys=%u comp=%u",
        mav.target_system,
        mav.target_component,
    )

    period = 1.0 / RATE_HZ
    next_t = time.time()

    while not rospy.is_shutdown():
        with lock:
            r, p, t, y, ch6 = cmd_pwm

        mav.mav.rc_channels_override_send(
            mav.target_system,
            mav.target_component,
            r, p, t, y,
            IGNORE,   # CH5 (ignored)
            ch6,      # CH6 flight mode (from Simulink)
            IGNORE,   # CH7
            IGNORE    # CH8
        )

        next_t += period
        sleep_s = next_t - time.time()
        if sleep_s > 0:
            time.sleep(sleep_s)
        else:
            next_t = time.time()


if __name__ == "__main__":
    try:
        main()
    except Exception:
        import traceback
        traceback.print_exc()
        raise