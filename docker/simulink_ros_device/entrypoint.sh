#!/usr/bin/env bash
set -euo pipefail

SSH_PORT="${SIMULINK_ROS_DEVICE_SSH_PORT:-2222}"
WORKSPACE="${SIMULINK_CATKIN_WORKSPACE:-/home/ubuntu/catkin_ws}"
PASSWORD_FILE="${SIMULINK_ROS_DEVICE_PASSWORD_FILE:-}"

if [ -n "${SIMULINK_ROS_DEVICE_PASSWORD:-}" ]; then
    PASSWORD="${SIMULINK_ROS_DEVICE_PASSWORD}"
elif [ -n "$PASSWORD_FILE" ] && [ -f "$PASSWORD_FILE" ]; then
    PASSWORD="$(tr -d '\r\n' < "$PASSWORD_FILE")"
else
    echo "SIMULINK_ROS_DEVICE_PASSWORD or SIMULINK_ROS_DEVICE_PASSWORD_FILE is required" >&2
    exit 64
fi

if [ -z "$PASSWORD" ]; then
    echo "Simulink ROS device password must not be empty" >&2
    exit 64
fi

printf 'ubuntu:%s\n' "$PASSWORD" | chpasswd
unset PASSWORD SIMULINK_ROS_DEVICE_PASSWORD

mkdir -p "$WORKSPACE/src" /run/sshd /etc/ssh/sshd_config.d
chown -R ubuntu:ubuntu "$WORKSPACE"

cat > /etc/ssh/sshd_config.d/simulink_ros_device.conf <<EOF
Port ${SSH_PORT}
PasswordAuthentication yes
KbdInteractiveAuthentication no
PermitRootLogin no
AllowUsers ubuntu
X11Forwarding no
AllowTcpForwarding yes
EOF

ssh-keygen -A >/dev/null
exec /usr/sbin/sshd -D -e
