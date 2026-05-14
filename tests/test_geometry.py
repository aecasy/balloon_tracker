import math
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from vision_tracker.calibration import CalibrationData
from vision_tracker.geometry import (
    ImageSize,
    PixelPoint,
    calibrated_pixel_to_bearing_degrees,
    image_center,
    pixel_offset,
    pixel_to_bearing_degrees,
)


class GeometryTests(unittest.TestCase):
    def test_image_center_for_even_dimensions(self):
        self.assertEqual(image_center(ImageSize(640, 480)), PixelPoint(319.5, 239.5))

    def test_pixel_offset_uses_positive_y_up(self):
        dx, dy = pixel_offset(PixelPoint(419.5, 189.5), ImageSize(640, 480))

        self.assertEqual(dx, 100.0)
        self.assertEqual(dy, 50.0)

    def test_invalid_image_size_raises(self):
        with self.assertRaises(ValueError):
            ImageSize(0, 480)

    def test_pixel_to_bearing_degrees(self):
        yaw, pitch = pixel_to_bearing_degrees(
            PixelPoint(419.5, 139.5),
            ImageSize(640, 480),
            focal_length_px=(500.0, 500.0),
        )

        self.assertTrue(math.isclose(yaw, 11.3099, rel_tol=1e-4))
        self.assertTrue(math.isclose(pitch, 11.3099, rel_tol=1e-4))

    def test_pixel_to_bearing_requires_positive_focal_lengths(self):
        with self.assertRaises(ValueError):
            pixel_to_bearing_degrees(PixelPoint(0, 0), ImageSize(640, 480), (0.0, 500.0))

    def test_calibrated_center_is_zero_bearing_without_cv2(self):
        yaw, pitch = calibrated_pixel_to_bearing_degrees(
            PixelPoint(320.0, 240.0),
            sample_calibration(),
            cv2_module=False,
        )

        self.assertTrue(math.isclose(yaw, 0.0, abs_tol=1e-9))
        self.assertTrue(math.isclose(pitch, 0.0, abs_tol=1e-9))

    def test_calibrated_bearing_signs_without_cv2(self):
        right_yaw, _ = calibrated_pixel_to_bearing_degrees(PixelPoint(420.0, 240.0), sample_calibration(), cv2_module=False)
        left_yaw, _ = calibrated_pixel_to_bearing_degrees(PixelPoint(220.0, 240.0), sample_calibration(), cv2_module=False)
        _, up_pitch = calibrated_pixel_to_bearing_degrees(PixelPoint(320.0, 140.0), sample_calibration(), cv2_module=False)
        _, down_pitch = calibrated_pixel_to_bearing_degrees(PixelPoint(320.0, 340.0), sample_calibration(), cv2_module=False)

        self.assertGreater(right_yaw, 0.0)
        self.assertLess(left_yaw, 0.0)
        self.assertGreater(up_pitch, 0.0)
        self.assertLess(down_pitch, 0.0)


def sample_calibration() -> CalibrationData:
    return CalibrationData(
        image_width=640,
        image_height=480,
        fx=500.0,
        fy=500.0,
        cx=320.0,
        cy=240.0,
        distortion_coefficients=[],
        reprojection_error=0.2,
        pattern_cols=6,
        pattern_rows=8,
        square_size_mm=35.8,
        sample_count=15,
        created_at="2026-05-14T00:00:00+00:00",
    )


if __name__ == "__main__":
    unittest.main()
