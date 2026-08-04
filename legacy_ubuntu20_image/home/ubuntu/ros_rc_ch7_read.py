#!/usr/bin/env python3
import rospy
from std_msgs.msg import Bool
from pymavlink import mavutil
import time

MAV_ENDPOINT = "udp:127.0.0.1:14552"
CH_INDEX = 6          # CH7 → index 6 (0-based)
HIGH_THRESH = 1800    # µs

def main():
    rospy.init_node("rc_ch7_enable")

    pub = rospy.Publisher(
        "autonomy_enable",
        Bool,
        queue_size=1
    )

    rospy.loginfo("Connecting to MAVProxy at %s", MAV_ENDPOINT)
    mav = mavutil.mavlink_connection(MAV_ENDPOINT)

    # Wait for heartbeat so we know RC_CHANNELS will come
    mav.wait_heartbeat(timeout=5)
    rospy.loginfo("Heartbeat received")

    rate = rospy.Rate(50)  # RC_CHANNELS ~50 Hz

    last_state = None

    while not rospy.is_shutdown():
        msg = mav.recv_match(type="RC_CHANNELS", blocking=False)

        if msg is not None:
            try:
                ch_val = msg.chan7_raw if hasattr(msg, "chan7_raw") else msg.chan_raw[CH_INDEX]
                enabled = ch_val > HIGH_THRESH

                if enabled != last_state:
                    rospy.loginfo(
                        "Autonomy %s (CH7 = %d)",
                        "ENABLED" if enabled else "DISABLED",
                        ch_val
                    )
                    last_state = enabled

                pub.publish(Bool(enabled))

            except Exception as e:
                rospy.logwarn_throttle(1.0, "RC parse error: %s", e)

        rate.sleep()

if __name__ == "__main__":
    main()