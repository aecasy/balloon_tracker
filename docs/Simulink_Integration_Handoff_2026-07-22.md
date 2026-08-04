# Simulink Integration Handoff - 2026-07-22

This handoff is for the next agent continuing the Simulink integration work. Read
`AGENTS.md` before changing the repository or operating the drone stack.

## Repository State

- Repository: `https://github.com/aecasy/balloon_tracker.git`
- Active checkout: `C:\Users\sarchi\git\balloon_tracker_ros`
- Active branch: `feat/ros-docker`
- Starting commit for this handoff: `740ab7b docs: add current project handoff`
- The similarly named `C:\Users\sarchi\git\balloon_tracker` checkout is on the
  older `main` branch. Do not implement the migration work there.
- No Simulink implementation change was made during the 2026-07-22 discussion.

Read these first:

- `docs/Current_Handoff_2026-07-22.md`
- `docs/Next_Work_Day_Report_2026-06-18.md`
- `docs/CASY_Drone_Camera_Project_Specifications.md`
- `docs/Pi_OS_Lite_Troubleshooting.md`
- `README.md`, section `Simulink GUI ROS Device Container`

## Current Architecture

```text
Windows PC running MATLAB/Simulink
  -> SSH deployment and Monitor & Tune on Pi port 2222

Pi OS Lite: casy@192.168.1.126
  -> native Picamera2 tracker
  -> native MAVProxy and CH8 shutdown listener
  -> ROS Noetic Docker nodes
  -> optional Simulink ROS-device Docker container

ROS master and VRPN node
  -> currently reported at 192.168.1.156:11311
```

The Pi is a ROS node host, not the ROS master.

## Latest ROS Master Finding

On 2026-07-22, the user reported that `roscore` and the VRPN node were running on
`192.168.1.156`. A read-only check from the Pi found:

```text
/etc/casy-drone/pi_os_lite.env:
ROS_MASTER_URI=http://192.168.1.154:11311

192.168.1.156:11311 reachable from the Pi
192.168.1.154:11311 refusing connections
```

The runtime file therefore still had the old master address at the time of the
check. The user was instructed to change it to:

```text
ROS_MASTER_URI=http://192.168.1.156:11311
```

Do not assume that edit was completed. Verify the live file first:

```bash
ssh casy@192.168.1.126
grep '^ROS_MASTER_URI=' /etc/casy-drone/pi_os_lite.env
```

If it is still `.154`, ask the user to update the runtime file or update it with
their approval, then restart only the ROS-dependent services:

```bash
sudo systemctl restart casy-ros-bridges.service
sudo systemctl restart casy-tracker-pipeline.service
```

Verify the ROS graph afterward:

```bash
cd ~/balloon_tracker
./scripts/ros_exec.sh rostopic list
./scripts/ros_exec.sh rostopic echo -n 1 /target_bearing
```

The committed defaults and several docs still mention `.154`. Decide with the
user whether `.156` is permanent before updating repository defaults.

## Existing Simulink Support

The Pi-side deployment target already exists:

- Compose service: `simulink-ros-device`
- Dockerfile: `Dockerfile.simulink-ros-device`
- Helper: `deploy/pi_os_lite/simulink_ros_device.sh`
- Container entrypoint: `docker/simulink_ros_device/entrypoint.sh`
- SSH endpoint: `192.168.1.126:2222`
- SSH user: `ubuntu`
- ROS distribution: Noetic
- ROS folder: `/opt/ros/noetic`
- Catkin workspace: `/home/ubuntu/catkin_ws`
- Compatibility alias: `/home/user/catkin_ws`
- Persistent host workspace: `/home/casy/simulink_catkin_ws`

The Simulink GUI `Test` previously succeeded with those settings. The container
is manual-start only and must remain so until deployment and model behavior are
validated.

Pi commands:

```bash
cd ~/balloon_tracker
deploy/pi_os_lite/simulink_ros_device.sh status
deploy/pi_os_lite/simulink_ros_device.sh start
deploy/pi_os_lite/simulink_ros_device.sh check
```

Windows SSH smoke test:

```powershell
ssh -p 2222 ubuntu@192.168.1.126 "source /opt/ros/noetic/setup.bash && rosversion -d"
```

## Missing Piece

The repository has no `.slx` or `.mdl` source model. It contains only generated
legacy catkin packages copied from the Ubuntu 20.04 image:

```text
fjgadhfas
fjgadhfas2
test_position_control
test_position_control2
test_position_control3
test_position_control4
untitled
```

Their names are not sufficient to identify the intended flight controller.
Do not select or auto-start one by guessing.

The previous agent had just asked the user which integration target to pursue:

1. Create a tiny non-flight Simulink model to prove deployment, ROS subscribe,
   ROS publish, and Monitor & Tune end to end. This is the recommended first step.
2. Integrate the user's real guidance/control `.slx` model from the Windows PC.
3. Recover one of the legacy generated packages from the old Pi image.

Resume by getting the user's answer to this question. If the real model is
chosen, ask for its local path and MATLAB/Simulink release before designing the
deployment workflow.

## Intended Guidance Topic Contract

The eventual guidance model is expected to use:

```text
subscribe /target_bearing       geometry_msgs/PointStamped
subscribe /autonomy_enable      std_msgs/Bool
publish   /quad_commands        std_msgs/UInt16MultiArray
```

Current interpretation of `/target_bearing`:

- `point.x`: calibrated yaw bearing
- `point.y`: calibrated pitch bearing
- `point.z`: detection-valid flag; `1.0` means a valid target and `0.0` means no
  valid target

Confirm this contract against `src/ros_nodes/target_bearing_node.py` before
building the Simulink model.

## Recommended Validation Order

1. Verify the Pi uses the live ROS master at `.156` and can list VRPN topics.
2. Verify the Simulink ROS-device container starts and passes its `check` command.
3. Deploy a tiny non-flight model from Simulink.
4. Demonstrate Monitor & Tune without publishing flight commands.
5. Subscribe to a harmless ROS topic and expose the received value in Simulink.
6. Publish a separate diagnostic/test topic and inspect it with `rostopic echo`.
7. Design the real guidance model around `/target_bearing` and
   `/autonomy_enable`.
8. Stop the MAVLink command bridge before allowing the model to publish
   `/quad_commands`.
9. Validate that autonomy disabled or target invalid produces all-zero/no-override
   commands.
10. Reconnect the RC override bridge only after ROS-only behavior is proven.

## Safety Requirements

- Keep propellers removed during all MAVLink, RC override, shutdown, and generated
  guidance validation.
- Do not auto-start any generated Simulink node yet.
- Before testing a model that can publish `/quad_commands`, stop command delivery:

  ```bash
  sudo systemctl stop casy-ros-bridges.service
  ```

- Confirm the FC remains disarmed during command-path tests.
- `/quad_commands` must remain zero/no-override whenever
  `/autonomy_enable` is false or `/target_bearing.point.z` is `0.0`.
- Do not reconnect command delivery until ROS-only output is verified.

## Known Adjacent Issue

The last report said green-ball recognition only worked when the ball was almost
touching the lens. That is considered a tracker/tuning issue, not a ROS or
Simulink publication issue. A tiny Simulink smoke model can be validated without
waiting for the vision tuning fix, but real guidance validation requires reliable
target detection at realistic distances.

## Documentation Discipline

When a command fails or observed behavior differs from expectation, investigate
the root cause first and record the durable result in
`docs/Pi_OS_Lite_Troubleshooting.md`. Keep
`docs/CASY_Drone_Camera_Project_Specifications.md` aligned with any approved
architecture or ROS topic-contract change.
