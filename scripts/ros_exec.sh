#!/bin/bash
# Helper script to execute ROS commands inside the roscore container.
# It automatically loads the ROS setup script before executing your command.
#
# Usage:
#   ./scripts/ros_exec.sh rostopic echo /target_bearing
#   ./scripts/ros_exec.sh rostopic hz /target_bearing

if [ "$#" -eq 0 ]; then
    echo "Usage: ./scripts/ros_exec.sh <ros_command>"
    echo "Example: ./scripts/ros_exec.sh rostopic echo /target_bearing"
    exit 1
fi

# The container name might be balloon_tracker_roscore_1 or balloon_tracker-roscore-1
# depending on the docker-compose version. We'll try to find the running roscore container.
CONTAINER_NAME=$(sudo docker ps --format '{{.Names}}' | grep "roscore" | head -n 1)

if [ -z "$CONTAINER_NAME" ]; then
    echo "Error: Could not find a running roscore container. Is docker compose up -d running?"
    exit 1
fi

# We use sudo here because many users will have Docker running as root. 
# If their user is in the docker group, sudo will just prompt for password or run normally.
sudo docker exec -it "$CONTAINER_NAME" bash -c "source /opt/ros/noetic/setup.bash && $*"
