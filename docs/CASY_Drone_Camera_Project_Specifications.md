# CASY Drone Camera Project Specifications

This is the living project specification. Archived handoff notes may describe earlier assumptions; this file should match the current intended system.

## Goal

Build a Raspberry Pi camera-based companion module for the CASY drone. The module detects a colored target in live video, converts the target centroid into calibrated yaw/pitch bearing angles, publishes those bearings into ROS, and coexists with the migrated MAVLink/Simulink control path.

The system does not currently estimate distance, perform 3D reconstruction, run SLAM, or use neural-network detection. The active vision approach is classical OpenCV color segmentation plus contour scoring.

## Current Target And Final Target

Current development target:

- green ball
- HSV segmentation
- scored contour selection
- calibrated yaw/pitch output

Final target, after the migrated flight stack is stable:

- red balloon
- full-resolution or higher-resolution tracking as performance allows
- retuned HSV/scoring configuration
- new calibration at the exact final camera geometry

The red balloon/full-resolution work is intentionally the last roadmap item, after ROS, MAVLink, and boot services are validated.

## Hardware

- Raspberry Pi 4
- Raspberry Pi Camera Module 3, IMX708
- flight controller connected to the Pi UART
- local network with Windows development PC and Ubuntu OptiTrack ROS master PC
- current color target: green ball
- final color target: red balloon

## Runtime Architecture

The Camera Module 3 requires the modern Raspberry Pi camera stack. The old Ubuntu 20.04 Server image used for ROS Noetic cannot expose the IMX708 camera driver/overlay on its 5.4 Raspberry Pi kernel, so the deployed system uses Raspberry Pi OS Lite as the host OS and ROS Noetic inside Docker.

Current architecture:

```text
Ubuntu OptiTrack PC
  roscore on 192.168.1.154:11311
  OptiTrack ROS topics

Raspberry Pi OS Lite host
  native Picamera2 / libcamera / rpicam-apps
  native Python tracker
  native MAVProxy on /dev/serial0 at 921600
  native CH8 shutdown listener
  Docker ROS Noetic nodes
    /target_bearing publisher
    quad_commands -> MAVLink RC override bridge
    RC CH7 -> autonomy_enable publisher
    build-only Simulink-generated catkin packages
```

The Pi is a ROS node host, not the ROS master. Runtime values live in `/etc/casy-drone/pi_os_lite.env` on the Pi.

Expected ROS settings:

```text
ROS_MASTER_URI=http://192.168.1.154:11311
ROS_IP=<current Pi IP>
```

The current Pi has used `192.168.1.126` during recent testing. The template still contains the earlier planned `192.168.1.168`. A future quality-of-life task is to support `ROS_IP=auto`.

## Vision Pipeline

1. Capture frames with Picamera2.
2. Request a wide IMX708 raw mode, usually `2304x1296`.
3. Process a configured 16:9 output frame such as `1280x720`, `960x540`, or `640x360`.
4. Convert frame to HSV.
5. Threshold by configured HSV bounds.
6. Clean mask with morphology.
7. Find candidate contours.
8. Reject candidates below minimum area and quality thresholds.
9. Score valid candidates.
10. Select the best candidate.
11. Smooth centroid.
12. Convert centroid to image offset and calibrated yaw/pitch bearing.
13. Emit human-readable lines, JSON, or ROS-piped JSON depending on runtime mode.

Runtime and tuning parameters are stored in:

```text
config/green_tracker.json
```

The active calibration file for the current deployment is:

```text
config/camera_calibration_1280x720_raw2304x1296.json
```

Calibration is tied to the exact `width`, `height`, `raw_width`, and `raw_height`. A `1280x720` calibration must not be treated as interchangeable with `640x360` unless a calibration-scaling workflow is explicitly implemented and validated.

## Tracker Output

The tracker reports target detection and quality data:

```text
detected=<bool>
dx=<int|None>
dy=<int|None>
area=<int>
circularity=<float>
score=<float>
yaw_deg=<float|None>
pitch_deg=<float|None>
```

