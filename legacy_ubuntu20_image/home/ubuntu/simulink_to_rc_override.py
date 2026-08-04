#!/usr/bin/env python3

import time
import rospy
from std_msgs.msg import UInt16MultiArray
from pymavlink import mavutil

# =========================
# USER CONFIG
# =========================
ROS_TOPIC = "/guidance/rc"
UART_DEV  = "/dev/ttyAMA0"
BAUDRATE  = 921600
SEND_HZ   = 50           # RC override rate
TIMEOUT  = 0.25          # seconds before failsafe
SAFE_RC  = [1600, 0, 0, 0]  # roll, pitch, throttle, yaw
# =========================


class RcOverrideNode:
    def __init__(self):
        self.last_cmd = None
        self.last_rx_time = 0.0

        rospy.init_node("simulink_to_rc_override", anonymous=False)

        # --- MAVLink connection ---
        rospy.loginfo("Connecting to FC on %s @ %d baud", UART_DEV, BAUDRATE)
        self.master = mavutil.mavlink_connection(UART_DEV, baud=BAUDRATE)

        rospy.loginfo("Waiting for MAVLink heartbeat...")
        hb = self.master.wait_heartbeat(timeout=5)

        if hb is None:
            raise RuntimeError(
                "No MAVLink heartbeat received on /dev/ttyAMA0. "
                "If no FC is connected, this is expected. "
                "If FC is connected: check wiring (TX↔RX, GND), FC SERIALx_PROTOCOL, and BAUD."
            )

        # Extra validation (optional)
        if hb.autopilot == mavutil.mavlink.MAV_AUTOPILOT_INVALID:
            raise RuntimeError("Heartbeat received but autopilot is INVALID (likely echo/noise).")

        rospy.loginfo(
            "MAVLink heartbeat OK: sysid=%d compid=%d autopilot=%d type=%d mavlink_version=%d",
            self.master.target_system, self.master.target_component,
            hb.autopilot, hb.type, hb.mavlink_version
        )

        # --- ROS subscriber ---
        rospy.Subscriber(
            ROS_TOPIC,
            UInt16MultiArray,
            self.ros_callback,
            queue_size=1
        )

        self.rate = rospy.Rate(SEND_HZ)

    # -------------------------
    def ros_callback(self, msg: UInt16MultiArray):
        """
        Store the latest RC vector from Simulink
        """
        try:
            # Preferred: Simulink sets current_length
            n = msg.data_sl_info.current_length
        except Exception:
            # Fallback if SL info not present
            n = len(msg.data)

        self.last_cmd = list(msg.data[:n])
        self.last_rx_time = time.time()

    # -------------------------
    def send_override(self, channels):
        """
        Send MAVLink RC_OVERRIDE (8 channels max).
        Use 0 to ignore a channel.
        """
        # Ensure exactly 8 channels
        rc = list(channels[:8]) + [0] * (8 - len(channels))
    
        self.master.mav.rc_channels_override_send(
            self.master.target_system,
            self.master.target_component,
            rc[0], rc[1], rc[2], rc[3],
            rc[4], rc[5], rc[6], rc[7]
        )
    

    # -------------------------
    def run(self):
        rospy.loginfo("RC override node running")

        while not rospy.is_shutdown():
            now = time.time()

            if (
                self.last_cmd is None
                or (now - self.last_rx_time) > TIMEOUT
            ):
                # FAILSAFE
                self.send_override(SAFE_RC)
            else:
                self.send_override(self.last_cmd)

            self.rate.sleep()


# =========================
if __name__ == "__main__":
    try:
        node = RcOverrideNode()
        node.run()
    except rospy.ROSInterruptException:
        pass
