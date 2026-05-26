#!/usr/bin/env bash
set -euo pipefail

ENV_FILE="${ENV_FILE:-/etc/casy-drone/pi_os_lite.env}"
if [ -f "$ENV_FILE" ]; then
  set -a
  # shellcheck disable=SC1090
  . "$ENV_FILE"
  set +a
fi

ROS_MASTER_URI="${ROS_MASTER_URI:-http://192.168.1.154:11311}"
ROS_MASTER_HOST="${ROS_MASTER_URI#http://}"
ROS_MASTER_HOST="${ROS_MASTER_HOST%%:*}"
FC_UART="${FC_UART:-/dev/serial0}"

echo "Checking camera command..."
command -v rpicam-hello

echo "Checking Picamera2 import..."
python3 -c 'from picamera2 import Picamera2; print("picamera2 ok")'

echo "Checking serial device..."
test -e "$FC_UART"
ls -l "$FC_UART"

echo "Checking Docker access..."
docker version >/dev/null

echo "Checking ROS master port ${ROS_MASTER_HOST}:11311..."
timeout 3 bash -c "</dev/tcp/${ROS_MASTER_HOST}/11311"

echo "Preflight checks passed."
