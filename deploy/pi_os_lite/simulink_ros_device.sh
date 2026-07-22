#!/usr/bin/env bash
set -euo pipefail

COMMAND="${1:-}"
PROJECT_DIR="${PROJECT_DIR:-/home/casy/balloon_tracker}"
ENV_FILE="${ENV_FILE:-/etc/casy-drone/pi_os_lite.env}"
PASSWORD_FILE="${SIMULINK_ROS_DEVICE_PASSWORD_FILE:-/etc/casy-drone/simulink_ros_device_password}"
HOST_WORKSPACE="${SIMULINK_CATKIN_HOST_DIR:-/home/casy/simulink_catkin_ws}"
SSH_PORT="${SIMULINK_ROS_DEVICE_SSH_PORT:-22}"
SERVICE="simulink-ros-device"

usage() {
    cat <<EOF
Usage: deploy/pi_os_lite/simulink_ros_device.sh <command>

Commands:
  init-password  Create or replace the local ubuntu SSH password file
  build          Build the Simulink ROS-device Docker image
  start          Start the Simulink ROS-device container
  stop           Stop the Simulink ROS-device container
  restart        Restart the Simulink ROS-device container
  status         Show container status
  logs           Follow container logs
  check          Verify ROS and catkin inside the running container

Environment:
  PROJECT_DIR=${PROJECT_DIR}
  ENV_FILE=${ENV_FILE}
  SIMULINK_ROS_DEVICE_PASSWORD_FILE=${PASSWORD_FILE}
  SIMULINK_CATKIN_HOST_DIR=${HOST_WORKSPACE}
  SIMULINK_ROS_DEVICE_SSH_PORT=${SSH_PORT}
EOF
}

require_command() {
    if [ -z "$COMMAND" ]; then
        usage
        exit 2
    fi
}

compose() {
    cd "$PROJECT_DIR"
    export SIMULINK_ROS_DEVICE_PASSWORD_FILE="$PASSWORD_FILE"
    export SIMULINK_CATKIN_HOST_DIR="$HOST_WORKSPACE"
    export SIMULINK_ROS_DEVICE_SSH_PORT="$SSH_PORT"
    docker compose --env-file "$ENV_FILE" --profile simulink "$@"
}

ensure_password_file() {
    if [ ! -s "$PASSWORD_FILE" ]; then
        echo "Missing password file: $PASSWORD_FILE" >&2
        echo "Run: deploy/pi_os_lite/simulink_ros_device.sh init-password" >&2
        exit 64
    fi
}

init_password() {
    printf "New password for Simulink container user ubuntu: "
    stty -echo
    read -r password
    stty echo
    printf "\n"

    if [ -z "$password" ]; then
        echo "Password must not be empty" >&2
        exit 64
    fi

    tmp_file="$(mktemp)"
    chmod 600 "$tmp_file"
    printf "%s\n" "$password" > "$tmp_file"
    sudo install -m 600 -o root -g root "$tmp_file" "$PASSWORD_FILE"
    rm -f "$tmp_file"
    echo "Wrote password file: $PASSWORD_FILE"
}

check_container() {
    compose exec -T "$SERVICE" bash -lc \
        "source /opt/ros/noetic/setup.bash && rosversion -d && su - ubuntu -c 'source /opt/ros/noetic/setup.bash && mkdir -p ~/catkin_ws/src && cd ~/catkin_ws && catkin_make'"
}

require_command

case "$COMMAND" in
    init-password)
        init_password
        ;;
    build)
        mkdir -p "$HOST_WORKSPACE"
        compose build "$SERVICE"
        ;;
    start)
        ensure_password_file
        mkdir -p "$HOST_WORKSPACE"
        compose up -d "$SERVICE"
        ;;
    stop)
        compose stop "$SERVICE"
        ;;
    restart)
        ensure_password_file
        mkdir -p "$HOST_WORKSPACE"
        compose up -d --force-recreate "$SERVICE"
        ;;
    status)
        compose ps "$SERVICE"
        ;;
    logs)
        compose logs -f "$SERVICE"
        ;;
    check)
        check_container
        ;;
    *)
        usage
        exit 2
        ;;
esac
