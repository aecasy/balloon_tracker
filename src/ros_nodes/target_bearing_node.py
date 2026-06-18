#!/usr/bin/env python3
import json
import os
import sys
import rospy
from geometry_msgs.msg import PointStamped
from std_msgs.msg import String

try:
    from ros_nodes.latency_diagnostics import (
        build_latency_payload,
        format_latency_payload,
        is_enabled,
    )
except ImportError:
    from latency_diagnostics import (
        build_latency_payload,
        format_latency_payload,
        is_enabled,
    )

def main():
    rospy.init_node('target_bearing_publisher', anonymous=True)
    pub = rospy.Publisher('/target_bearing', PointStamped, queue_size=10)
    latency_pub = None
    if is_enabled(os.getenv("LATENCY_DIAGNOSTICS")):
        latency_topic = os.getenv("TARGET_LATENCY_TOPIC", "/target_latency")
        latency_pub = rospy.Publisher(latency_topic, String, queue_size=10)
        rospy.loginfo("Latency diagnostics enabled on %s", latency_topic)

    sequence = 0
    rospy.loginfo("Target Bearing Node started. Waiting for JSON input on stdin...")

    for line in sys.stdin:
        if rospy.is_shutdown():
            break
            
        line = line.strip()
        if not line:
            continue
            
        try:
            docker_receive_time = rospy.Time.now().to_sec()
            data = json.loads(line)
            
            # Create the message
            msg = PointStamped()
            publish_time = rospy.Time.now()
            msg.header.stamp = publish_time
            msg.header.frame_id = "camera_optical_frame"
            
            detected = data.get("detected", False)
            yaw = data.get("yaw_deg", None)
            pitch = data.get("pitch_deg", None)
            
            if detected and yaw is not None and pitch is not None:
                # We use x for yaw, y for pitch, z for detection state (1.0 = detected)
                msg.point.x = float(yaw)
                msg.point.y = float(pitch)
                msg.point.z = 1.0
            else:
                # Not detected or uncalibrated
                msg.point.x = 0.0
                msg.point.y = 0.0
                msg.point.z = 0.0
                
            pub.publish(msg)

            if latency_pub is not None:
                payload = build_latency_payload(
                    data,
                    sequence=sequence,
                    docker_receive_time=docker_receive_time,
                    ros_publish_time=publish_time.to_sec(),
                )
                latency_pub.publish(String(data=format_latency_payload(payload)))
            sequence += 1
            
        except json.JSONDecodeError:
            rospy.logwarn(f"Failed to parse JSON: {line}")
        except Exception as e:
            rospy.logerr(f"Error processing input: {e}")

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
