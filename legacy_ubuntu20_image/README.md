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
