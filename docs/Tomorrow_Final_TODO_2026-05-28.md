# Tomorrow Final TODO - 2026-05-28

## Current Status

- MAVProxy, ROS bridges, tracker pipeline, and CH8 shutdown service were enabled and active after reboot.
- MAVProxy detected the flight controller on `/dev/serial0` at `921600`.
- CH7 autonomy switch publishing was validated.
- CH8 shutdown was validated from the real transmitter.
- Target recognition works.
- The brief ARM/DISARM events seen in MAVProxy logs were intentional manual actions, not unexpected system behavior.
- Props must remain removed during tomorrow's control and shutdown checks.

## Tomorrow Checklist

1. Clean the Pi repo working tree if remaining changes are only chmod or mode leftovers.
2. Power-cycle the drone/Pi with props off and confirm these services auto-start:
   - `casy-mavproxy.service`
   - `casy-ros-bridges.service`
   - `casy-tracker-pipeline.service`
   - `casy-ch8-shutdown.service`
3. Confirm ROS topics from the remote master:
   - `/target_bearing`
   - `/autonomy_enable`
   - `/quad_commands`
   - OptiTrack topics
4. Verify live behavior once more:
   - target visible gives valid `/target_bearing`
   - CH7 switch toggles `/autonomy_enable`
   - CH8 dry-run or controlled real shutdown still works
   - MAVProxy receives FC heartbeat and vehicle status
5. Determine the required locked camera mount angle on the drone before final flight validation.
   - Verify the angle with the real drone geometry, target position, and expected flight attitude.
   - Treat the camera mount as part of the tracking calibration setup: once the angle changes, re-check tracking and calibration assumptions.
   - Design the physical mount so the camera cannot rotate or drift after the angle is chosen.
6. Identify which Simulink-generated ROS package or node is the real active control program.
7. Do not auto-start any Simulink-generated node until the active package is chosen and validated.
8. Do a safe RC override bridge test with props off, starting with all-zero `quad_commands` and confirming ignored override values.
9. Check Windows/Simulink integration against the remote ROS master.
10. Update docs with final validation results:
   - `docs/Pi_OS_Lite_Troubleshooting.md`
   - `docs/CASY_Drone_Camera_Project_Specifications.md`
   - `README.md` if user-facing instructions changed
11. Keep red balloon and full-resolution tracking as the final roadmap task after the migrated flight stack is stable.

## Useful Commands

```bash
cd ~/balloon_tracker
git status --short
deploy/pi_os_lite/preflight.sh
systemctl --no-pager --full status casy-mavproxy.service
systemctl --no-pager --full status casy-ros-bridges.service
systemctl --no-pager --full status casy-tracker-pipeline.service
systemctl --no-pager --full status casy-ch8-shutdown.service
docker ps
```

```bash
docker run --rm --network host \
  -e ROS_MASTER_URI=http://192.168.1.154:11311 \
  -e ROS_IP=192.168.1.126 \
  casy-ros-node rostopic list
```

```bash
docker run --rm --network host \
  -e ROS_MASTER_URI=http://192.168.1.154:11311 \
  -e ROS_IP=192.168.1.126 \
  casy-ros-node rostopic echo -n 1 /target_bearing
```

## Assumptions

- The OptiTrack PC remains ROS master at `192.168.1.154:11311`.
- The Pi keeps the reserved address `192.168.1.126`.
- The external MAVLink consumer remains `192.168.1.115:14550`.
- Props stay off until control behavior is deliberately validated.
