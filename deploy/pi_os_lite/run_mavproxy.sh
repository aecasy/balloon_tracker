#!/usr/bin/env bash
set -euo pipefail

FC_UART="${FC_UART:-/dev/serial0}"
MAVLINK_BAUD="${MAVLINK_BAUD:-921600}"
MAVLINK_LOGFILE="${MAVLINK_LOGFILE:-/var/log/mavproxy/Smav.tlog}"
MAVLINK_OUT_GROUND="${MAVLINK_OUT_GROUND:-udp:192.168.1.115:14550}"
MAVLINK_OUT_LOCAL_1="${MAVLINK_OUT_LOCAL_1:-udp:127.0.0.1:14551}"
MAVLINK_OUT_LOCAL_2="${MAVLINK_OUT_LOCAL_2:-udp:127.0.0.1:14552}"
MAVLINK_OUT_LOCAL_3="${MAVLINK_OUT_LOCAL_3:-udp:127.0.0.1:14553}"
MAVLINK_OUT_TCP="${MAVLINK_OUT_TCP:-tcpin:0.0.0.0:5760}"
MAVPROXY_BIN="${MAVPROXY_BIN:-mavproxy.py}"

mkdir -p "$(dirname "$MAVLINK_LOGFILE")" 2>/dev/null || true

exec "$MAVPROXY_BIN" \
  --non-interactive \
  --master="$FC_UART" \
  --baudrate "$MAVLINK_BAUD" \
  --logfile="$MAVLINK_LOGFILE" \
  --out="$MAVLINK_OUT_GROUND" \
  --out="$MAVLINK_OUT_LOCAL_1" \
  --out="$MAVLINK_OUT_LOCAL_2" \
  --out="$MAVLINK_OUT_LOCAL_3" \
  --out="$MAVLINK_OUT_TCP"
