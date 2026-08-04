# CASY Drone Repo Instructions

These rules apply to this repository for Codex and other coding agents.

## Project Context

- This repo implements the CASY drone camera tracker and migrated Raspberry Pi OS Lite + ROS Docker flight-support stack.
- The active architecture is: Raspberry Pi OS Lite host for Picamera2, MAVProxy, and shutdown handling; ROS Noetic nodes run in Docker and connect to the remote ROS master at `192.168.1.154:11311`.
- The Pi is a ROS node host, not the ROS master.
- Runtime Pi settings live on the Pi in `/etc/casy-drone/pi_os_lite.env`; the committed `deploy/pi_os_lite/pi_os_lite.env.example` is only a template.
- Keep secrets, Wi-Fi passwords, SD-card image locations, and private machine credentials out of git.

## Source Of Truth

- Keep `docs/CASY_Drone_Camera_Project_Specifications.md` as the living project specification.
- Keep `docs/Pi_OS_Lite_Troubleshooting.md` as the running troubleshooting log.
- Keep `docs/Legacy_Ubuntu20_Scan.md` as the reference scan of the old Ubuntu 20.04 image.
- Files under `docs/archived/` are historical context only. Do not treat archived handoff notes as current truth unless the user explicitly asks to recover something from them.

## Safety Rules

- Keep propellers removed during MAVLink, RC override, and service validation.
- Do not enable boot services until manual MAVLink, ROS, and tracker checks pass.
- Do not auto-start Simulink-generated nodes until the active generated package is chosen and validated.
- Preserve the final roadmap ordering: switch to red balloon and full-resolution or higher-resolution tracking only after the migrated flight stack is stable.

## Troubleshooting Discipline

- When an error occurs, a command fails, or behavior differs from the initial expectation, investigate root cause before changing code or configuration.
- Log meaningful troubleshooting outcomes in `docs/Pi_OS_Lite_Troubleshooting.md`, especially:
  - symptoms and exact error messages
  - commands used to diagnose the issue
  - root cause
  - fix or workaround
  - verification command/output summary
- Prefer adding durable notes over relying on chat history.

## Development Checks

- For Python-only changes, run `python -m unittest discover -s tests` when feasible.
- For migration/deployment changes, also consider `python -m unittest discover -s tests` plus Docker build validation on the Pi when Docker behavior is affected.
- For documentation-only changes, at minimum run `git diff --check`.
