#!/usr/bin/env python3
"""Publish the RC channel 7 autonomy-enable switch as a ROS Bool."""

from __future__ import annotations

import os


MAV_ENDPOINT = os.getenv(
    "MAVLINK_RC_CH7_ENDPOINT",
    os.getenv("MAVLINK_RC_ENDPOINT", "udp:127.0.0.1:14551"),
)
TOPIC_NAME = os.getenv("AUTONOMY_ENABLE_TOPIC", "autonomy_enable")
RATE_HZ = float(os.getenv("RC_CH7_RATE_HZ", "50.0"))
HIGH_THRESH = int(os.getenv("RC_CH7_HIGH_THRESH", "1800"))


def rc_ch7_value(msg):
    if hasattr(msg, "chan7_raw"):
        return msg.chan7_raw
    if hasattr(msg, "chan_raw") and len(msg.chan_raw) >= 7:
        return msg.chan_raw[6]
    return None


def main() -> int:
    import rospy
    from pymavlink import mavutil
    from std_msgs.msg import Bool

    rospy.init_node("rc_ch7_enable", anonymous=False)
    pub = rospy.Publisher(TOPIC_NAME, Bool, queue_size=1)

    rospy.loginfo("Connecting to MAVProxy at %s", MAV_ENDPOINT)
    mav = mavutil.mavlink_connection(MAV_ENDPOINT, autoreconnect=True)
    mav.wait_heartbeat(timeout=5)
    rospy.loginfo("Heartbeat received")

    rate = rospy.Rate(RATE_HZ)
    last_state = None

    while not rospy.is_shutdown():
        msg = mav.recv_match(type="RC_CHANNELS", blocking=False)
        if msg is not None:
            ch_val = rc_ch7_value(msg)
            if ch_val is not None:
                enabled = ch_val > HIGH_THRESH
                if enabled != last_state:
                    rospy.loginfo(
                        "Autonomy %s (CH7 = %d)",
                        "ENABLED" if enabled else "DISABLED",
                        ch_val,
                    )
                    last_state = enabled
                pub.publish(Bool(enabled))
        rate.sleep()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
