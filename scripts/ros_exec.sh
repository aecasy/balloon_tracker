#!/bin/bash
# Helper script to execute ROS commands inside a ROS container.
# It uses a running local roscore container when present, or falls back to a
# temporary casy-ros-node container pointed at the configured remote ROS master.
#
# Usage:
#   ./scripts/ros_exec.sh rostopic echo /target_bearing
#   ./scripts/ros_exec.sh rostopic hz /target_bearing

if [ "$#" -eq 0 ]; then
    echo "Usage: ./scripts/ros_exec.sh <ros_command>"
    echo "Example: ./scripts/ros_exec.sh rostopic echo /target_bearing"
    exit 1
fi

ENV_FILE=${ENV_FILE:-/etc/casy-drone/pi_os_lite.env}
DOCKER_IMAGE=${DOCKER_IMAGE:-casy-ros-node}
DEFAULT_ROS_MASTER_URI=${ROS_MASTER_URI:-http://192.168.1.154:11311}
DEFAULT_ROS_IP=${ROS_IP:-192.168.1.168}

# The container name might be balloon_tracker_roscore_1 or balloon_tracker-roscore-1
# depending on the docker-compose version. We'll try to find the running roscore container.
CONTAINER_NAME=$(docker ps --format '{{.Names}}' 2>/dev/null | grep "roscore" | head -n 1)
if [ -z "$CONTAINER_NAME" ] && command -v sudo >/dev/null 2>&1; then
    CONTAINER_NAME=$(sudo docker ps --format '{{.Names}}' 2>/dev/null | grep "roscore" | head -n 1)
fi

if [ -n "$CONTAINER_NAME" ]; then
    docker exec -it "$CONTAINER_NAME" bash -c "source /opt/ros/noetic/setup.bash && $*" \
        || sudo docker exec -it "$CONTAINER_NAME" bash -c "source /opt/ros/noetic/setup.bash && $*"
    exit $?
fi

if [ -f "$ENV_FILE" ]; then
    docker run --rm -it --network host --env-file "$ENV_FILE" "$DOCKER_IMAGE" \
        bash -c "source /opt/ros/noetic/setup.bash && $*" \
        || sudo docker run --rm -it --network host --env-file "$ENV_FILE" "$DOCKER_IMAGE" \
            bash -c "source /opt/ros/noetic/setup.bash && $*"
else
    docker run --rm -it --network host \
        -e ROS_MASTER_URI="$DEFAULT_ROS_MASTER_URI" \
        -e ROS_IP="$DEFAULT_ROS_IP" \
        "$DOCKER_IMAGE" \
        bash -c "source /opt/ros/noetic/setup.bash && $*" \
        || sudo docker run --rm -it --network host \
            -e ROS_MASTER_URI="$DEFAULT_ROS_MASTER_URI" \
            -e ROS_IP="$DEFAULT_ROS_IP" \
            "$DOCKER_IMAGE" \
            bash -c "source /opt/ros/noetic/setup.bash && $*"
fi
