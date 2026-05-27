#!/usr/bin/env bash
set -euo pipefail

if [ "$(id -un)" != "casy" ]; then
  echo "Run this as the casy user on the new Pi OS Lite host." >&2
  exit 1
fi

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$PROJECT_DIR"

chmod +x deploy/pi_os_lite/*.sh deploy/pi_os_lite/shutdown_on_ch8.py

sudo apt update
sudo apt install -y git curl python3-venv python3-pip rpicam-apps python3-picamera2 python3-opencv python3-numpy

if ! command -v docker >/dev/null 2>&1; then
  curl -fsSL https://get.docker.com -o /tmp/get-docker.sh
  sudo sh /tmp/get-docker.sh
fi

sudo usermod -aG docker casy

sudo mkdir -p /etc/casy-drone
if [ ! -f /etc/casy-drone/pi_os_lite.env ]; then
  sudo install -m 0644 deploy/pi_os_lite/pi_os_lite.env.example /etc/casy-drone/pi_os_lite.env
fi

sudo mkdir -p /opt/casy-drone
sudo python3 -m venv /opt/casy-drone/mavproxy-venv
sudo /opt/casy-drone/mavproxy-venv/bin/pip install --retries 10 --timeout 120 --no-cache-dir --upgrade pip setuptools
for attempt in 1 2 3 4 5; do
  if sudo /opt/casy-drone/mavproxy-venv/bin/pip install --retries 10 --timeout 120 MAVProxy pymavlink pyserial future; then
    break
  fi
  if [ "$attempt" -eq 5 ]; then
    echo "MAVProxy install failed after $attempt attempts." >&2
    exit 1
  fi
  echo "MAVProxy install failed on attempt $attempt; retrying in 10 seconds..." >&2
  sleep 10
done
sudo install -d -o casy -g casy -m 0755 /var/log/mavproxy

sudo install -m 0644 deploy/pi_os_lite/sudoers.d/casy-shutdown /etc/sudoers.d/casy-shutdown
sudo visudo -cf /etc/sudoers.d/casy-shutdown

sudo install -m 0644 deploy/pi_os_lite/systemd/*.service /etc/systemd/system/
sudo systemctl daemon-reload

sudo docker build -t casy-ros-node -f Dockerfile.ros .

cat <<'EOF'
Install files are in place.

Important:
1. Log out and back in so the docker group takes effect.
2. Review /etc/casy-drone/pi_os_lite.env before enabling services.
3. With props removed, run deploy/pi_os_lite/preflight.sh.
4. Enable services only after MAVLink and ROS connectivity are verified.
EOF
