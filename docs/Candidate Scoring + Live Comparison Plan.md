# Candidate Scoring + Live Comparison Plan

## Summary
Add a side-by-side detection scorer that keeps the current HSV + contour pipeline, but changes candidate selection from “largest contour passing thresholds” to “best weighted candidate.” Do not use fixed radius or fixed object size as a gate. Keep the old method visible during testing so you can compare behavior live on the Pi.

Also fix the tuning GUI hitbox bug by making the control panel window use exact canvas dimensions or by mapping mouse coordinates back to canvas coordinates before hit-testing.

## Key Changes
- Add a candidate metrics layer in `tracker.py`:
  - `circularity`: current `4*pi*area/perimeter^2`.
  - `enclosing_fill`: contour area divided by enclosing-circle area, scale-independent.
  - `solidity`: contour area divided by convex hull area.
  - `color_fill`: green mask density inside the candidate’s enclosing circle or contour ROI.
  - `shading_score`: optional low-weight sphere cue from smoothness/gradient in the HSV `V` channel.
- Add `ScoringConfig` to JSON config:
  - weights: `color_fill`, `circularity`, `enclosing_fill`, `solidity`, `shading`.
  - minimum final score, default around `0.55`.
  - `shading_enabled`, default `false` or very low weight initially.
  - `shading_min_area`, default around `400`, below which shading returns neutral `0.5` so far-away tiny balls are not punished.
- Add `ScoredCandidate` and `ScoredDetectionResult`:
  - include centroid, dx/dy, area, circularity, each component score, final score, and selected method.
  - preserve the existing log fields, but append `score=<float>` and component details when requested.
- Keep old detection method:
  - `legacy`: current largest valid contour.
  - `scored`: new weighted best candidate.
  - live tools show both at once; runtime can default to `scored` only after comparison proves it better.

## Testing Tools
- Add a live comparison script, likely `scripts/compare_trackers.py`:
  - uses the same camera/config/mask pipeline.
  - overlays legacy detection and scored detection in different colors.
  - shows a candidate table on the frame: area, circularity, fill, solidity, color fill, shading, final score.
  - prints both outputs per frame for quick terminal comparison.
- Extend `scripts/tune_tracker.py`:
  - add a “Scoring” group for weights and minimum score.
  - add a display toggle for showing candidate scores.
  - keep “Target color” and “Detection quality” first so tuning does not become overwhelming.
- Add synthetic unit tests for score math:
  - filled circle should score higher than thin/irregular blob.
  - small compact noise can have high circularity but should not beat a larger, filled, solid ball-like candidate.
  - shading score returns neutral for very small areas.
  - disabling shading leaves shape/color scoring unchanged.

## GUI Bug Fix
- Fix mouse hit-testing in `tune_tracker.py` by removing OpenCV resize drift:
  - create the controls window with `cv2.WINDOW_NORMAL`.
  - immediately set the window image size to exactly `PANEL_WIDTH x PANEL_HEIGHT`.
  - either stop resizing the window after drawing, or store actual displayed size and map mouse coordinates to canvas coordinates.
- Preferred implementation:
  - use exact-size canvas hitboxes and avoid calling `resizeWindow` to a size different from the canvas.
  - add a tiny debug option `--show-control-hitboxes` that draws row rectangles if the issue persists on the Pi.

## Assumptions
- Comparison will be live-camera first, not recorded video.
- The new scorer will run side by side with the old method before replacing it.
- No fixed radius or fixed object-size gate will be added.
- Shading is experimental and low priority; shape/color/fill/solidity should carry the decision.
