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
