import math
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from vision_tracker.geometry import ImageSize, PixelPoint, image_center, pixel_offset, pixel_to_bearing_degrees


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


if __name__ == "__main__":
    unittest.main()
