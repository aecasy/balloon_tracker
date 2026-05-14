# Calibration Notes

Calibration is intentionally a later project phase.

Before calibration:

- Confirm the target is detected reliably.
- Confirm `dx` and `dy` move in the expected direction.
- Confirm the contour does not jump to background objects.
- Decide whether focus, exposure, and white balance should be locked.

Future calibration workflow:

1. Capture chessboard or calibration target images.
2. Estimate camera matrix and distortion coefficients with OpenCV.
3. Save `fx`, `fy`, `cx`, `cy`, and distortion coefficients.
4. Add tests for pixel-to-bearing conversion.
5. Convert target centroid to yaw and pitch bearing angles.

Do not add ROS publishing until this math is verified.

Current project checkerboard:

- 6 by 8 inner corners
- 35.8 mm square size

Calibration command:

```bash
python3 scripts/calibrate_camera.py --pattern-cols 6 --pattern-rows 8 --square-size-mm 35.8
```
