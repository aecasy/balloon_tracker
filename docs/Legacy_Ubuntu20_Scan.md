# Legacy Ubuntu 20.04 Image Scan

Scanned over SSH on 2026-05-25 from `ubuntu@192.168.1.167`.

This file summarizes the relevant non-camera behavior from the old Ubuntu 20.04 Server image. It intentionally avoids credentials and image-backup details.

## Host

```text
hostname: pi
user: ubuntu
OS: Ubuntu 20.04.6 LTS
kernel: Linux 5.4.0-1129-raspi aarch64
active network during scan: wlan0 192.168.1.167/24
groups include: dialout, sudo, video, netdev
```

Serial devices present:

```text
/dev/ttyS0
/dev/ttyAMA0
```

## Enabled Runtime Services

The important services were enabled and running:

```text
mavproxy.service
rc_override.service
ros_rc_ch7_read.service
ch8-shutdown.service
```

### `mavproxy.service`

Runs `/home/ubuntu/run_mavproxy.sh`.

MAVProxy command:

```bash
/usr/bin/python3 -u /home/ubuntu/.local/bin/mavproxy.py \
  --non-interactive \
  --master=/dev/ttyS0 \
  --baudrate 921600 \
  --logfile=/var/log/mavproxy/Smav.tlog \
  --out=udp:192.168.1.115:14550 \
  --out=udp:127.0.0.1:14551 \
  --out=udp:127.0.0.1:14552 \
  --out=udp:127.0.0.1:14553 \
  --out=tcpin:0.0.0.0:5760
```

This is the core bridge between the flight controller UART and local/network MAVLink consumers.

### `rc_override.service`

Runs `/home/ubuntu/ros_rc_bridge.py`.

Systemd environment:

```text
ROS_MASTER_URI=http://192.168.1.154:11311
ROS_IP=192.168.1.126
PYTHONUNBUFFERED=1
```

Behavior:

```text
ROS topic in: quad_commands
ROS message type: std_msgs/UInt16MultiArray
MAVLink endpoint: udp:127.0.0.1:14552
rate: 50 Hz
```

Channel mapping:

```text
data[0] -> CH1 roll
data[1] -> CH2 pitch
data[2] -> CH3 throttle/climb
data[3] -> CH4 yaw
data[5] -> CH6 flight mode
```

`0` means no command and is converted to MAVLink ignore value `65535`. Values are clamped to `1000..2000`.

### `ros_rc_ch7_read.service`

Runs `/home/ubuntu/ros_rc_ch7_read.py`.

Systemd environment:

```text
ROS_MASTER_URI=http://192.168.1.154:11311
ROS_IP=192.168.1.126
PYTHONUNBUFFERED=1
```

Behavior:

```text
MAVLink endpoint: udp:127.0.0.1:14552
reads: RC channel 7
threshold: > 1800
ROS topic out: autonomy_enable
ROS message type: std_msgs/Bool
rate: 50 Hz
```

### `ch8-shutdown.service`

Runs `/home/ubuntu/shutdown_on_ch8.py`.

Behavior:

```text
MAVLink endpoint: udpin:127.0.0.1:14552
reads: RC channel 8
shutdown threshold: >= 1900
low/reset threshold: <= 1500
hold time: 1.0 s
action: sudo /sbin/shutdown -h now
```

## Other Relevant Script

`/home/ubuntu/simulink_to_rc_override.py` exists but was not found as an enabled service during the scan.

Behavior:

```text
ROS topic in: /guidance/rc
ROS message type: std_msgs/UInt16MultiArray
direct MAVLink UART: /dev/ttyAMA0
baudrate: 921600
send rate: 50 Hz
failsafe timeout: 0.25 s
safe RC: [1600, 0, 0, 0]
```

This looks like an earlier or alternate direct-serial bridge. The active services instead use MAVProxy and `udp:127.0.0.1:14552`.

## ROS / Simulink Workspace

Workspace:

```text
/home/ubuntu/catkin_ws
```

Detected generated packages:

```text
fjgadhfas
fjgadhfas2
test_position_control
test_position_control2
test_position_control3
test_position_control4
untitled
```

All packages depend on:

```text
geometry_msgs
roscpp
std_msgs
```

The workspace appears to contain Simulink-generated C++ ROS nodes with external mode support files (`ext_svr.c`, `rtiostream_tcpip.c`, `packageInfo.mat`, etc.).

Generated topic behavior:

```text
fjgadhfas, fjgadhfas2, test_position_control3, test_position_control4, untitled:
  subscribe /autonomy_enable                  std_msgs/Bool
  subscribe /vrpn_client_node/Quad/pose       geometry_msgs/PoseStamped
  subscribe /vrpn_velocity/optitrack_frame/filtered geometry_msgs/TwistStamped
  publish   quad_commands                     std_msgs/UInt16MultiArray

test_position_control, test_position_control2:
  subscribe /vrpn_client_node/Quad/pose       geometry_msgs/PoseStamped
  publish   quad_commands                     std_msgs/UInt16MultiArray
```

## Installed Package Clues

Python packages from `pip3 freeze`:

```text
mavproxy==1.8.74
pymavlink==2.4.49
pyserial==3.5
numpy==1.17.4
rosdep==0.25.1
rospkg==1.6.0
```

Relevant apt packages included ROS Noetic base/comm packages, `python3-opencv`, `python3-numpy`, `python3-serial`, and `micro`.

## Migration Notes

The old image assumed a remote ROS master:

```text
ROS_MASTER_URI=http://192.168.1.154:11311
ROS_IP=192.168.1.126
```

During the scan the Pi was actually reachable at `192.168.1.167`, so the fixed `ROS_IP` may be stale or tied to a previous network assignment.

For the new Raspberry Pi OS Lite + Docker deployment, the old behavior to reproduce is:

```text
flight controller UART -> MAVProxy -> local MAVLink UDP ports
Simulink/ROS UInt16MultiArray on quad_commands -> RC override bridge -> MAVLink RC override
RC CH7 -> autonomy_enable Bool topic
RC CH8 high hold -> Pi shutdown
vision tracker -> /target_bearing -> future guidance/Simulink control path
```

Resolved migration decision:

```text
MAVProxy: native on Pi OS Lite, /dev/serial0, 921600 baud
CH8 shutdown listener: native on Pi OS Lite
ROS master: dedicated Ubuntu OptiTrack PC at 192.168.1.154:11311
Pi ROS identity: 192.168.1.168
ROS MAVLink bridge nodes: Docker ROS Noetic containers
Simulink-generated packages: build inside Docker, but do not auto-start yet
```

This split keeps serial and shutdown behavior on the host while keeping ROS Noetic dependencies inside the container.
