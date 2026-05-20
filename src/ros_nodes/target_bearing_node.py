#!/usr/bin/env python3
import sys
import json
import rospy
from geometry_msgs.msg import PointStamped

def main():
    rospy.init_node('target_bearing_publisher', anonymous=True)
    pub = rospy.Publisher('/target_bearing', PointStamped, queue_size=10)
    rate = rospy.Rate(30) # 30hz, but we publish as fast as stdin provides
    
    rospy.loginfo("Target Bearing Node started. Waiting for JSON input on stdin...")

    for line in sys.stdin:
        if rospy.is_shutdown():
            break
            
        line = line.strip()
        if not line:
            continue
            
        try:
            data = json.loads(line)
            
            # Create the message
            msg = PointStamped()
            msg.header.stamp = rospy.Time.now()
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
            
        except json.JSONDecodeError:
            rospy.logwarn(f"Failed to parse JSON: {line}")
        except Exception as e:
            rospy.logerr(f"Error processing input: {e}")

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
