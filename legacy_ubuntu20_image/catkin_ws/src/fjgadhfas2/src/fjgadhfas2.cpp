//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: fjgadhfas2.cpp
//
// Code generated for Simulink model 'fjgadhfas2'.
//
// Model version                  : 1.2
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Jan 15 18:30:43 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "fjgadhfas2.h"
#include "rtwtypes.h"
#include <math.h>
#include "fjgadhfas2_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>
#include "fjgadhfas2_types.h"
#include "rt_defines.h"
#include <float.h>
#include "fjgadhfas2_dt.h"

// Block signals (default storage)
B_fjgadhfas2_T fjgadhfas2_B;

// Block states (default storage)
DW_fjgadhfas2_T fjgadhfas2_DW;

// Real-time model
RT_MODEL_fjgadhfas2_T fjgadhfas2_M_ = RT_MODEL_fjgadhfas2_T();
RT_MODEL_fjgadhfas2_T *const fjgadhfas2_M = &fjgadhfas2_M_;

// Forward declaration for local functions
static void fjgadhfas2_cosd(real_T *x);
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
static void fjgadhfas2_cosd(real_T *x)
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
void fjgadhfas2_step(void)
{
  SL_Bus_fjgadhfas2_std_msgs_Bool b_varargout_2;
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_0;
  int32_T i;
  boolean_T b_varargout_1;
  boolean_T rtb_AND;
  boolean_T tmp;

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC_o);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas2_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas2_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas2_DW.IfActionSubsystem2_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC_d);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC);

  // Outputs for Atomic SubSystem: '<S3>/Subscribe'
  // MATLABSystem: '<S10>/SourceBlock'
  b_varargout_1 = Sub_fjgadhfas2_39.getLatestMessage(&fjgadhfas2_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S20>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S20>/In1'
    fjgadhfas2_B.In1 = fjgadhfas2_B.b_varargout_2;
    srUpdateBC(fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC_d);
  }

  // End of MATLABSystem: '<S10>/SourceBlock'
  // End of Outputs for SubSystem: '<S10>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S3>/Subscribe'

  // Gain: '<S3>/Gain'
  fjgadhfas2_B.x = fjgadhfas2_P.Gain_Gain * fjgadhfas2_B.In1.Pose.Position.Y;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  fjgadhfas2_B.X = fjgadhfas2_B.In1.Pose.Position.X;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  fjgadhfas2_B.Z = fjgadhfas2_B.In1.Pose.Position.Z;

  // MATLAB Function: '<S28>/MATLAB Function' incorporates:
  //   Constant: '<S28>/Constant'

  if (fjgadhfas2_DW.filled == 0) {
    fjgadhfas2_DW.bufX[fjgadhfas2_DW.idx - 1] = fjgadhfas2_B.x;
    fjgadhfas2_DW.bufY[fjgadhfas2_DW.idx - 1] = fjgadhfas2_B.X;
    fjgadhfas2_DW.bufZ[fjgadhfas2_DW.idx - 1] = fjgadhfas2_B.Z;
    fjgadhfas2_DW.filled = 1U;
    fjgadhfas2_DW.idx = 2U;
    fjgadhfas2_B.Valid = true;
    fjgadhfas2_B.frozenNow = false;
    fjgadhfas2_B.filled_ = 0U;
    fjgadhfas2_B.updated = false;
    fjgadhfas2_B.d = -1.0;
    fjgadhfas2_B.v = -1.0;
  } else {
    uint32_T qY;
    uint8_T prevIdx;
    qY = fjgadhfas2_DW.idx - 1U;
    if (fjgadhfas2_DW.idx - 1U > fjgadhfas2_DW.idx) {
      qY = 0U;
    }

    prevIdx = static_cast<uint8_T>(qY);
    if (static_cast<uint8_T>(qY) == 0) {
      prevIdx = 11U;
    }

    fjgadhfas2_B.dx = fjgadhfas2_B.x - fjgadhfas2_DW.bufX[prevIdx - 1];
    fjgadhfas2_B.dy = fjgadhfas2_B.X - fjgadhfas2_DW.bufY[prevIdx - 1];
    fjgadhfas2_B.dz = fjgadhfas2_B.Z - fjgadhfas2_DW.bufZ[prevIdx - 1];
    fjgadhfas2_B.d = sqrt((fjgadhfas2_B.dx * fjgadhfas2_B.dx + fjgadhfas2_B.dy *
      fjgadhfas2_B.dy) + fjgadhfas2_B.dz * fjgadhfas2_B.dz);
    fjgadhfas2_B.v = fjgadhfas2_B.d / fjgadhfas2_P.time_step;
    fjgadhfas2_B.updated = (fjgadhfas2_B.d > 1.0E-6);
    fjgadhfas2_B.frozenNow = false;
    if (fjgadhfas2_DW.filled >= 11) {
      boolean_T exitg1;
      fjgadhfas2_B.frozenNow = true;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 10)) {
        int32_T ddx_tmp_tmp;
        ddx_tmp_tmp = prevIdx - 1;
        fjgadhfas2_B.dx = fjgadhfas2_B.x - fjgadhfas2_DW.bufX[prevIdx - 1];
        fjgadhfas2_B.dy = fjgadhfas2_B.X - fjgadhfas2_DW.bufY[prevIdx - 1];
        fjgadhfas2_B.dz = fjgadhfas2_B.Z - fjgadhfas2_DW.bufZ[prevIdx - 1];
        if (sqrt((fjgadhfas2_B.dx * fjgadhfas2_B.dx + fjgadhfas2_B.dy *
                  fjgadhfas2_B.dy) + fjgadhfas2_B.dz * fjgadhfas2_B.dz) > 1.0E-6)
        {
          fjgadhfas2_B.frozenNow = false;
          exitg1 = true;
        } else {
          prevIdx = static_cast<uint8_T>(prevIdx - 1);
          if (static_cast<uint8_T>(ddx_tmp_tmp) == 0) {
            prevIdx = 11U;
          }

          i++;
        }
      }
    }

    if (!fjgadhfas2_DW.inLost) {
      if ((fjgadhfas2_B.v > 20.0) || fjgadhfas2_B.frozenNow) {
        fjgadhfas2_DW.inLost = true;
        fjgadhfas2_DW.goodCnt = 0U;
        fjgadhfas2_B.Valid = false;
      } else {
        fjgadhfas2_B.Valid = true;
      }
    } else if (fjgadhfas2_B.updated && (fjgadhfas2_B.v <= 20.0)) {
      if (fjgadhfas2_DW.goodCnt < 255) {
        fjgadhfas2_DW.goodCnt = static_cast<uint8_T>(fjgadhfas2_DW.goodCnt + 1U);
      }

      if (fjgadhfas2_DW.goodCnt >= 5) {
        fjgadhfas2_DW.inLost = false;
        fjgadhfas2_DW.goodCnt = 0U;
        fjgadhfas2_B.Valid = true;
      } else {
        fjgadhfas2_B.Valid = false;
      }
    } else {
      if (fjgadhfas2_B.v > 20.0) {
        fjgadhfas2_DW.goodCnt = 0U;
      }

      fjgadhfas2_B.Valid = false;
    }

    fjgadhfas2_DW.bufX[fjgadhfas2_DW.idx - 1] = fjgadhfas2_B.x;
    fjgadhfas2_DW.bufY[fjgadhfas2_DW.idx - 1] = fjgadhfas2_B.X;
    fjgadhfas2_DW.bufZ[fjgadhfas2_DW.idx - 1] = fjgadhfas2_B.Z;
    if (fjgadhfas2_DW.filled < 11) {
      fjgadhfas2_DW.filled = static_cast<uint8_T>(fjgadhfas2_DW.filled + 1U);
    }

    i = static_cast<int32_T>(fjgadhfas2_DW.idx + 1U);
    if (fjgadhfas2_DW.idx + 1U > 255U) {
      i = 255;
    }

    fjgadhfas2_DW.idx = static_cast<uint8_T>(i);
    if (fjgadhfas2_DW.idx > 11) {
      fjgadhfas2_DW.idx = 1U;
    }

    fjgadhfas2_B.filled_ = fjgadhfas2_DW.filled;
  }

  // End of MATLAB Function: '<S28>/MATLAB Function'

  // Sqrt: '<S18>/sqrt' incorporates:
  //   Product: '<S19>/Product'
  //   Product: '<S19>/Product1'
  //   Product: '<S19>/Product2'
  //   Product: '<S19>/Product3'
  //   Sum: '<S19>/Sum'

  fjgadhfas2_B.dz = sqrt(((fjgadhfas2_B.In1.Pose.Orientation.W *
    fjgadhfas2_B.In1.Pose.Orientation.W + fjgadhfas2_B.In1.Pose.Orientation.X *
    fjgadhfas2_B.In1.Pose.Orientation.X) + fjgadhfas2_B.In1.Pose.Orientation.Y *
    fjgadhfas2_B.In1.Pose.Orientation.Y) + fjgadhfas2_B.In1.Pose.Orientation.Z *
    fjgadhfas2_B.In1.Pose.Orientation.Z);

  // Product: '<S13>/Product'
  fjgadhfas2_B.dy = fjgadhfas2_B.In1.Pose.Orientation.W / fjgadhfas2_B.dz;

  // Product: '<S13>/Product1'
  fjgadhfas2_B.Sum4 = fjgadhfas2_B.In1.Pose.Orientation.X / fjgadhfas2_B.dz;

  // Product: '<S13>/Product2'
  fjgadhfas2_B.Product2 = fjgadhfas2_B.In1.Pose.Orientation.Y / fjgadhfas2_B.dz;

  // Product: '<S13>/Product3'
  fjgadhfas2_B.dz = fjgadhfas2_B.In1.Pose.Orientation.Z / fjgadhfas2_B.dz;

  // Fcn: '<S11>/fcn2' incorporates:
  //   Fcn: '<S11>/fcn5'

  fjgadhfas2_B.VectorConcatenate_tmp = fjgadhfas2_B.dy * fjgadhfas2_B.dy;
  fjgadhfas2_B.VectorConcatenate_tmp_c = fjgadhfas2_B.Sum4 * fjgadhfas2_B.Sum4;
  VectorConcatenate_tmp = fjgadhfas2_B.Product2 * fjgadhfas2_B.Product2;
  VectorConcatenate_tmp_0 = fjgadhfas2_B.dz * fjgadhfas2_B.dz;

  // Trigonometry: '<S12>/Trigonometric Function1' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn1'
  //   Fcn: '<S11>/fcn2'

  fjgadhfas2_B.VectorConcatenate[0] = rt_atan2d_snf((fjgadhfas2_B.Product2 *
    fjgadhfas2_B.dz - fjgadhfas2_B.dy * fjgadhfas2_B.Sum4) * -2.0,
    ((fjgadhfas2_B.VectorConcatenate_tmp - fjgadhfas2_B.VectorConcatenate_tmp_c)
     - VectorConcatenate_tmp) + VectorConcatenate_tmp_0);

  // Fcn: '<S11>/fcn3'
  fjgadhfas2_B.dx = (fjgadhfas2_B.Sum4 * fjgadhfas2_B.dz + fjgadhfas2_B.dy *
                     fjgadhfas2_B.Product2) * 2.0;

  // If: '<S14>/If' incorporates:
  //   Constant: '<S15>/Constant'
  //   Constant: '<S16>/Constant'

  if (fjgadhfas2_B.dx > 1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    fjgadhfas2_B.dx = fjgadhfas2_P.Constant_Value_ey;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S15>/Constant'

    srUpdateBC(fjgadhfas2_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem'
  } else if (fjgadhfas2_B.dx < -1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    fjgadhfas2_B.dx = fjgadhfas2_P.Constant_Value_b;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S16>/Constant'

    srUpdateBC(fjgadhfas2_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S14>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S17>/Action Port'

    // Update for If: '<S14>/If'
    srUpdateBC(fjgadhfas2_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem2'
  }

  // End of If: '<S14>/If'

  // Trigonometry: '<S12>/trigFcn' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'

  if (fjgadhfas2_B.dx > 1.0) {
    fjgadhfas2_B.dx = 1.0;
  } else if (fjgadhfas2_B.dx < -1.0) {
    fjgadhfas2_B.dx = -1.0;
  }

  fjgadhfas2_B.VectorConcatenate[1] = asin(fjgadhfas2_B.dx);

  // End of Trigonometry: '<S12>/trigFcn'

  // Trigonometry: '<S12>/Trigonometric Function3' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn4'
  //   Fcn: '<S11>/fcn5'

  fjgadhfas2_B.VectorConcatenate[2] = rt_atan2d_snf((fjgadhfas2_B.Sum4 *
    fjgadhfas2_B.Product2 - fjgadhfas2_B.dy * fjgadhfas2_B.dz) * -2.0,
    ((fjgadhfas2_B.VectorConcatenate_tmp + fjgadhfas2_B.VectorConcatenate_tmp_c)
     - VectorConcatenate_tmp) - VectorConcatenate_tmp_0);

  // Outputs for Atomic SubSystem: '<S2>/Subscribe'
  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = Sub_fjgadhfas2_22.getLatestMessage(&b_varargout_2);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    fjgadhfas2_B.In1_p = b_varargout_2;
    srUpdateBC(fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC_o);
  }

  // End of MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S2>/Subscribe'

  // Logic: '<S5>/AND'
  rtb_AND = (fjgadhfas2_B.Valid && fjgadhfas2_B.In1_p.Data);

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  if (rtb_AND && (fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE =
      fjgadhfas2_P.DiscreteTimeIntegrator_IC;
  }

  if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE >= fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE = fjgadhfas2_P.I_max_XY;
  } else if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE <=
             -fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE = -fjgadhfas2_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  fjgadhfas2_B.DiscreteTimeIntegrator =
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE;

  // Sum: '<S5>/Sum' incorporates:
  //   Constant: '<S5>/X_ref'

  fjgadhfas2_B.dx = fjgadhfas2_P.X_ref_Value - fjgadhfas2_B.x;

  // Gain: '<S25>/Gain'
  fjgadhfas2_B.Gain = fjgadhfas2_P.Gain_Gain_j * fjgadhfas2_B.dx;

  // Outputs for Atomic SubSystem: '<S4>/Subscribe'
  // MATLABSystem: '<S21>/SourceBlock'
  b_varargout_1 = Sub_fjgadhfas2_50.getLatestMessage
    (&fjgadhfas2_B.b_varargout_2_m);

  // Outputs for Enabled SubSystem: '<S21>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S22>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S22>/In1'
    fjgadhfas2_B.In1_d = fjgadhfas2_B.b_varargout_2_m;
    srUpdateBC(fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S21>/SourceBlock'
  // End of Outputs for SubSystem: '<S21>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S4>/Subscribe'

  // Gain: '<S4>/Gain' incorporates:
  //   SignalConversion generated from: '<S4>/Bus Selector'

  fjgadhfas2_B.x_d = fjgadhfas2_P.Gain_Gain_n *
    fjgadhfas2_B.In1_d.Twist.Linear.Y;

  // Gain: '<S25>/Gain2'
  fjgadhfas2_B.Gain2 = fjgadhfas2_P.Gain2_Gain * fjgadhfas2_B.x_d;

  // Sum: '<S25>/Sum3'
  fjgadhfas2_B.dy = (fjgadhfas2_B.DiscreteTimeIntegrator + fjgadhfas2_B.Gain) -
    fjgadhfas2_B.Gain2;

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  if (rtb_AND && (fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRe_b <= 0)) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n =
      fjgadhfas2_P.DiscreteTimeIntegrator_IC_e;
  }

  if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n >= fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n = fjgadhfas2_P.I_max_XY;
  } else if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n <=
             -fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n = -fjgadhfas2_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  fjgadhfas2_B.DiscreteTimeIntegrator_p =
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n;

  // Sum: '<S5>/Sum1' incorporates:
  //   Constant: '<S5>/Y_ref'

  fjgadhfas2_B.dz = fjgadhfas2_P.Y_ref_Value - fjgadhfas2_B.X;

  // Gain: '<S26>/Gain'
  fjgadhfas2_B.Gain_j = fjgadhfas2_P.Gain_Gain_c * fjgadhfas2_B.dz;

  // SignalConversion generated from: '<S4>/Bus Selector'
  fjgadhfas2_B.X_h = fjgadhfas2_B.In1_d.Twist.Linear.X;

  // Gain: '<S26>/Gain2'
  fjgadhfas2_B.Gain2_m = fjgadhfas2_P.Gain2_Gain_j * fjgadhfas2_B.X_h;

  // Sum: '<S26>/Sum3'
  fjgadhfas2_B.Product2 = (fjgadhfas2_B.DiscreteTimeIntegrator_p +
    fjgadhfas2_B.Gain_j) - fjgadhfas2_B.Gain2_m;

  // MATLAB Function: '<S5>/MATLAB Function'
  fjgadhfas2_B.VectorConcatenate_tmp = cos(fjgadhfas2_B.VectorConcatenate[2]);
  fjgadhfas2_B.VectorConcatenate_tmp_c = sin(fjgadhfas2_B.VectorConcatenate[2]);
  fjgadhfas2_B.Sum4 = -fjgadhfas2_B.Product2 *
    fjgadhfas2_B.VectorConcatenate_tmp_c - fjgadhfas2_B.dy *
    fjgadhfas2_B.VectorConcatenate_tmp;
  fjgadhfas2_B.Product2 = -fjgadhfas2_B.Product2 *
    fjgadhfas2_B.VectorConcatenate_tmp + fjgadhfas2_B.dy *
    fjgadhfas2_B.VectorConcatenate_tmp_c;

  // Switch: '<S5>/Switch1'
  if (fjgadhfas2_B.Valid) {
    // Switch: '<S5>/Switch1'
    fjgadhfas2_B.Switch1 = fjgadhfas2_B.Product2;
  } else {
    // Switch: '<S5>/Switch1' incorporates:
    //   Constant: '<S5>/Constant1'

    fjgadhfas2_B.Switch1 = fjgadhfas2_P.Constant1_Value;
  }

  // End of Switch: '<S5>/Switch1'

  // Saturate: '<Root>/Saturation'
  if (fjgadhfas2_B.Switch1 > fjgadhfas2_P.Saturation_UpperSat) {
    // Saturate: '<Root>/Saturation'
    fjgadhfas2_B.Saturation = fjgadhfas2_P.Saturation_UpperSat;
  } else if (fjgadhfas2_B.Switch1 < fjgadhfas2_P.Saturation_LowerSat) {
    // Saturate: '<Root>/Saturation'
    fjgadhfas2_B.Saturation = fjgadhfas2_P.Saturation_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation'
    fjgadhfas2_B.Saturation = fjgadhfas2_B.Switch1;
  }

  // End of Saturate: '<Root>/Saturation'

  // Sum: '<S1>/Sum' incorporates:
  //   Constant: '<S1>/Trim'
  //   Gain: '<S1>/Gain'
  //   Gain: '<S1>/Gain1'

  fjgadhfas2_B.Sum = fjgadhfas2_P.Gain_Gain_h * fjgadhfas2_B.Saturation *
    fjgadhfas2_P.Gain1_Gain + fjgadhfas2_P.Trim_Value;

  // Switch: '<S5>/Switch'
  if (fjgadhfas2_B.Valid) {
    // Switch: '<S5>/Switch'
    fjgadhfas2_B.Switch = fjgadhfas2_B.Sum4;
  } else {
    // Switch: '<S5>/Switch' incorporates:
    //   Constant: '<S5>/Constant'

    fjgadhfas2_B.Switch = fjgadhfas2_P.Constant_Value_f;
  }

  // End of Switch: '<S5>/Switch'

  // Saturate: '<Root>/Saturation1'
  if (fjgadhfas2_B.Switch > fjgadhfas2_P.Saturation1_UpperSat) {
    // Saturate: '<Root>/Saturation1'
    fjgadhfas2_B.Saturation1 = fjgadhfas2_P.Saturation1_UpperSat;
  } else if (fjgadhfas2_B.Switch < fjgadhfas2_P.Saturation1_LowerSat) {
    // Saturate: '<Root>/Saturation1'
    fjgadhfas2_B.Saturation1 = fjgadhfas2_P.Saturation1_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation1'
    fjgadhfas2_B.Saturation1 = fjgadhfas2_B.Switch;
  }

  // End of Saturate: '<Root>/Saturation1'

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Trim1'
  //   Gain: '<S1>/Gain2'
  //   Gain: '<S1>/Gain3'

  fjgadhfas2_B.Sum1 = fjgadhfas2_P.Gain2_Gain_je * fjgadhfas2_B.Saturation1 *
    fjgadhfas2_P.Gain3_Gain + fjgadhfas2_P.Trim1_Value;

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  if (rtb_AND && (fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRe_c <= 0)) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d =
      fjgadhfas2_P.DiscreteTimeIntegrator_IC_l;
  }

  if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d >= fjgadhfas2_P.I_max_Z) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d = fjgadhfas2_P.I_max_Z;
  } else if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d <=
             -fjgadhfas2_P.I_max_Z) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d = -fjgadhfas2_P.I_max_Z;
  }

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  fjgadhfas2_B.DiscreteTimeIntegrator_n =
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d;

  // Sum: '<S5>/Sum2' incorporates:
  //   Constant: '<S5>/Z_ref'

  fjgadhfas2_B.dy = fjgadhfas2_P.Z_ref_Value - fjgadhfas2_B.Z;

  // Gain: '<S27>/Gain'
  fjgadhfas2_B.Gain_n = fjgadhfas2_P.Gain_Gain_d * fjgadhfas2_B.dy;

  // SignalConversion generated from: '<S4>/Bus Selector'
  fjgadhfas2_B.Z_n = fjgadhfas2_B.In1_d.Twist.Linear.Z;

  // Gain: '<S27>/Gain2'
  fjgadhfas2_B.Gain2_g = fjgadhfas2_P.Gain2_Gain_b * fjgadhfas2_B.Z_n;

  // MATLAB Function: '<S5>/MATLAB Function1'
  fjgadhfas2_B.Sum4 = 0.5 * fjgadhfas2_B.VectorConcatenate[1] + 0.5 *
    fjgadhfas2_B.Sum4;
  fjgadhfas2_cosd(&fjgadhfas2_B.Sum4);
  fjgadhfas2_B.Product2 = 0.5 * fjgadhfas2_B.VectorConcatenate[0] + 0.5 *
    fjgadhfas2_B.Product2;
  fjgadhfas2_cosd(&fjgadhfas2_B.Product2);

  // Switch: '<S5>/Switch2'
  if (fjgadhfas2_B.Valid) {
    // Switch: '<S5>/Switch2' incorporates:
    //   MATLAB Function: '<S5>/MATLAB Function1'
    //   Sum: '<S27>/Sum3'

    fjgadhfas2_B.Switch2 = ((fjgadhfas2_B.DiscreteTimeIntegrator_n +
      fjgadhfas2_B.Gain_n) - fjgadhfas2_B.Gain2_g) / fjgadhfas2_B.Sum4 /
      fjgadhfas2_B.Product2;
  } else {
    // Switch: '<S5>/Switch2' incorporates:
    //   Constant: '<S5>/Constant2'

    fjgadhfas2_B.Switch2 = fjgadhfas2_P.Constant2_Value;
  }

  // End of Switch: '<S5>/Switch2'

  // Saturate: '<Root>/Saturation2'
  if (fjgadhfas2_B.Switch2 > fjgadhfas2_P.Saturation2_UpperSat) {
    // Saturate: '<Root>/Saturation2'
    fjgadhfas2_B.Saturation2 = fjgadhfas2_P.Saturation2_UpperSat;
  } else if (fjgadhfas2_B.Switch2 < fjgadhfas2_P.Saturation2_LowerSat) {
    // Saturate: '<Root>/Saturation2'
    fjgadhfas2_B.Saturation2 = fjgadhfas2_P.Saturation2_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation2'
    fjgadhfas2_B.Saturation2 = fjgadhfas2_B.Switch2;
  }

  // End of Saturate: '<Root>/Saturation2'

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.Sum4 = floor(fjgadhfas2_B.Sum);
  if (rtIsNaN(fjgadhfas2_B.Sum4) || rtIsInf(fjgadhfas2_B.Sum4)) {
    fjgadhfas2_B.Sum4 = 0.0;
  } else {
    fjgadhfas2_B.Sum4 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[0] = static_cast<uint16_T>(fjgadhfas2_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas2_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas2_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.Sum4 = floor(fjgadhfas2_B.Sum1);
  if (rtIsNaN(fjgadhfas2_B.Sum4) || rtIsInf(fjgadhfas2_B.Sum4)) {
    fjgadhfas2_B.Sum4 = 0.0;
  } else {
    fjgadhfas2_B.Sum4 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[1] = static_cast<uint16_T>(fjgadhfas2_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas2_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas2_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S1>/Thrust for hover'
  //   Gain: '<S1>/From motor test stand'
  //   Sum: '<S1>/Sum4'

  fjgadhfas2_B.Sum4 = floor(fjgadhfas2_P.Frommotorteststand_Gain *
    fjgadhfas2_B.Saturation2 + fjgadhfas2_P.MOT_THST_HOVER_MCS);
  if (rtIsNaN(fjgadhfas2_B.Sum4) || rtIsInf(fjgadhfas2_B.Sum4)) {
    fjgadhfas2_B.Sum4 = 0.0;
  } else {
    fjgadhfas2_B.Sum4 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[2] = static_cast<uint16_T>(fjgadhfas2_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas2_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas2_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Zero2'

  fjgadhfas2_B.Sum4 = floor(fjgadhfas2_P.Zero2_Value);
  if (rtIsNaN(fjgadhfas2_B.Sum4) || rtIsInf(fjgadhfas2_B.Sum4)) {
    fjgadhfas2_B.Sum4 = 0.0;
  } else {
    fjgadhfas2_B.Sum4 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[3] = static_cast<uint16_T>(fjgadhfas2_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas2_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas2_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero'

  fjgadhfas2_B.Sum4 = floor(fjgadhfas2_P.Zero_Value);
  b_varargout_1 = rtIsNaN(fjgadhfas2_B.Sum4);
  tmp = rtIsInf(fjgadhfas2_B.Sum4);
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[4] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Flight Mode'

  fjgadhfas2_B.Product2 = floor(fjgadhfas2_P.STABILIZE);
  if (rtIsNaN(fjgadhfas2_B.Product2) || rtIsInf(fjgadhfas2_B.Product2)) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Product2, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[5] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[6] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[7] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[8] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[9] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[10] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[11] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[12] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas2_B.DataTypeConversion[13] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas2_B.Product2 = 0.0;
    fjgadhfas2_B.Sum4 = 0.0;
  } else {
    fjgadhfas2_B.Product2 = fmod(fjgadhfas2_B.Sum4, 65536.0);
    fjgadhfas2_B.Sum4 = fjgadhfas2_B.Product2;
  }

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero3'

  fjgadhfas2_B.DataTypeConversion[14] = static_cast<uint16_T>
    (fjgadhfas2_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Product2)));
  fjgadhfas2_B.DataTypeConversion[15] = static_cast<uint16_T>(fjgadhfas2_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas2_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas2_B.Sum4)));
  for (i = 0; i < 112; i++) {
    fjgadhfas2_B.Sum4 = floor(fjgadhfas2_P.Zero3_Value[i]);
    if (rtIsNaN(fjgadhfas2_B.Sum4) || rtIsInf(fjgadhfas2_B.Sum4)) {
      fjgadhfas2_B.Sum4 = 0.0;
    } else {
      fjgadhfas2_B.Sum4 = fmod(fjgadhfas2_B.Sum4, 65536.0);
    }

    fjgadhfas2_B.DataTypeConversion[i + 16] = static_cast<uint16_T>
      (fjgadhfas2_B.Sum4 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
         static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas2_B.Sum4)))) :
       static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas2_B.Sum4)));
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   Constant: '<S30>/Constant'

  fjgadhfas2_B.BusAssignment4 = fjgadhfas2_P.Constant_Value;
  memcpy(&fjgadhfas2_B.BusAssignment4.Data[0], &fjgadhfas2_B.DataTypeConversion
         [0], sizeof(uint16_T) << 7U);

  // DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
  //   Constant: '<S6>/Constant'

  fjgadhfas2_B.Sum4 = floor(fjgadhfas2_P.Constant_Value_n);
  if (rtIsNaN(fjgadhfas2_B.Sum4) || rtIsInf(fjgadhfas2_B.Sum4)) {
    fjgadhfas2_B.Sum4 = 0.0;
  } else {
    fjgadhfas2_B.Sum4 = fmod(fjgadhfas2_B.Sum4, 4.294967296E+9);
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   DataTypeConversion: '<S6>/Data Type Conversion1'

  fjgadhfas2_B.BusAssignment4.Data_SL_Info.CurrentLength = fjgadhfas2_B.Sum4 <
    0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>
    (-fjgadhfas2_B.Sum4))) : static_cast<uint32_T>(fjgadhfas2_B.Sum4);

  // Outputs for Atomic SubSystem: '<S6>/Publish'
  // MATLABSystem: '<S31>/SinkBlock'
  Pub_fjgadhfas2_183.publish(&fjgadhfas2_B.BusAssignment4);

  // End of Outputs for SubSystem: '<S6>/Publish'
  // S-Function (saeroclockpacer): '<Root>/Simulation Pace'
  //
  //  The Clock Pacer generates no code, it is only active in
  //  interpreted simulation.


  // Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S25>/Gain1'

  fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE += fjgadhfas2_P.Gain1_Gain_jk *
    fjgadhfas2_B.dx * fjgadhfas2_P.DiscreteTimeIntegrator_gainval;
  if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE >= fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE = fjgadhfas2_P.I_max_XY;
  } else if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE <=
             -fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE = -fjgadhfas2_P.I_max_XY;
  }

  fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRese = static_cast<int8_T>(rtb_AND);

  // Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S26>/Gain1'

  fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n += fjgadhfas2_P.Gain1_Gain_jc *
    fjgadhfas2_B.dz * fjgadhfas2_P.DiscreteTimeIntegrator_gainva_g;
  if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n >= fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n = fjgadhfas2_P.I_max_XY;
  } else if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n <=
             -fjgadhfas2_P.I_max_XY) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n = -fjgadhfas2_P.I_max_XY;
  }

  fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRe_b = static_cast<int8_T>(rtb_AND);

  // End of Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S27>/Gain1'

  fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d += fjgadhfas2_P.Gain1_Gain_j *
    fjgadhfas2_B.dy * fjgadhfas2_P.DiscreteTimeIntegrator_gainva_k;
  if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d >= fjgadhfas2_P.I_max_Z) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d = fjgadhfas2_P.I_max_Z;
  } else if (fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d <=
             -fjgadhfas2_P.I_max_Z) {
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d = -fjgadhfas2_P.I_max_Z;
  }

  fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRe_c = static_cast<int8_T>(rtb_AND);

  // End of Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator'

  // External mode
  rtExtModeUploadCheckTrigger(1);

  {                                    // Sample time: [0.0125s, 0.0s]
    rtExtModeUpload(0, (real_T)fjgadhfas2_M->Timing.taskTime0);
  }

  // signal main to stop simulation
  {                                    // Sample time: [0.0125s, 0.0s]
    if ((rtmGetTFinal(fjgadhfas2_M)!=-1) &&
        !((rtmGetTFinal(fjgadhfas2_M)-fjgadhfas2_M->Timing.taskTime0) >
          fjgadhfas2_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(fjgadhfas2_M, "Simulation finished");
    }

    if (rtmGetStopRequested(fjgadhfas2_M)) {
      rtmSetErrorStatus(fjgadhfas2_M, "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  fjgadhfas2_M->Timing.taskTime0 =
    ((time_T)(++fjgadhfas2_M->Timing.clockTick0)) *
    fjgadhfas2_M->Timing.stepSize0;
}

// Model initialize function
void fjgadhfas2_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(fjgadhfas2_M, -1);
  fjgadhfas2_M->Timing.stepSize0 = 0.0125;

  // External mode info
  fjgadhfas2_M->Sizes.checksums[0] = (2929098801U);
  fjgadhfas2_M->Sizes.checksums[1] = (3152731070U);
  fjgadhfas2_M->Sizes.checksums[2] = (1553843473U);
  fjgadhfas2_M->Sizes.checksums[3] = (3074847467U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[22];
    fjgadhfas2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC_o;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = (sysRanDType *)&fjgadhfas2_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[5] = (sysRanDType *)&fjgadhfas2_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[6] = (sysRanDType *)&fjgadhfas2_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[7] = (sysRanDType *)&fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC_d;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = (sysRanDType *)&fjgadhfas2_DW.EnabledSubsystem_SubsysRanBC;
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
    rteiSetModelMappingInfoPtr(fjgadhfas2_M->extModeInfo,
      &fjgadhfas2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(fjgadhfas2_M->extModeInfo, fjgadhfas2_M->Sizes.checksums);
    rteiSetTPtr(fjgadhfas2_M->extModeInfo, rtmGetTPtr(fjgadhfas2_M));
  }

  // data type transition information
  {
    static DataTypeTransInfo dtInfo;
    fjgadhfas2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 35;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    // Block I/O transition table
    dtInfo.BTransTable = &rtBTransTable;

    // Parameters transition table
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    char_T b_zeroDelimTopic[29];
    char_T b_zeroDelimTopic_0[17];
    char_T b_zeroDelimTopic_1[14];
    static const char_T tmp[28] = { '/', 'v', 'r', 'p', 'n', '_', 'c', 'l', 'i',
      'e', 'n', 't', '_', 'n', 'o', 'd', 'e', '/', 'Q', 'u', 'a', 'd', '1', '/',
      'p', 'o', 's', 'e' };

    static const char_T tmp_0[16] = { '/', 'a', 'u', 't', 'o', 'n', 'o', 'm',
      'y', '_', 'e', 'n', 'a', 'b', 'l', 'e' };

    static const char_T tmp_1[39] = { '/', 'v', 'r', 'p', 'n', '_', 'v', 'e',
      'l', 'o', 'c', 'i', 't', 'y', '/', 'o', 'p', 't', 'i', 't', 'r', 'a', 'c',
      'k', '_', 'f', 'r', 'a', 'm', 'e', '/', 'f', 'i', 'l', 't', 'e', 'r', 'e',
      'd' };

    static const char_T tmp_2[13] = { 'q', 'u', 'a', 'd', '_', 'c', 'o', 'm',
      'm', 'a', 'n', 'd', 's' };

    // InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' 
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE =
      fjgadhfas2_P.DiscreteTimeIntegrator_IC;
    fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRese = 2;

    // InitializeConditions for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' 
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_n =
      fjgadhfas2_P.DiscreteTimeIntegrator_IC_e;
    fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRe_b = 2;

    // InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' 
    fjgadhfas2_DW.DiscreteTimeIntegrator_DSTATE_d =
      fjgadhfas2_P.DiscreteTimeIntegrator_IC_l;
    fjgadhfas2_DW.DiscreteTimeIntegrator_PrevRe_c = 2;

    // SystemInitialize for Atomic SubSystem: '<S3>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S10>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S20>/In1' incorporates:
    //   Outport: '<S20>/Out1'

    fjgadhfas2_B.In1 = fjgadhfas2_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S10>/Enabled Subsystem'

    // Start for MATLABSystem: '<S10>/SourceBlock'
    fjgadhfas2_DW.obj_k.matlabCodegenIsDeleted = false;
    fjgadhfas2_DW.obj_k.isInitialized = 1;
    for (int32_T i = 0; i < 28; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[28] = '\x00';
    Sub_fjgadhfas2_39.createSubscriber(&b_zeroDelimTopic[0], 1);
    fjgadhfas2_DW.obj_k.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S10>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S3>/Subscribe'

    // SystemInitialize for MATLAB Function: '<S28>/MATLAB Function'
    fjgadhfas2_DW.idx = 1U;

    // SystemInitialize for Atomic SubSystem: '<S2>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S8>/In1' incorporates:
    //   Outport: '<S8>/Out1'

    fjgadhfas2_B.In1_p = fjgadhfas2_P.Out1_Y0_k;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'

    // Start for MATLABSystem: '<S7>/SourceBlock'
    fjgadhfas2_DW.obj_d.matlabCodegenIsDeleted = false;
    fjgadhfas2_DW.obj_d.isInitialized = 1;
    for (int32_T i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[16] = '\x00';
    Sub_fjgadhfas2_22.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    fjgadhfas2_DW.obj_d.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S2>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S4>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S21>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S22>/In1' incorporates:
    //   Outport: '<S22>/Out1'

    fjgadhfas2_B.In1_d = fjgadhfas2_P.Out1_Y0_e;

    // End of SystemInitialize for SubSystem: '<S21>/Enabled Subsystem'

    // Start for MATLABSystem: '<S21>/SourceBlock'
    fjgadhfas2_DW.obj.matlabCodegenIsDeleted = false;
    fjgadhfas2_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 39; i++) {
      fjgadhfas2_B.b_zeroDelimTopic[i] = tmp_1[i];
    }

    fjgadhfas2_B.b_zeroDelimTopic[39] = '\x00';
    Sub_fjgadhfas2_50.createSubscriber(&fjgadhfas2_B.b_zeroDelimTopic[0], 1);
    fjgadhfas2_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S21>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S4>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S6>/Publish'
    // Start for MATLABSystem: '<S31>/SinkBlock'
    fjgadhfas2_DW.obj_n.matlabCodegenIsDeleted = false;
    fjgadhfas2_DW.obj_n.isInitialized = 1;
    for (int32_T i = 0; i < 13; i++) {
      b_zeroDelimTopic_1[i] = tmp_2[i];
    }

    b_zeroDelimTopic_1[13] = '\x00';
    Pub_fjgadhfas2_183.createPublisher(&b_zeroDelimTopic_1[0], 1);
    fjgadhfas2_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S31>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<S6>/Publish'
  }
}

// Model terminate function
void fjgadhfas2_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S3>/Subscribe'
  // Terminate for MATLABSystem: '<S10>/SourceBlock'
  if (!fjgadhfas2_DW.obj_k.matlabCodegenIsDeleted) {
    fjgadhfas2_DW.obj_k.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S10>/SourceBlock'
  // End of Terminate for SubSystem: '<S3>/Subscribe'

  // Terminate for Atomic SubSystem: '<S2>/Subscribe'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!fjgadhfas2_DW.obj_d.matlabCodegenIsDeleted) {
    fjgadhfas2_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'
  // End of Terminate for SubSystem: '<S2>/Subscribe'

  // Terminate for Atomic SubSystem: '<S4>/Subscribe'
  // Terminate for MATLABSystem: '<S21>/SourceBlock'
  if (!fjgadhfas2_DW.obj.matlabCodegenIsDeleted) {
    fjgadhfas2_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S21>/SourceBlock'
  // End of Terminate for SubSystem: '<S4>/Subscribe'

  // Terminate for Atomic SubSystem: '<S6>/Publish'
  // Terminate for MATLABSystem: '<S31>/SinkBlock'
  if (!fjgadhfas2_DW.obj_n.matlabCodegenIsDeleted) {
    fjgadhfas2_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S31>/SinkBlock'
  // End of Terminate for SubSystem: '<S6>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
