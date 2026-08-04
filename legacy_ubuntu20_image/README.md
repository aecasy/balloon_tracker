# Legacy Ubuntu 20.04 Image Files

This directory contains the migration-relevant files copied from the old Ubuntu 20.04 Raspberry Pi image.

Copied from:

```text
ubuntu@192.168.1.167
hostname: pi
OS: Ubuntu 20.04.6 LTS
kernel: 5.4.0-1129-raspi
```

The files are kept here as reference material for porting the old MAVLink, RC override, shutdown, ROS, and Simulink behavior to the Raspberry Pi OS Lite + ROS Docker deployment.

For the running migration/debug notes, including the Raspberry Pi OS Lite install issues and the FC UART serial-console fix, see `../docs/Pi_OS_Lite_Troubleshooting.md`.

## Contents

```text
boot/firmware/
  cmdline.txt
  config.txt
  network-config.redacted
  syscfg.txt
  usercfg.txt
catkin_ws/src/
  Simulink-generated ROS packages from the old image
etc/
  hosts
  netplan/50-cloud-init.yaml
  sudoers.d/
home/ubuntu/
  run_mavproxy.sh
  ros_rc_bridge.py
  ros_rc_ch7_read.py
  shutdown_on_ch8.py
  simulink_to_rc_override.py
  roll_test.py
  test_transmit.py
systemd/
  ch8-shutdown.service
  mavproxy.service
  rc_override.service
  ros_rc_ch7_read.service
```

## Redactions

`etc/netplan/50-cloud-init.yaml` had the Wi-Fi password redacted before committing. `boot/firmware/network-config.redacted` keeps the cloud-init example file with example passwords redacted as well. Do not restore secrets in this repository.

## Notes

The copied service files preserve old IP assumptions such as `ROS_MASTER_URI=http://192.168.1.154:11311` and `ROS_IP=192.168.1.126`. Treat those as legacy references, not final values for the new Pi OS Lite deployment.

During shutdown, the old image may print a message like `A stop job is running for MAVProxy Companion Link (UART) (... / 1min 30s)`. This is systemd waiting for `mavproxy.service` to stop. On the old image, that service runs `home/ubuntu/run_mavproxy.sh`, which starts MAVProxy on `/dev/ttyS0` at `921600` baud and writes telemetry logs under `/var/log/mavproxy/`.

The old `systemd/mavproxy.service` does not define `TimeoutStopSec`, so systemd uses its default stop timeout, often around 90 seconds. The wait does not mean MAVProxy is expected to need that long; it means systemd is giving it a grace period before force-killing it.

For a future or migrated MAVProxy service, set a shorter explicit stop timeout:

```ini
[Service]
TimeoutStopSec=5
KillSignal=SIGINT
KillMode=control-group
```

If MAVProxy does not stop reliably with `SIGINT`, try `KillMode=mixed`.
