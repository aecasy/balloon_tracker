#!/usr/bin/env bash
exec /usr/bin/python3 -u /home/ubuntu/.local/bin/mavproxy.py \
  --non-interactive \
  --master=/dev/ttyS0 \
  --baudrate 921600 \
  --logfile=/var/log/mavproxy/Smav.tlog \
  --out=udp:192.168.1.115:14550 \
  --out=udp:127.0.0.1:14551 \
  --out=udp:127.0.0.1:14552 \
  --out=udp:127.0.0.1:14553 \
  --out=tcpin:0.0.0.0:5760
