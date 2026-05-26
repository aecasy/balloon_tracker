#!/usr/bin/env python3
"""Bridge Simulink ROS RC commands to MAVLink RC override messages."""

from __future__ import annotations

import os
import threading
import time
from typing import Iterable


TOPIC_NAME = os.getenv("RC_OVERRIDE_TOPIC", "quad_commands")
MAV_ENDPOINT = os.getenv("MAVLINK_RC_ENDPOINT", "udp:127.0.0.1:14552")
RATE_HZ = float(os.getenv("RC_OVERRIDE_RATE_HZ", "50.0"))

PWM_MIN = 1000
PWM_MAX = 2000
IGNORE = 65535


def clamp_pwm(value: int) -> int:
    return max(PWM_MIN, min(PWM_MAX, value))


def sanitize_pwm(value: int) -> int:
    if value == 0 or value == IGNORE:
        return IGNORE
    return clamp_pwm(value)


def map_quad_commands(values: Iterable[int]) -> list[int] | None:
    data = list(values)
    if len(data) < 6:
        return None
    return [
        sanitize_pwm(int(data[0])),  # CH1 roll
        sanitize_pwm(int(data[1])),  # CH2 pitch
        sanitize_pwm(int(data[2])),  # CH3 throttle/climb
        sanitize_pwm(int(data[3])),  # CH4 yaw
        sanitize_pwm(int(data[5])),  # CH6 flight mode
    ]


class RcOverrideBridge:
    def __init__(self):
        import rospy
        from pymavlink import mavutil
        from std_msgs.msg import UInt16MultiArray

        self.rospy = rospy
        self.UInt16MultiArray = UInt16MultiArray
        self.lock = threading.Lock()
        self.cmd_pwm = [IGNORE, IGNORE, IGNORE, IGNORE, IGNORE]

        rospy.init_node("ros_rc_bridge", anonymous=False)
        rospy.Subscriber(TOPIC_NAME, UInt16MultiArray, self.on_cmd, queue_size=1)

        rospy.loginfo("Connecting to MAVProxy at %s", MAV_ENDPOINT)
        self.mav = mavutil.mavlink_connection(MAV_ENDPOINT, autoreconnect=True)

        rospy.loginfo("Waiting for heartbeat...")
        self.mav.wait_heartbeat()
        rospy.loginfo(
            "Heartbeat from sys=%u comp=%u",
            self.mav.target_system,
            self.mav.target_component,
        )

    def on_cmd(self, msg):
        mapped = map_quad_commands(msg.data or [])
        if mapped is None:
            return
        with self.lock:
            self.cmd_pwm = mapped

    def run(self):
        period = 1.0 / RATE_HZ
        next_t = time.time()

        while not self.rospy.is_shutdown():
            with self.lock:
                roll, pitch, throttle, yaw, ch6 = self.cmd_pwm

            self.mav.mav.rc_channels_override_send(
                self.mav.target_system,
                self.mav.target_component,
                roll,
                pitch,
                throttle,
                yaw,
                IGNORE,
                ch6,
                IGNORE,
                IGNORE,
            )

            next_t += period
            sleep_s = next_t - time.time()
            if sleep_s > 0:
                time.sleep(sleep_s)
            else:
                next_t = time.time()


def main() -> int:
    bridge = RcOverrideBridge()
    bridge.run()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
