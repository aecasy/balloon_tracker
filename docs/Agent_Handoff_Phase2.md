# CASY Drone Tracker - Phase 2 Handoff Document

This document summarizes the architecture, recent achievements, and current state of the CASY Drone Camera Green Ball Tracker project. It is intended for an AI Agent to seamlessly pick up development where the previous session left off.

## Current Architecture & Environment

The project relies on a hybrid execution model because the Raspberry Pi Camera Module 3 (IMX708) requires a modern operating system with libcamera support, which breaks compatibility with the native, legacy ROS Noetic packages designed for Ubuntu 20.04.

*   **Hardware:** Raspberry Pi 4, Raspberry Pi Camera Module 3, connected to a flight controller.
*   **Host OS:** Raspberry Pi OS Lite (64-bit, headless Debian Bookworm). This runs the native Picamera2 libraries for maximum performance.
*   **ROS Environment:** A Docker container (`ros:noetic-ros-base-focal`) running in host networking mode.
*   **Development Machine:** A Windows PC on the same local network, used for SSH and viewing the remote camera stream.

### The Pipeline
1.  **Vision Node (`scripts/green_tracker.py`):** Runs natively on the PiOS host. Uses OpenCV HSV masking and candidate scoring to find a green target. Outputs JSON strings containing `x` (yaw), `y` (pitch), and `z` (1.0 = detected, 0.0 = lost).
2.  **Pipe:** The JSON strings are piped via stdout directly into the Docker container.
3.  **ROS Bridge (`src/ros_nodes/target_bearing_node.py`):** Runs inside the Docker container. Parses the JSON from `stdin` and publishes `geometry_msgs/PointStamped` messages to the `/target_bearing` topic.

## What Was Just Achieved (Phase 1)

1.  **Resolved OS/Camera Conflicts:** Migrated from an incompatible Ubuntu 26.04 bring-up to the modern PiOS Lite OS.
2.  **Built the Docker Infrastructure:** 
    *   Created `Dockerfile.ros` to package ROS Noetic and the bridge script.
    *   Added `docker-compose.yml` to manage `roscore`.
3.  **Implemented Headless TCP Streaming:** Because the Pi is headless, we cannot use `cv2.imshow`. 
    *   Created `src/vision_tracker/streamer.py` and `scripts/remote_viewer.py`. 
    *   The Pi streams JPEG frames over TCP, and the Windows machine views them and sends keystrokes back (essential for camera calibration).
4.  **Performance Tuning:** Verified the full piped pipeline runs natively at **~54 FPS** with a 1280x720 capture and 2304x1296 raw sensor mode.
5.  **Quality-of-Life Scripts:** Added `scripts/ros_exec.sh` to fix Docker ROS environment issues. Users can now run `./scripts/ros_exec.sh rostopic echo /target_bearing` without manually sourcing `setup.bash`.

## How to Run the System

**1. Start ROS Core (On Pi)**
```bash
sudo docker compose up -d
```

**2. Start the Piped Tracker (On Pi)**
*(The tracker is silent because stdout is piped to the container)*
```bash
python3 scripts/green_tracker.py \
  --width 1280 \
  --height 720 \
  --raw-width 2304 \
  --raw-height 1296 \
  --method scored \
  --output json \
  --headless \
  --calibration config/camera_calibration_1280x720_raw2304x1296.json \
  | sudo docker run -i --rm --network host casy-ros-node
```

**3. Verify the ROS Topic (On Pi - Second Terminal)**
```bash
./scripts/ros_exec.sh rostopic echo /target_bearing
```

**4. Stream Debug Video (Optional)**
If you want to *see* what the tracker is doing, stop the pipeline above and run:
*   **On Pi:** `python3 scripts/green_tracker.py --stream-port 5000`
*   **On Windows:** `python scripts/remote_viewer.py --ip <PI_IP> --port 5000`

## Next Steps for the New Agent

1.  **Flight Controller Integration:** The vision node successfully publishes `/target_bearing`. The next major milestone is subscribing to this topic from the flight controller or Simulink model to issue drone movement commands based on the yaw/pitch errors.
2.  **Auto-Start:** Implement a systemd service to automatically launch the pipeline (`docker compose up -d` followed by the piped tracker script) on Pi boot so the drone is flyable without SSH.
3.  **Dynamic Reconfigure:** If the user wants to adjust tracker HSV parameters during flight, the tracker might need to pull parameters dynamically from a ROS service rather than loading a static JSON file on boot.

All code is currently committed to the `feat/ros-docker` branch.
