#!/usr/bin/env bash
set -euo pipefail

ENV_FILE="${ENV_FILE:-/etc/casy-drone/pi_os_lite.env}"
if [ -f "$ENV_FILE" ]; then
  set -a
  # shellcheck disable=SC1090
  . "$ENV_FILE"
  set +a
fi

PROJECT_DIR="${PROJECT_DIR:-/home/casy/balloon_tracker}"
DOCKER_BIN="${DOCKER_BIN:-docker}"
DOCKER_IMAGE="${DOCKER_IMAGE:-casy-ros-node}"
ROS_MASTER_URI="${ROS_MASTER_URI:-http://192.168.1.154:11311}"
ROS_IP="${ROS_IP:-192.168.1.168}"

cd "$PROJECT_DIR"

python3 scripts/green_tracker.py \
  --config "${TRACKER_CONFIG:-config/green_tracker.json}" \
  --width "${TRACKER_WIDTH:-1280}" \
  --height "${TRACKER_HEIGHT:-720}" \
  --raw-width "${TRACKER_RAW_WIDTH:-2304}" \
  --raw-height "${TRACKER_RAW_HEIGHT:-1296}" \
  --output json \
  --headless \
  --calibration "${TRACKER_CALIBRATION:-config/camera_calibration_1280x720_raw2304x1296.json}" \
  | "$DOCKER_BIN" run -i --rm --network host \
      -e ROS_MASTER_URI="$ROS_MASTER_URI" \
      -e ROS_IP="$ROS_IP" \
      -e PYTHONUNBUFFERED=1 \
      "$DOCKER_IMAGE" \
      python3 /app/src/ros_nodes/target_bearing_node.py
