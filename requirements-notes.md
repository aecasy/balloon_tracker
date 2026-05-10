# Requirements Notes

This project currently relies on Raspberry Pi / Ubuntu apt packages rather than a normal pip-only Python environment.

Install on the Raspberry Pi:

```bash
sudo apt update
sudo apt install -y rpicam-apps python3-picamera2 python3-opencv
```

Avoid:

```bash
pip install picamera2
```

Reason: modern Ubuntu may block system-wide pip writes with `externally-managed-environment`, and Picamera2 is tied to the system camera stack.

For non-camera development on another machine, the geometry tests only require the Python standard library.
