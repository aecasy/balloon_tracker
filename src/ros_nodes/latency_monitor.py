#!/usr/bin/env python3
import json
import os

import rospy
from std_msgs.msg import String

try:
    from ros_nodes.latency_diagnostics import RollingLatencyStats
except ImportError:
    from latency_diagnostics import RollingLatencyStats


FIELDS = (
    "tracker_to_docker_ms",
    "docker_to_publish_ms",
    "tracker_to_publish_ms",
)


def format_summary(name, summary):
    if summary is None:
        return f"{name}: n/a"
    return (
        f"{name}: n={summary['count']} "
        f"avg={summary['avg']:.2f}ms "
        f"p95={summary['p95']:.2f}ms "
        f"min={summary['min']:.2f}ms "
        f"max={summary['max']:.2f}ms"
    )


def main():
    rospy.init_node("target_latency_monitor", anonymous=False)
    topic = os.getenv("TARGET_LATENCY_TOPIC", "/target_latency")
    window_size = int(os.getenv("LATENCY_WINDOW_SIZE", "200"))
    print_every = max(1, int(os.getenv("LATENCY_PRINT_EVERY", "30")))
    stats = RollingLatencyStats(window_size=window_size)
    count = 0

    def on_latency(msg):
        nonlocal count
        try:
            payload = json.loads(msg.data)
        except json.JSONDecodeError:
            rospy.logwarn("Invalid latency payload: %s", msg.data)
            return

        stats.add(payload)
        count += 1
        if count % print_every != 0:
            return

        parts = [format_summary(field, stats.summary(field)) for field in FIELDS]
        rospy.loginfo(" | ".join(parts))

    rospy.Subscriber(topic, String, on_latency, queue_size=50)
    rospy.loginfo(
        "Monitoring %s with window=%d print_every=%d",
        topic,
        window_size,
        print_every,
    )
    rospy.spin()


if __name__ == "__main__":
    main()