Important definitions:

- `detected`: whether a valid target was found.
- `dx`: horizontal pixel offset from image center. Positive means target is right of center.
- `dy`: vertical pixel offset from image center. Positive means target is above center.
- `yaw_deg`: calibrated horizontal bearing angle.
- `pitch_deg`: calibrated vertical bearing angle.
- `score`: weighted contour score from enabled scoring components.

For ROS integration, `target_bearing_node.py` publishes calibrated bearing data to:

```text
/target_bearing
```

The exact ROS message path should stay aligned with `src/ros_nodes/target_bearing_node.py` and the README.

## Candidate Scoring

The legacy tracker selected the largest contour that passed area and circularity gates. The current scored method ranks every valid contour using weighted components:

- `color_fill`
- `circularity`
- `circle_fit`
- `enclosing_fill`
- `solidity`
- `relative_area`
- optional `shading`

Only enabled scoring components with positive weights participate in the final score:

```text
final_score = sum(component_score * component_weight) / sum(active_component_weights)
```

If every component is disabled or every active weight is zero, scored detection returns no target.

`shading` is off by default because it costs more CPU and depends on lighting.

## Calibration

Checkerboard:

```text
6 by 8 inner corners
35.8 mm square size
```

Recommended sample count:

```text
15 minimum
20-25 preferred
```

Capture samples across the frame: center, corners, edges, closer, farther, and tilted. Use the same camera geometry for tuning, calibration, and final runtime.

When running headless, use the TCP remote viewer path instead of OpenCV local windows:

```bash
python3 scripts/calibrate_camera.py --stream-port 5000
python scripts/remote_viewer.py --ip <pi-ip> --port 5000
```

## ROS And MAVLink Integration

Native host services:

- `casy-mavproxy.service`
- `casy-ch8-shutdown.service`

Docker ROS services:

- `casy-ros-bridges.service`
- `casy-tracker-pipeline.service`

MAVProxy settings:

```text
FC UART: /dev/serial0
baud: 921600
ground output: udp:192.168.1.115:14550
local outputs: udp:127.0.0.1:14551..14553
TCP input: tcpin:0.0.0.0:5760
```

The Pi serial login console must be disabled before using `/dev/serial0` for MAVLink. See `docs/Pi_OS_Lite_Troubleshooting.md` for the exact checks and fix.

RC override behavior:

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

`0` means no command and is converted to MAVLink ignore value `65535`. Active PWM values are clamped to `1000..2000`.

RC channel 7 behavior:

```text
RC CH7 > 1800 -> autonomy_enable=True
topic: autonomy_enable
message type: std_msgs/Bool
rate: 50 Hz
```

RC channel 8 shutdown behavior:

```text
shutdown threshold: >= 1900
reset threshold: <= 1500
hold time: 1.0 s
action: sudo /sbin/shutdown -h now
```

## Safety And Validation Rules

- Keep propellers removed during all MAVLink, RC override, and service validation.
- Start services one at a time.
- Do not enable boot services until manual checks pass.
- Do not auto-start Simulink-generated nodes until the active generated package is chosen and validated.
- A USB-powered FC may report battery/pre-arm warnings; that does not by itself invalidate UART communication.

Required validation path:

1. `deploy/pi_os_lite/preflight.sh`
2. MAVProxy heartbeat from the FC on `/dev/serial0`
3. CH8 shutdown behavior
4. CH7 `autonomy_enable` publication
5. safe `quad_commands` test with zeros mapping to ignore values
6. `/target_bearing` publication from the tracker pipeline
7. boot enablement only after the above pass

## Roadmap

1. Finish migrated Pi OS Lite flight-stack validation.
2. Validate Docker ROS bridge services against the remote ROS master.
3. Choose the active Simulink-generated package, then decide whether and how to auto-start it.
4. Validate `/target_bearing` consumption by the downstream control path.
5. Add `ROS_IP=auto` support for Pi network changes.
6. Move to the final red balloon target and full-resolution or higher-resolution tracking.
