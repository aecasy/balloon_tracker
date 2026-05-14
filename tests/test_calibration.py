import sys
import tempfile
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from vision_tracker.calibration import CalibrationData, load_calibration, load_calibration_optional, save_calibration


class CalibrationTests(unittest.TestCase):
    def test_save_and_load_calibration(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            path = Path(temp_dir) / "camera_calibration.json"
            save_calibration(sample_calibration(), path)

            loaded = load_calibration(path)

        self.assertEqual(loaded.image_width, 640)
        self.assertEqual(loaded.image_height, 480)
        self.assertEqual(loaded.fx, 500.0)
        self.assertEqual(loaded.pattern_cols, 6)
        self.assertEqual(loaded.pattern_rows, 8)
        self.assertEqual(loaded.square_size_mm, 35.8)

    def test_load_optional_missing_returns_none(self):
        self.assertIsNone(load_calibration_optional(Path("does-not-exist.json")))

    def test_invalid_calibration_raises(self):
        with self.assertRaises(ValueError):
            CalibrationData(
                image_width=0,
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


def sample_calibration() -> CalibrationData:
    return CalibrationData(
        image_width=640,
        image_height=480,
        fx=500.0,
        fy=500.0,
        cx=320.0,
        cy=240.0,
        distortion_coefficients=[0.1, -0.1, 0.0, 0.0, 0.0],
        reprojection_error=0.2,
        pattern_cols=6,
        pattern_rows=8,
        square_size_mm=35.8,
        sample_count=15,
        created_at="2026-05-14T00:00:00+00:00",
    )


if __name__ == "__main__":
    unittest.main()
