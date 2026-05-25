//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: untitled.cpp
//
// Code generated for Simulink model 'untitled'.
//
// Model version                  : 1.0
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Jan 15 18:03:02 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "untitled.h"
#include "rtwtypes.h"
#include <math.h>
#include "untitled_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>
#include "untitled_types.h"
#include "rt_defines.h"
#include <float.h>
#include "untitled_dt.h"

// Block signals (default storage)
B_untitled_T untitled_B;

// Block states (default storage)
DW_untitled_T untitled_DW;

// Real-time model
RT_MODEL_untitled_T untitled_M_ = RT_MODEL_untitled_T();
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

// Forward declaration for local functions
static void untitled_cosd(real_T *x);
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    real_T q;
    if (u1 < 0.0) {
      q = ceil(u1);
    } else {
      q = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != q)) {
      q = fabs(u0 / u1);
      if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S5>/MATLAB Function1'
static void untitled_cosd(real_T *x)
{
  if (rtIsInf(*x) || rtIsNaN(*x)) {
    *x = (rtNaN);
  } else {
    real_T absx;
    real_T b_x;
    int8_T n;
    b_x = rt_remd_snf(*x, 360.0);
    absx = fabs(b_x);
    if (absx > 180.0) {
      if (b_x > 0.0) {
        b_x -= 360.0;
      } else {
        b_x += 360.0;
      }

      absx = fabs(b_x);
    }

    if (absx <= 45.0) {
      b_x *= 0.017453292519943295;
      n = 0;
    } else if (absx <= 135.0) {
      if (b_x > 0.0) {
        b_x = (b_x - 90.0) * 0.017453292519943295;
        n = 1;
      } else {
        b_x = (b_x + 90.0) * 0.017453292519943295;
        n = -1;
      }
    } else if (b_x > 0.0) {
      b_x = (b_x - 180.0) * 0.017453292519943295;
      n = 2;
    } else {
      b_x = (b_x + 180.0) * 0.017453292519943295;
      n = -2;
    }

    switch (n) {
     case 0:
      *x = cos(b_x);
      break;

     case 1:
      *x = -sin(b_x);
      break;

     case -1:
      *x = sin(b_x);
      break;

     default:
      *x = -cos(b_x);
      break;
    }
  }
}

// Model step function
void untitled_step(void)
{
  SL_Bus_untitled_std_msgs_Bool b_varargout_2;
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_0;
  int32_T i;
  boolean_T b_varargout_1;
  boolean_T rtb_AND;
  boolean_T tmp;

  // Reset subsysRan breadcrumbs
  srClearBC(untitled_DW.EnabledSubsystem_SubsysRanBC_o);

  // Reset subsysRan breadcrumbs
  srClearBC(untitled_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(untitled_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(untitled_DW.IfActionSubsystem2_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(untitled_DW.EnabledSubsystem_SubsysRanBC_d);

  // Reset subsysRan breadcrumbs
  srClearBC(untitled_DW.EnabledSubsystem_SubsysRanBC);

  // Outputs for Atomic SubSystem: '<S3>/Subscribe'
  // MATLABSystem: '<S10>/SourceBlock'
  b_varargout_1 = Sub_untitled_39.getLatestMessage(&untitled_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S20>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S20>/In1'
    untitled_B.In1 = untitled_B.b_varargout_2;
    srUpdateBC(untitled_DW.EnabledSubsystem_SubsysRanBC_d);
  }

  // End of MATLABSystem: '<S10>/SourceBlock'
  // End of Outputs for SubSystem: '<S10>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S3>/Subscribe'

  // Gain: '<S3>/Gain'
  untitled_B.x = untitled_P.Gain_Gain * untitled_B.In1.Pose.Position.Y;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  untitled_B.X = untitled_B.In1.Pose.Position.X;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  untitled_B.Z = untitled_B.In1.Pose.Position.Z;

  // MATLAB Function: '<S28>/MATLAB Function' incorporates:
  //   Constant: '<S28>/Constant'

  if (untitled_DW.filled == 0) {
    untitled_DW.bufX[untitled_DW.idx - 1] = untitled_B.x;
    untitled_DW.bufY[untitled_DW.idx - 1] = untitled_B.X;
    untitled_DW.bufZ[untitled_DW.idx - 1] = untitled_B.Z;
    untitled_DW.filled = 1U;
    untitled_DW.idx = 2U;
    untitled_B.Valid = true;
    untitled_B.frozenNow = false;
    untitled_B.filled_ = 0U;
    untitled_B.updated = false;
    untitled_B.d = -1.0;
    untitled_B.v = -1.0;
  } else {
    uint32_T qY;
    uint8_T prevIdx;
    qY = untitled_DW.idx - 1U;
    if (untitled_DW.idx - 1U > untitled_DW.idx) {
      qY = 0U;
    }

    prevIdx = static_cast<uint8_T>(qY);
    if (static_cast<uint8_T>(qY) == 0) {
      prevIdx = 6U;
    }

    untitled_B.dx = untitled_B.x - untitled_DW.bufX[prevIdx - 1];
    untitled_B.dy = untitled_B.X - untitled_DW.bufY[prevIdx - 1];
    untitled_B.dz = untitled_B.Z - untitled_DW.bufZ[prevIdx - 1];
    untitled_B.d = sqrt((untitled_B.dx * untitled_B.dx + untitled_B.dy *
                         untitled_B.dy) + untitled_B.dz * untitled_B.dz);
    untitled_B.v = untitled_B.d / untitled_P.time_step;
    untitled_B.updated = (untitled_B.d > 1.0E-6);
    untitled_B.frozenNow = false;
    if (untitled_DW.filled >= 6) {
      boolean_T exitg1;
      untitled_B.frozenNow = true;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 5)) {
        int32_T ddx_tmp_tmp;
        ddx_tmp_tmp = prevIdx - 1;
        untitled_B.dx = untitled_B.x - untitled_DW.bufX[prevIdx - 1];
        untitled_B.dy = untitled_B.X - untitled_DW.bufY[prevIdx - 1];
        untitled_B.dz = untitled_B.Z - untitled_DW.bufZ[prevIdx - 1];
        if (sqrt((untitled_B.dx * untitled_B.dx + untitled_B.dy * untitled_B.dy)
                 + untitled_B.dz * untitled_B.dz) > 1.0E-6) {
          untitled_B.frozenNow = false;
          exitg1 = true;
        } else {
          prevIdx = static_cast<uint8_T>(prevIdx - 1);
          if (static_cast<uint8_T>(ddx_tmp_tmp) == 0) {
            prevIdx = 6U;
          }

          i++;
        }
      }
    }

    if (!untitled_DW.inLost) {
      if ((untitled_B.v > 20.0) || untitled_B.frozenNow) {
        untitled_DW.inLost = true;
        untitled_DW.goodCnt = 0U;
        untitled_B.Valid = false;
      } else {
        untitled_B.Valid = true;
      }
    } else if (untitled_B.updated && (untitled_B.v <= 20.0)) {
      if (untitled_DW.goodCnt < 255) {
        untitled_DW.goodCnt = static_cast<uint8_T>(untitled_DW.goodCnt + 1U);
      }

      if (untitled_DW.goodCnt >= 5) {
        untitled_DW.inLost = false;
        untitled_DW.goodCnt = 0U;
        untitled_B.Valid = true;
      } else {
        untitled_B.Valid = false;
      }
    } else {
      if (untitled_B.v > 20.0) {
        untitled_DW.goodCnt = 0U;
      }

      untitled_B.Valid = false;
    }

    untitled_DW.bufX[untitled_DW.idx - 1] = untitled_B.x;
    untitled_DW.bufY[untitled_DW.idx - 1] = untitled_B.X;
    untitled_DW.bufZ[untitled_DW.idx - 1] = untitled_B.Z;
    if (untitled_DW.filled < 6) {
      untitled_DW.filled = static_cast<uint8_T>(untitled_DW.filled + 1U);
    }

    i = static_cast<int32_T>(untitled_DW.idx + 1U);
    if (untitled_DW.idx + 1U > 255U) {
      i = 255;
    }

    untitled_DW.idx = static_cast<uint8_T>(i);
    if (untitled_DW.idx > 6) {
      untitled_DW.idx = 1U;
    }

    untitled_B.filled_ = untitled_DW.filled;
  }

  // End of MATLAB Function: '<S28>/MATLAB Function'

  // Sqrt: '<S18>/sqrt' incorporates:
  //   Product: '<S19>/Product'
  //   Product: '<S19>/Product1'
  //   Product: '<S19>/Product2'
  //   Product: '<S19>/Product3'
  //   Sum: '<S19>/Sum'

  untitled_B.dz = sqrt(((untitled_B.In1.Pose.Orientation.W *
    untitled_B.In1.Pose.Orientation.W + untitled_B.In1.Pose.Orientation.X *
    untitled_B.In1.Pose.Orientation.X) + untitled_B.In1.Pose.Orientation.Y *
                        untitled_B.In1.Pose.Orientation.Y) +
                       untitled_B.In1.Pose.Orientation.Z *
                       untitled_B.In1.Pose.Orientation.Z);

  // Product: '<S13>/Product'
  untitled_B.dy = untitled_B.In1.Pose.Orientation.W / untitled_B.dz;

  // Product: '<S13>/Product1'
  untitled_B.Sum4 = untitled_B.In1.Pose.Orientation.X / untitled_B.dz;

  // Product: '<S13>/Product2'
  untitled_B.Product2 = untitled_B.In1.Pose.Orientation.Y / untitled_B.dz;

  // Product: '<S13>/Product3'
  untitled_B.dz = untitled_B.In1.Pose.Orientation.Z / untitled_B.dz;

  // Fcn: '<S11>/fcn2' incorporates:
  //   Fcn: '<S11>/fcn5'

  untitled_B.VectorConcatenate_tmp = untitled_B.dy * untitled_B.dy;
  untitled_B.VectorConcatenate_tmp_c = untitled_B.Sum4 * untitled_B.Sum4;
  VectorConcatenate_tmp = untitled_B.Product2 * untitled_B.Product2;
  VectorConcatenate_tmp_0 = untitled_B.dz * untitled_B.dz;

  // Trigonometry: '<S12>/Trigonometric Function1' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn1'
  //   Fcn: '<S11>/fcn2'

  untitled_B.VectorConcatenate[0] = rt_atan2d_snf((untitled_B.Product2 *
    untitled_B.dz - untitled_B.dy * untitled_B.Sum4) * -2.0,
    ((untitled_B.VectorConcatenate_tmp - untitled_B.VectorConcatenate_tmp_c) -
     VectorConcatenate_tmp) + VectorConcatenate_tmp_0);

  // Fcn: '<S11>/fcn3'
  untitled_B.dx = (untitled_B.Sum4 * untitled_B.dz + untitled_B.dy *
                   untitled_B.Product2) * 2.0;

  // If: '<S14>/If' incorporates:
  //   Constant: '<S15>/Constant'
  //   Constant: '<S16>/Constant'

  if (untitled_B.dx > 1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    untitled_B.dx = untitled_P.Constant_Value_ey;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S15>/Constant'

    srUpdateBC(untitled_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem'
  } else if (untitled_B.dx < -1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    untitled_B.dx = untitled_P.Constant_Value_b;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S16>/Constant'

    srUpdateBC(untitled_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S14>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S17>/Action Port'

    // Update for If: '<S14>/If'
    srUpdateBC(untitled_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem2'
  }

  // End of If: '<S14>/If'

  // Trigonometry: '<S12>/trigFcn' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'

  if (untitled_B.dx > 1.0) {
    untitled_B.dx = 1.0;
  } else if (untitled_B.dx < -1.0) {
    untitled_B.dx = -1.0;
  }

  untitled_B.VectorConcatenate[1] = asin(untitled_B.dx);

  // End of Trigonometry: '<S12>/trigFcn'

  // Trigonometry: '<S12>/Trigonometric Function3' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn4'
  //   Fcn: '<S11>/fcn5'

  untitled_B.VectorConcatenate[2] = rt_atan2d_snf((untitled_B.Sum4 *
    untitled_B.Product2 - untitled_B.dy * untitled_B.dz) * -2.0,
    ((untitled_B.VectorConcatenate_tmp + untitled_B.VectorConcatenate_tmp_c) -
     VectorConcatenate_tmp) - VectorConcatenate_tmp_0);

  // Outputs for Atomic SubSystem: '<S2>/Subscribe'
  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = Sub_untitled_22.getLatestMessage(&b_varargout_2);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    untitled_B.In1_p = b_varargout_2;
    srUpdateBC(untitled_DW.EnabledSubsystem_SubsysRanBC_o);
  }

  // End of MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S2>/Subscribe'

  // Logic: '<S5>/AND'
  rtb_AND = (untitled_B.Valid && untitled_B.In1_p.Data);

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  if (rtb_AND && (untitled_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE =
      untitled_P.DiscreteTimeIntegrator_IC;
  }

  if (untitled_DW.DiscreteTimeIntegrator_DSTATE >= untitled_P.I_max_XY) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE = untitled_P.I_max_XY;
  } else if (untitled_DW.DiscreteTimeIntegrator_DSTATE <= -untitled_P.I_max_XY)
  {
    untitled_DW.DiscreteTimeIntegrator_DSTATE = -untitled_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  untitled_B.DiscreteTimeIntegrator = untitled_DW.DiscreteTimeIntegrator_DSTATE;

  // Sum: '<S5>/Sum' incorporates:
  //   Constant: '<S5>/X_ref'

  untitled_B.dx = untitled_P.X_ref_Value - untitled_B.x;

  // Gain: '<S25>/Gain'
  untitled_B.Gain = untitled_P.Gain_Gain_j * untitled_B.dx;

  // Outputs for Atomic SubSystem: '<S4>/Subscribe'
  // MATLABSystem: '<S21>/SourceBlock'
  b_varargout_1 = Sub_untitled_50.getLatestMessage(&untitled_B.b_varargout_2_m);

  // Outputs for Enabled SubSystem: '<S21>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S22>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S22>/In1'
    untitled_B.In1_d = untitled_B.b_varargout_2_m;
    srUpdateBC(untitled_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S21>/SourceBlock'
  // End of Outputs for SubSystem: '<S21>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S4>/Subscribe'

  // Gain: '<S4>/Gain' incorporates:
  //   SignalConversion generated from: '<S4>/Bus Selector'

  untitled_B.x_d = untitled_P.Gain_Gain_n * untitled_B.In1_d.Twist.Linear.Y;

  // Gain: '<S25>/Gain2'
  untitled_B.Gain2 = untitled_P.Gain2_Gain * untitled_B.x_d;

  // Sum: '<S25>/Sum3'
  untitled_B.dy = (untitled_B.DiscreteTimeIntegrator + untitled_B.Gain) -
    untitled_B.Gain2;

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  if (rtb_AND && (untitled_DW.DiscreteTimeIntegrator_PrevRe_b <= 0)) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_n =
      untitled_P.DiscreteTimeIntegrator_IC_e;
  }

  if (untitled_DW.DiscreteTimeIntegrator_DSTATE_n >= untitled_P.I_max_XY) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_n = untitled_P.I_max_XY;
  } else if (untitled_DW.DiscreteTimeIntegrator_DSTATE_n <= -untitled_P.I_max_XY)
  {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_n = -untitled_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  untitled_B.DiscreteTimeIntegrator_p =
    untitled_DW.DiscreteTimeIntegrator_DSTATE_n;

  // Sum: '<S5>/Sum1' incorporates:
  //   Constant: '<S5>/Y_ref'

  untitled_B.dz = untitled_P.Y_ref_Value - untitled_B.X;

  // Gain: '<S26>/Gain'
  untitled_B.Gain_j = untitled_P.Gain_Gain_c * untitled_B.dz;

  // SignalConversion generated from: '<S4>/Bus Selector'
  untitled_B.X_h = untitled_B.In1_d.Twist.Linear.X;

  // Gain: '<S26>/Gain2'
  untitled_B.Gain2_m = untitled_P.Gain2_Gain_j * untitled_B.X_h;

  // Sum: '<S26>/Sum3'
  untitled_B.Product2 = (untitled_B.DiscreteTimeIntegrator_p + untitled_B.Gain_j)
    - untitled_B.Gain2_m;

  // MATLAB Function: '<S5>/MATLAB Function'
  untitled_B.VectorConcatenate_tmp = cos(untitled_B.VectorConcatenate[2]);
  untitled_B.VectorConcatenate_tmp_c = sin(untitled_B.VectorConcatenate[2]);
  untitled_B.Sum4 = -untitled_B.Product2 * untitled_B.VectorConcatenate_tmp_c -
    untitled_B.dy * untitled_B.VectorConcatenate_tmp;
  untitled_B.Product2 = -untitled_B.Product2 * untitled_B.VectorConcatenate_tmp
    + untitled_B.dy * untitled_B.VectorConcatenate_tmp_c;

  // Switch: '<S5>/Switch1'
  if (untitled_B.Valid) {
    // Switch: '<S5>/Switch1'
    untitled_B.Switch1 = untitled_B.Product2;
  } else {
    // Switch: '<S5>/Switch1' incorporates:
    //   Constant: '<S5>/Constant1'

    untitled_B.Switch1 = untitled_P.Constant1_Value;
  }

  // End of Switch: '<S5>/Switch1'

  // Saturate: '<Root>/Saturation'
  if (untitled_B.Switch1 > untitled_P.Saturation_UpperSat) {
    // Saturate: '<Root>/Saturation'
    untitled_B.Saturation = untitled_P.Saturation_UpperSat;
  } else if (untitled_B.Switch1 < untitled_P.Saturation_LowerSat) {
    // Saturate: '<Root>/Saturation'
    untitled_B.Saturation = untitled_P.Saturation_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation'
    untitled_B.Saturation = untitled_B.Switch1;
  }

  // End of Saturate: '<Root>/Saturation'

  // Sum: '<S1>/Sum' incorporates:
  //   Constant: '<S1>/Trim'
  //   Gain: '<S1>/Gain'
  //   Gain: '<S1>/Gain1'

  untitled_B.Sum = untitled_P.Gain_Gain_h * untitled_B.Saturation *
    untitled_P.Gain1_Gain + untitled_P.Trim_Value;

  // Switch: '<S5>/Switch'
  if (untitled_B.Valid) {
    // Switch: '<S5>/Switch'
    untitled_B.Switch = untitled_B.Sum4;
  } else {
    // Switch: '<S5>/Switch' incorporates:
    //   Constant: '<S5>/Constant'

    untitled_B.Switch = untitled_P.Constant_Value_f;
  }

  // End of Switch: '<S5>/Switch'

  // Saturate: '<Root>/Saturation1'
  if (untitled_B.Switch > untitled_P.Saturation1_UpperSat) {
    // Saturate: '<Root>/Saturation1'
    untitled_B.Saturation1 = untitled_P.Saturation1_UpperSat;
  } else if (untitled_B.Switch < untitled_P.Saturation1_LowerSat) {
    // Saturate: '<Root>/Saturation1'
    untitled_B.Saturation1 = untitled_P.Saturation1_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation1'
    untitled_B.Saturation1 = untitled_B.Switch;
  }

  // End of Saturate: '<Root>/Saturation1'

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Trim1'
  //   Gain: '<S1>/Gain2'
  //   Gain: '<S1>/Gain3'

  untitled_B.Sum1 = untitled_P.Gain2_Gain_je * untitled_B.Saturation1 *
    untitled_P.Gain3_Gain + untitled_P.Trim1_Value;

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  if (rtb_AND && (untitled_DW.DiscreteTimeIntegrator_PrevRe_c <= 0)) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_d =
      untitled_P.DiscreteTimeIntegrator_IC_l;
  }

  if (untitled_DW.DiscreteTimeIntegrator_DSTATE_d >= untitled_P.I_max_Z) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_d = untitled_P.I_max_Z;
  } else if (untitled_DW.DiscreteTimeIntegrator_DSTATE_d <= -untitled_P.I_max_Z)
  {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_d = -untitled_P.I_max_Z;
  }

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  untitled_B.DiscreteTimeIntegrator_n =
    untitled_DW.DiscreteTimeIntegrator_DSTATE_d;

  // Sum: '<S5>/Sum2' incorporates:
  //   Constant: '<S5>/Z_ref'

  untitled_B.dy = untitled_P.Z_ref_Value - untitled_B.Z;

  // Gain: '<S27>/Gain'
  untitled_B.Gain_n = untitled_P.Gain_Gain_d * untitled_B.dy;

  // SignalConversion generated from: '<S4>/Bus Selector'
  untitled_B.Z_n = untitled_B.In1_d.Twist.Linear.Z;

  // Gain: '<S27>/Gain2'
  untitled_B.Gain2_g = untitled_P.Gain2_Gain_b * untitled_B.Z_n;

  // MATLAB Function: '<S5>/MATLAB Function1'
  untitled_B.Sum4 = 0.5 * untitled_B.VectorConcatenate[1] + 0.5 *
    untitled_B.Sum4;
  untitled_cosd(&untitled_B.Sum4);
  untitled_B.Product2 = 0.5 * untitled_B.VectorConcatenate[0] + 0.5 *
    untitled_B.Product2;
  untitled_cosd(&untitled_B.Product2);

  // Switch: '<S5>/Switch2'
  if (untitled_B.Valid) {
    // Switch: '<S5>/Switch2' incorporates:
    //   MATLAB Function: '<S5>/MATLAB Function1'
    //   Sum: '<S27>/Sum3'

    untitled_B.Switch2 = ((untitled_B.DiscreteTimeIntegrator_n +
      untitled_B.Gain_n) - untitled_B.Gain2_g) / untitled_B.Sum4 /
      untitled_B.Product2;
  } else {
    // Switch: '<S5>/Switch2' incorporates:
    //   Constant: '<S5>/Constant2'

    untitled_B.Switch2 = untitled_P.Constant2_Value;
  }

  // End of Switch: '<S5>/Switch2'

  // Saturate: '<Root>/Saturation2'
  if (untitled_B.Switch2 > untitled_P.Saturation2_UpperSat) {
    // Saturate: '<Root>/Saturation2'
    untitled_B.Saturation2 = untitled_P.Saturation2_UpperSat;
  } else if (untitled_B.Switch2 < untitled_P.Saturation2_LowerSat) {
    // Saturate: '<Root>/Saturation2'
    untitled_B.Saturation2 = untitled_P.Saturation2_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation2'
    untitled_B.Saturation2 = untitled_B.Switch2;
  }

  // End of Saturate: '<Root>/Saturation2'

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.Sum4 = floor(untitled_B.Sum);
  if (rtIsNaN(untitled_B.Sum4) || rtIsInf(untitled_B.Sum4)) {
    untitled_B.Sum4 = 0.0;
  } else {
    untitled_B.Sum4 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[0] = static_cast<uint16_T>(untitled_B.Sum4 < 0.0
    ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.Sum4 = floor(untitled_B.Sum1);
  if (rtIsNaN(untitled_B.Sum4) || rtIsInf(untitled_B.Sum4)) {
    untitled_B.Sum4 = 0.0;
  } else {
    untitled_B.Sum4 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[1] = static_cast<uint16_T>(untitled_B.Sum4 < 0.0
    ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S1>/Thrust for hover'
  //   Gain: '<S1>/From motor test stand'
  //   Sum: '<S1>/Sum4'

  untitled_B.Sum4 = floor(untitled_P.Frommotorteststand_Gain *
    untitled_B.Saturation2 + untitled_P.MOT_THST_HOVER_MCS);
  if (rtIsNaN(untitled_B.Sum4) || rtIsInf(untitled_B.Sum4)) {
    untitled_B.Sum4 = 0.0;
  } else {
    untitled_B.Sum4 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[2] = static_cast<uint16_T>(untitled_B.Sum4 < 0.0
    ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Zero2'

  untitled_B.Sum4 = floor(untitled_P.Zero2_Value);
  if (rtIsNaN(untitled_B.Sum4) || rtIsInf(untitled_B.Sum4)) {
    untitled_B.Sum4 = 0.0;
  } else {
    untitled_B.Sum4 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[3] = static_cast<uint16_T>(untitled_B.Sum4 < 0.0
    ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero'

  untitled_B.Sum4 = floor(untitled_P.Zero_Value);
  b_varargout_1 = rtIsNaN(untitled_B.Sum4);
  tmp = rtIsInf(untitled_B.Sum4);
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[4] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Flight Mode'

  untitled_B.Product2 = floor(untitled_P.STABILIZE);
  if (rtIsNaN(untitled_B.Product2) || rtIsInf(untitled_B.Product2)) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Product2, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[5] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[6] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[7] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[8] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[9] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[10] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[11] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[12] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  untitled_B.DataTypeConversion[13] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    untitled_B.Product2 = 0.0;
    untitled_B.Sum4 = 0.0;
  } else {
    untitled_B.Product2 = fmod(untitled_B.Sum4, 65536.0);
    untitled_B.Sum4 = untitled_B.Product2;
  }

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero3'

  untitled_B.DataTypeConversion[14] = static_cast<uint16_T>(untitled_B.Product2 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Product2)));
  untitled_B.DataTypeConversion[15] = static_cast<uint16_T>(untitled_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-untitled_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(untitled_B.Sum4)));
  for (i = 0; i < 112; i++) {
    untitled_B.Sum4 = floor(untitled_P.Zero3_Value[i]);
    if (rtIsNaN(untitled_B.Sum4) || rtIsInf(untitled_B.Sum4)) {
      untitled_B.Sum4 = 0.0;
    } else {
      untitled_B.Sum4 = fmod(untitled_B.Sum4, 65536.0);
    }

    untitled_B.DataTypeConversion[i + 16] = static_cast<uint16_T>
      (untitled_B.Sum4 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
         static_cast<int16_T>(static_cast<uint16_T>(-untitled_B.Sum4)))) :
       static_cast<int32_T>(static_cast<uint16_T>(untitled_B.Sum4)));
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   Constant: '<S30>/Constant'

  untitled_B.BusAssignment4 = untitled_P.Constant_Value;
  memcpy(&untitled_B.BusAssignment4.Data[0], &untitled_B.DataTypeConversion[0],
         sizeof(uint16_T) << 7U);

  // DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
  //   Constant: '<S6>/Constant'

  untitled_B.Sum4 = floor(untitled_P.Constant_Value_n);
  if (rtIsNaN(untitled_B.Sum4) || rtIsInf(untitled_B.Sum4)) {
    untitled_B.Sum4 = 0.0;
  } else {
    untitled_B.Sum4 = fmod(untitled_B.Sum4, 4.294967296E+9);
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   DataTypeConversion: '<S6>/Data Type Conversion1'

  untitled_B.BusAssignment4.Data_SL_Info.CurrentLength = untitled_B.Sum4 < 0.0 ?
    static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>
    (-untitled_B.Sum4))) : static_cast<uint32_T>(untitled_B.Sum4);

  // Outputs for Atomic SubSystem: '<S6>/Publish'
  // MATLABSystem: '<S31>/SinkBlock'
  Pub_untitled_183.publish(&untitled_B.BusAssignment4);

  // End of Outputs for SubSystem: '<S6>/Publish'
  // S-Function (saeroclockpacer): '<Root>/Simulation Pace'
  //
  //  The Clock Pacer generates no code, it is only active in
  //  interpreted simulation.


  // Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S25>/Gain1'

  untitled_DW.DiscreteTimeIntegrator_DSTATE += untitled_P.Gain1_Gain_jk *
    untitled_B.dx * untitled_P.DiscreteTimeIntegrator_gainval;
  if (untitled_DW.DiscreteTimeIntegrator_DSTATE >= untitled_P.I_max_XY) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE = untitled_P.I_max_XY;
  } else if (untitled_DW.DiscreteTimeIntegrator_DSTATE <= -untitled_P.I_max_XY)
  {
    untitled_DW.DiscreteTimeIntegrator_DSTATE = -untitled_P.I_max_XY;
  }

  untitled_DW.DiscreteTimeIntegrator_PrevRese = static_cast<int8_T>(rtb_AND);

  // Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S26>/Gain1'

  untitled_DW.DiscreteTimeIntegrator_DSTATE_n += untitled_P.Gain1_Gain_jc *
    untitled_B.dz * untitled_P.DiscreteTimeIntegrator_gainva_g;
  if (untitled_DW.DiscreteTimeIntegrator_DSTATE_n >= untitled_P.I_max_XY) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_n = untitled_P.I_max_XY;
  } else if (untitled_DW.DiscreteTimeIntegrator_DSTATE_n <= -untitled_P.I_max_XY)
  {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_n = -untitled_P.I_max_XY;
  }

  untitled_DW.DiscreteTimeIntegrator_PrevRe_b = static_cast<int8_T>(rtb_AND);

  // End of Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S27>/Gain1'

  untitled_DW.DiscreteTimeIntegrator_DSTATE_d += untitled_P.Gain1_Gain_j *
    untitled_B.dy * untitled_P.DiscreteTimeIntegrator_gainva_k;
  if (untitled_DW.DiscreteTimeIntegrator_DSTATE_d >= untitled_P.I_max_Z) {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_d = untitled_P.I_max_Z;
  } else if (untitled_DW.DiscreteTimeIntegrator_DSTATE_d <= -untitled_P.I_max_Z)
  {
    untitled_DW.DiscreteTimeIntegrator_DSTATE_d = -untitled_P.I_max_Z;
  }

  untitled_DW.DiscreteTimeIntegrator_PrevRe_c = static_cast<int8_T>(rtb_AND);

  // End of Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator'

  // External mode
  rtExtModeUploadCheckTrigger(1);

  {                                    // Sample time: [0.0125s, 0.0s]
    rtExtModeUpload(0, (real_T)untitled_M->Timing.taskTime0);
  }

  // signal main to stop simulation
  {                                    // Sample time: [0.0125s, 0.0s]
    if ((rtmGetTFinal(untitled_M)!=-1) &&
        !((rtmGetTFinal(untitled_M)-untitled_M->Timing.taskTime0) >
          untitled_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }

    if (rtmGetStopRequested(untitled_M)) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  untitled_M->Timing.taskTime0 =
    ((time_T)(++untitled_M->Timing.clockTick0)) * untitled_M->Timing.stepSize0;
}

// Model initialize function
void untitled_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(untitled_M, -1);
  untitled_M->Timing.stepSize0 = 0.0125;

  // External mode info
  untitled_M->Sizes.checksums[0] = (1420221968U);
  untitled_M->Sizes.checksums[1] = (3695731065U);
  untitled_M->Sizes.checksums[2] = (2767391140U);
  untitled_M->Sizes.checksums[3] = (1544940774U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[22];
    untitled_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&untitled_DW.EnabledSubsystem_SubsysRanBC_o;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = (sysRanDType *)&untitled_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[5] = (sysRanDType *)&untitled_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[6] = (sysRanDType *)&untitled_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[7] = (sysRanDType *)&untitled_DW.EnabledSubsystem_SubsysRanBC_d;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = (sysRanDType *)&untitled_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[11] = &rtAlwaysEnabled;
    systemRan[12] = &rtAlwaysEnabled;
    systemRan[13] = &rtAlwaysEnabled;
    systemRan[14] = &rtAlwaysEnabled;
    systemRan[15] = &rtAlwaysEnabled;
    systemRan[16] = &rtAlwaysEnabled;
    systemRan[17] = &rtAlwaysEnabled;
    systemRan[18] = &rtAlwaysEnabled;
    systemRan[19] = &rtAlwaysEnabled;
    systemRan[20] = &rtAlwaysEnabled;
    systemRan[21] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(untitled_M->extModeInfo,
      &untitled_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(untitled_M->extModeInfo, untitled_M->Sizes.checksums);
    rteiSetTPtr(untitled_M->extModeInfo, rtmGetTPtr(untitled_M));
  }

  // data type transition information
  {
    static DataTypeTransInfo dtInfo;
    untitled_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 35;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    // Block I/O transition table
    dtInfo.BTransTable = &rtBTransTable;

    // Parameters transition table
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    char_T b_zeroDelimTopic[28];
    char_T b_zeroDelimTopic_0[17];
    char_T b_zeroDelimTopic_1[14];
    static const char_T tmp[27] = { '/', 'v', 'r', 'p', 'n', '_', 'c', 'l', 'i',
      'e', 'n', 't', '_', 'n', 'o', 'd', 'e', '/', 'Q', 'u', 'a', 'd', '/', 'p',
      'o', 's', 'e' };

    static const char_T tmp_0[16] = { '/', 'a', 'u', 't', 'o', 'n', 'o', 'm',
      'y', '_', 'e', 'n', 'a', 'b', 'l', 'e' };

    static const char_T tmp_1[39] = { '/', 'v', 'r', 'p', 'n', '_', 'v', 'e',
      'l', 'o', 'c', 'i', 't', 'y', '/', 'o', 'p', 't', 'i', 't', 'r', 'a', 'c',
      'k', '_', 'f', 'r', 'a', 'm', 'e', '/', 'f', 'i', 'l', 't', 'e', 'r', 'e',
      'd' };

    static const char_T tmp_2[13] = { 'q', 'u', 'a', 'd', '_', 'c', 'o', 'm',
      'm', 'a', 'n', 'd', 's' };

    // InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' 
    untitled_DW.DiscreteTimeIntegrator_DSTATE =
      untitled_P.DiscreteTimeIntegrator_IC;
    untitled_DW.DiscreteTimeIntegrator_PrevRese = 2;

    // InitializeConditions for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' 
    untitled_DW.DiscreteTimeIntegrator_DSTATE_n =
      untitled_P.DiscreteTimeIntegrator_IC_e;
    untitled_DW.DiscreteTimeIntegrator_PrevRe_b = 2;

    // InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' 
    untitled_DW.DiscreteTimeIntegrator_DSTATE_d =
      untitled_P.DiscreteTimeIntegrator_IC_l;
    untitled_DW.DiscreteTimeIntegrator_PrevRe_c = 2;

    // SystemInitialize for Atomic SubSystem: '<S3>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S10>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S20>/In1' incorporates:
    //   Outport: '<S20>/Out1'

    untitled_B.In1 = untitled_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S10>/Enabled Subsystem'

    // Start for MATLABSystem: '<S10>/SourceBlock'
    untitled_DW.obj_k.matlabCodegenIsDeleted = false;
    untitled_DW.obj_k.isInitialized = 1;
    for (int32_T i = 0; i < 27; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[27] = '\x00';
    Sub_untitled_39.createSubscriber(&b_zeroDelimTopic[0], 1);
    untitled_DW.obj_k.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S10>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S3>/Subscribe'

    // SystemInitialize for MATLAB Function: '<S28>/MATLAB Function'
    untitled_DW.idx = 1U;

    // SystemInitialize for Atomic SubSystem: '<S2>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S8>/In1' incorporates:
    //   Outport: '<S8>/Out1'

    untitled_B.In1_p = untitled_P.Out1_Y0_k;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'

    // Start for MATLABSystem: '<S7>/SourceBlock'
    untitled_DW.obj_d.matlabCodegenIsDeleted = false;
    untitled_DW.obj_d.isInitialized = 1;
    for (int32_T i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[16] = '\x00';
    Sub_untitled_22.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    untitled_DW.obj_d.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S2>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S4>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S21>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S22>/In1' incorporates:
    //   Outport: '<S22>/Out1'

    untitled_B.In1_d = untitled_P.Out1_Y0_e;

    // End of SystemInitialize for SubSystem: '<S21>/Enabled Subsystem'

    // Start for MATLABSystem: '<S21>/SourceBlock'
    untitled_DW.obj.matlabCodegenIsDeleted = false;
    untitled_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 39; i++) {
      untitled_B.b_zeroDelimTopic[i] = tmp_1[i];
    }

    untitled_B.b_zeroDelimTopic[39] = '\x00';
    Sub_untitled_50.createSubscriber(&untitled_B.b_zeroDelimTopic[0], 1);
    untitled_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S21>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S4>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S6>/Publish'
    // Start for MATLABSystem: '<S31>/SinkBlock'
    untitled_DW.obj_n.matlabCodegenIsDeleted = false;
    untitled_DW.obj_n.isInitialized = 1;
    for (int32_T i = 0; i < 13; i++) {
      b_zeroDelimTopic_1[i] = tmp_2[i];
    }

    b_zeroDelimTopic_1[13] = '\x00';
    Pub_untitled_183.createPublisher(&b_zeroDelimTopic_1[0], 1);
    untitled_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S31>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<S6>/Publish'
  }
}

// Model terminate function
void untitled_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S3>/Subscribe'
  // Terminate for MATLABSystem: '<S10>/SourceBlock'
  if (!untitled_DW.obj_k.matlabCodegenIsDeleted) {
    untitled_DW.obj_k.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S10>/SourceBlock'
  // End of Terminate for SubSystem: '<S3>/Subscribe'

  // Terminate for Atomic SubSystem: '<S2>/Subscribe'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!untitled_DW.obj_d.matlabCodegenIsDeleted) {
    untitled_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'
  // End of Terminate for SubSystem: '<S2>/Subscribe'

  // Terminate for Atomic SubSystem: '<S4>/Subscribe'
  // Terminate for MATLABSystem: '<S21>/SourceBlock'
  if (!untitled_DW.obj.matlabCodegenIsDeleted) {
    untitled_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S21>/SourceBlock'
  // End of Terminate for SubSystem: '<S4>/Subscribe'

  // Terminate for Atomic SubSystem: '<S6>/Publish'
  // Terminate for MATLABSystem: '<S31>/SinkBlock'
  if (!untitled_DW.obj_n.matlabCodegenIsDeleted) {
    untitled_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S31>/SinkBlock'
  // End of Terminate for SubSystem: '<S6>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
