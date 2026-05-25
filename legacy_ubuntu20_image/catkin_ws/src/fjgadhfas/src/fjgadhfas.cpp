//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: fjgadhfas.cpp
//
// Code generated for Simulink model 'fjgadhfas'.
//
// Model version                  : 1.1
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Jan 15 18:04:51 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "fjgadhfas.h"
#include "rtwtypes.h"
#include <math.h>
#include "fjgadhfas_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>
#include "fjgadhfas_types.h"
#include "rt_defines.h"
#include <float.h>
#include "fjgadhfas_dt.h"

// Block signals (default storage)
B_fjgadhfas_T fjgadhfas_B;

// Block states (default storage)
DW_fjgadhfas_T fjgadhfas_DW;

// Real-time model
RT_MODEL_fjgadhfas_T fjgadhfas_M_ = RT_MODEL_fjgadhfas_T();
RT_MODEL_fjgadhfas_T *const fjgadhfas_M = &fjgadhfas_M_;

// Forward declaration for local functions
static void fjgadhfas_cosd(real_T *x);
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
static void fjgadhfas_cosd(real_T *x)
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
void fjgadhfas_step(void)
{
  SL_Bus_fjgadhfas_std_msgs_Bool b_varargout_2;
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_0;
  int32_T i;
  boolean_T b_varargout_1;
  boolean_T rtb_AND;
  boolean_T tmp;

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas_DW.EnabledSubsystem_SubsysRanBC_o);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas_DW.IfActionSubsystem2_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas_DW.EnabledSubsystem_SubsysRanBC_d);

  // Reset subsysRan breadcrumbs
  srClearBC(fjgadhfas_DW.EnabledSubsystem_SubsysRanBC);

  // Outputs for Atomic SubSystem: '<S3>/Subscribe'
  // MATLABSystem: '<S10>/SourceBlock'
  b_varargout_1 = Sub_fjgadhfas_39.getLatestMessage(&fjgadhfas_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S20>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S20>/In1'
    fjgadhfas_B.In1 = fjgadhfas_B.b_varargout_2;
    srUpdateBC(fjgadhfas_DW.EnabledSubsystem_SubsysRanBC_d);
  }

  // End of MATLABSystem: '<S10>/SourceBlock'
  // End of Outputs for SubSystem: '<S10>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S3>/Subscribe'

  // Gain: '<S3>/Gain'
  fjgadhfas_B.x = fjgadhfas_P.Gain_Gain * fjgadhfas_B.In1.Pose.Position.Y;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  fjgadhfas_B.X = fjgadhfas_B.In1.Pose.Position.X;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  fjgadhfas_B.Z = fjgadhfas_B.In1.Pose.Position.Z;

  // MATLAB Function: '<S28>/MATLAB Function' incorporates:
  //   Constant: '<S28>/Constant'

  if (fjgadhfas_DW.filled == 0) {
    fjgadhfas_DW.bufX[fjgadhfas_DW.idx - 1] = fjgadhfas_B.x;
    fjgadhfas_DW.bufY[fjgadhfas_DW.idx - 1] = fjgadhfas_B.X;
    fjgadhfas_DW.bufZ[fjgadhfas_DW.idx - 1] = fjgadhfas_B.Z;
    fjgadhfas_DW.filled = 1U;
    fjgadhfas_DW.idx = 2U;
    fjgadhfas_B.Valid = true;
    fjgadhfas_B.frozenNow = false;
    fjgadhfas_B.filled_ = 0U;
    fjgadhfas_B.updated = false;
    fjgadhfas_B.d = -1.0;
    fjgadhfas_B.v = -1.0;
  } else {
    uint32_T qY;
    uint8_T prevIdx;
    qY = fjgadhfas_DW.idx - 1U;
    if (fjgadhfas_DW.idx - 1U > fjgadhfas_DW.idx) {
      qY = 0U;
    }

    prevIdx = static_cast<uint8_T>(qY);
    if (static_cast<uint8_T>(qY) == 0) {
      prevIdx = 6U;
    }

    fjgadhfas_B.dx = fjgadhfas_B.x - fjgadhfas_DW.bufX[prevIdx - 1];
    fjgadhfas_B.dy = fjgadhfas_B.X - fjgadhfas_DW.bufY[prevIdx - 1];
    fjgadhfas_B.dz = fjgadhfas_B.Z - fjgadhfas_DW.bufZ[prevIdx - 1];
    fjgadhfas_B.d = sqrt((fjgadhfas_B.dx * fjgadhfas_B.dx + fjgadhfas_B.dy *
                          fjgadhfas_B.dy) + fjgadhfas_B.dz * fjgadhfas_B.dz);
    fjgadhfas_B.v = fjgadhfas_B.d / fjgadhfas_P.time_step;
    fjgadhfas_B.updated = (fjgadhfas_B.d > 1.0E-6);
    fjgadhfas_B.frozenNow = false;
    if (fjgadhfas_DW.filled >= 6) {
      boolean_T exitg1;
      fjgadhfas_B.frozenNow = true;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 5)) {
        int32_T ddx_tmp_tmp;
        ddx_tmp_tmp = prevIdx - 1;
        fjgadhfas_B.dx = fjgadhfas_B.x - fjgadhfas_DW.bufX[prevIdx - 1];
        fjgadhfas_B.dy = fjgadhfas_B.X - fjgadhfas_DW.bufY[prevIdx - 1];
        fjgadhfas_B.dz = fjgadhfas_B.Z - fjgadhfas_DW.bufZ[prevIdx - 1];
        if (sqrt((fjgadhfas_B.dx * fjgadhfas_B.dx + fjgadhfas_B.dy *
                  fjgadhfas_B.dy) + fjgadhfas_B.dz * fjgadhfas_B.dz) > 1.0E-6) {
          fjgadhfas_B.frozenNow = false;
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

    if (!fjgadhfas_DW.inLost) {
      if ((fjgadhfas_B.v > 20.0) || fjgadhfas_B.frozenNow) {
        fjgadhfas_DW.inLost = true;
        fjgadhfas_DW.goodCnt = 0U;
        fjgadhfas_B.Valid = false;
      } else {
        fjgadhfas_B.Valid = true;
      }
    } else if (fjgadhfas_B.updated && (fjgadhfas_B.v <= 20.0)) {
      if (fjgadhfas_DW.goodCnt < 255) {
        fjgadhfas_DW.goodCnt = static_cast<uint8_T>(fjgadhfas_DW.goodCnt + 1U);
      }

      if (fjgadhfas_DW.goodCnt >= 5) {
        fjgadhfas_DW.inLost = false;
        fjgadhfas_DW.goodCnt = 0U;
        fjgadhfas_B.Valid = true;
      } else {
        fjgadhfas_B.Valid = false;
      }
    } else {
      if (fjgadhfas_B.v > 20.0) {
        fjgadhfas_DW.goodCnt = 0U;
      }

      fjgadhfas_B.Valid = false;
    }

    fjgadhfas_DW.bufX[fjgadhfas_DW.idx - 1] = fjgadhfas_B.x;
    fjgadhfas_DW.bufY[fjgadhfas_DW.idx - 1] = fjgadhfas_B.X;
    fjgadhfas_DW.bufZ[fjgadhfas_DW.idx - 1] = fjgadhfas_B.Z;
    if (fjgadhfas_DW.filled < 6) {
      fjgadhfas_DW.filled = static_cast<uint8_T>(fjgadhfas_DW.filled + 1U);
    }

    i = static_cast<int32_T>(fjgadhfas_DW.idx + 1U);
    if (fjgadhfas_DW.idx + 1U > 255U) {
      i = 255;
    }

    fjgadhfas_DW.idx = static_cast<uint8_T>(i);
    if (fjgadhfas_DW.idx > 6) {
      fjgadhfas_DW.idx = 1U;
    }

    fjgadhfas_B.filled_ = fjgadhfas_DW.filled;
  }

  // End of MATLAB Function: '<S28>/MATLAB Function'

  // Sqrt: '<S18>/sqrt' incorporates:
  //   Product: '<S19>/Product'
  //   Product: '<S19>/Product1'
  //   Product: '<S19>/Product2'
  //   Product: '<S19>/Product3'
  //   Sum: '<S19>/Sum'

  fjgadhfas_B.dz = sqrt(((fjgadhfas_B.In1.Pose.Orientation.W *
    fjgadhfas_B.In1.Pose.Orientation.W + fjgadhfas_B.In1.Pose.Orientation.X *
    fjgadhfas_B.In1.Pose.Orientation.X) + fjgadhfas_B.In1.Pose.Orientation.Y *
    fjgadhfas_B.In1.Pose.Orientation.Y) + fjgadhfas_B.In1.Pose.Orientation.Z *
                        fjgadhfas_B.In1.Pose.Orientation.Z);

  // Product: '<S13>/Product'
  fjgadhfas_B.dy = fjgadhfas_B.In1.Pose.Orientation.W / fjgadhfas_B.dz;

  // Product: '<S13>/Product1'
  fjgadhfas_B.Sum4 = fjgadhfas_B.In1.Pose.Orientation.X / fjgadhfas_B.dz;

  // Product: '<S13>/Product2'
  fjgadhfas_B.Product2 = fjgadhfas_B.In1.Pose.Orientation.Y / fjgadhfas_B.dz;

  // Product: '<S13>/Product3'
  fjgadhfas_B.dz = fjgadhfas_B.In1.Pose.Orientation.Z / fjgadhfas_B.dz;

  // Fcn: '<S11>/fcn2' incorporates:
  //   Fcn: '<S11>/fcn5'

  fjgadhfas_B.VectorConcatenate_tmp = fjgadhfas_B.dy * fjgadhfas_B.dy;
  fjgadhfas_B.VectorConcatenate_tmp_c = fjgadhfas_B.Sum4 * fjgadhfas_B.Sum4;
  VectorConcatenate_tmp = fjgadhfas_B.Product2 * fjgadhfas_B.Product2;
  VectorConcatenate_tmp_0 = fjgadhfas_B.dz * fjgadhfas_B.dz;

  // Trigonometry: '<S12>/Trigonometric Function1' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn1'
  //   Fcn: '<S11>/fcn2'

  fjgadhfas_B.VectorConcatenate[0] = rt_atan2d_snf((fjgadhfas_B.Product2 *
    fjgadhfas_B.dz - fjgadhfas_B.dy * fjgadhfas_B.Sum4) * -2.0,
    ((fjgadhfas_B.VectorConcatenate_tmp - fjgadhfas_B.VectorConcatenate_tmp_c) -
     VectorConcatenate_tmp) + VectorConcatenate_tmp_0);

  // Fcn: '<S11>/fcn3'
  fjgadhfas_B.dx = (fjgadhfas_B.Sum4 * fjgadhfas_B.dz + fjgadhfas_B.dy *
                    fjgadhfas_B.Product2) * 2.0;

  // If: '<S14>/If' incorporates:
  //   Constant: '<S15>/Constant'
  //   Constant: '<S16>/Constant'

  if (fjgadhfas_B.dx > 1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    fjgadhfas_B.dx = fjgadhfas_P.Constant_Value_ey;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S15>/Constant'

    srUpdateBC(fjgadhfas_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem'
  } else if (fjgadhfas_B.dx < -1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    fjgadhfas_B.dx = fjgadhfas_P.Constant_Value_b;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S16>/Constant'

    srUpdateBC(fjgadhfas_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S14>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S17>/Action Port'

    // Update for If: '<S14>/If'
    srUpdateBC(fjgadhfas_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem2'
  }

  // End of If: '<S14>/If'

  // Trigonometry: '<S12>/trigFcn' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'

  if (fjgadhfas_B.dx > 1.0) {
    fjgadhfas_B.dx = 1.0;
  } else if (fjgadhfas_B.dx < -1.0) {
    fjgadhfas_B.dx = -1.0;
  }

  fjgadhfas_B.VectorConcatenate[1] = asin(fjgadhfas_B.dx);

  // End of Trigonometry: '<S12>/trigFcn'

  // Trigonometry: '<S12>/Trigonometric Function3' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn4'
  //   Fcn: '<S11>/fcn5'

  fjgadhfas_B.VectorConcatenate[2] = rt_atan2d_snf((fjgadhfas_B.Sum4 *
    fjgadhfas_B.Product2 - fjgadhfas_B.dy * fjgadhfas_B.dz) * -2.0,
    ((fjgadhfas_B.VectorConcatenate_tmp + fjgadhfas_B.VectorConcatenate_tmp_c) -
     VectorConcatenate_tmp) - VectorConcatenate_tmp_0);

  // Outputs for Atomic SubSystem: '<S2>/Subscribe'
  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = Sub_fjgadhfas_22.getLatestMessage(&b_varargout_2);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    fjgadhfas_B.In1_p = b_varargout_2;
    srUpdateBC(fjgadhfas_DW.EnabledSubsystem_SubsysRanBC_o);
  }

  // End of MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S2>/Subscribe'

  // Logic: '<S5>/AND'
  rtb_AND = (fjgadhfas_B.Valid && fjgadhfas_B.In1_p.Data);

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  if (rtb_AND && (fjgadhfas_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE =
      fjgadhfas_P.DiscreteTimeIntegrator_IC;
  }

  if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE >= fjgadhfas_P.I_max_XY) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE = fjgadhfas_P.I_max_XY;
  } else if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE <= -fjgadhfas_P.I_max_XY)
  {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE = -fjgadhfas_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  fjgadhfas_B.DiscreteTimeIntegrator =
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE;

  // Sum: '<S5>/Sum' incorporates:
  //   Constant: '<S5>/X_ref'

  fjgadhfas_B.dx = fjgadhfas_P.X_ref_Value - fjgadhfas_B.x;

  // Gain: '<S25>/Gain'
  fjgadhfas_B.Gain = fjgadhfas_P.Gain_Gain_j * fjgadhfas_B.dx;

  // Outputs for Atomic SubSystem: '<S4>/Subscribe'
  // MATLABSystem: '<S21>/SourceBlock'
  b_varargout_1 = Sub_fjgadhfas_50.getLatestMessage(&fjgadhfas_B.b_varargout_2_m);

  // Outputs for Enabled SubSystem: '<S21>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S22>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S22>/In1'
    fjgadhfas_B.In1_d = fjgadhfas_B.b_varargout_2_m;
    srUpdateBC(fjgadhfas_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S21>/SourceBlock'
  // End of Outputs for SubSystem: '<S21>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S4>/Subscribe'

  // Gain: '<S4>/Gain' incorporates:
  //   SignalConversion generated from: '<S4>/Bus Selector'

  fjgadhfas_B.x_d = fjgadhfas_P.Gain_Gain_n * fjgadhfas_B.In1_d.Twist.Linear.Y;

  // Gain: '<S25>/Gain2'
  fjgadhfas_B.Gain2 = fjgadhfas_P.Gain2_Gain * fjgadhfas_B.x_d;

  // Sum: '<S25>/Sum3'
  fjgadhfas_B.dy = (fjgadhfas_B.DiscreteTimeIntegrator + fjgadhfas_B.Gain) -
    fjgadhfas_B.Gain2;

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  if (rtb_AND && (fjgadhfas_DW.DiscreteTimeIntegrator_PrevRe_b <= 0)) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n =
      fjgadhfas_P.DiscreteTimeIntegrator_IC_e;
  }

  if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n >= fjgadhfas_P.I_max_XY) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n = fjgadhfas_P.I_max_XY;
  } else if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n <=
             -fjgadhfas_P.I_max_XY) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n = -fjgadhfas_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  fjgadhfas_B.DiscreteTimeIntegrator_p =
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n;

  // Sum: '<S5>/Sum1' incorporates:
  //   Constant: '<S5>/Y_ref'

  fjgadhfas_B.dz = fjgadhfas_P.Y_ref_Value - fjgadhfas_B.X;

  // Gain: '<S26>/Gain'
  fjgadhfas_B.Gain_j = fjgadhfas_P.Gain_Gain_c * fjgadhfas_B.dz;

  // SignalConversion generated from: '<S4>/Bus Selector'
  fjgadhfas_B.X_h = fjgadhfas_B.In1_d.Twist.Linear.X;

  // Gain: '<S26>/Gain2'
  fjgadhfas_B.Gain2_m = fjgadhfas_P.Gain2_Gain_j * fjgadhfas_B.X_h;

  // Sum: '<S26>/Sum3'
  fjgadhfas_B.Product2 = (fjgadhfas_B.DiscreteTimeIntegrator_p +
    fjgadhfas_B.Gain_j) - fjgadhfas_B.Gain2_m;

  // MATLAB Function: '<S5>/MATLAB Function'
  fjgadhfas_B.VectorConcatenate_tmp = cos(fjgadhfas_B.VectorConcatenate[2]);
  fjgadhfas_B.VectorConcatenate_tmp_c = sin(fjgadhfas_B.VectorConcatenate[2]);
  fjgadhfas_B.Sum4 = -fjgadhfas_B.Product2 * fjgadhfas_B.VectorConcatenate_tmp_c
    - fjgadhfas_B.dy * fjgadhfas_B.VectorConcatenate_tmp;
  fjgadhfas_B.Product2 = -fjgadhfas_B.Product2 *
    fjgadhfas_B.VectorConcatenate_tmp + fjgadhfas_B.dy *
    fjgadhfas_B.VectorConcatenate_tmp_c;

  // Switch: '<S5>/Switch1'
  if (fjgadhfas_B.Valid) {
    // Switch: '<S5>/Switch1'
    fjgadhfas_B.Switch1 = fjgadhfas_B.Product2;
  } else {
    // Switch: '<S5>/Switch1' incorporates:
    //   Constant: '<S5>/Constant1'

    fjgadhfas_B.Switch1 = fjgadhfas_P.Constant1_Value;
  }

  // End of Switch: '<S5>/Switch1'

  // Saturate: '<Root>/Saturation'
  if (fjgadhfas_B.Switch1 > fjgadhfas_P.Saturation_UpperSat) {
    // Saturate: '<Root>/Saturation'
    fjgadhfas_B.Saturation = fjgadhfas_P.Saturation_UpperSat;
  } else if (fjgadhfas_B.Switch1 < fjgadhfas_P.Saturation_LowerSat) {
    // Saturate: '<Root>/Saturation'
    fjgadhfas_B.Saturation = fjgadhfas_P.Saturation_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation'
    fjgadhfas_B.Saturation = fjgadhfas_B.Switch1;
  }

  // End of Saturate: '<Root>/Saturation'

  // Sum: '<S1>/Sum' incorporates:
  //   Constant: '<S1>/Trim'
  //   Gain: '<S1>/Gain'
  //   Gain: '<S1>/Gain1'

  fjgadhfas_B.Sum = fjgadhfas_P.Gain_Gain_h * fjgadhfas_B.Saturation *
    fjgadhfas_P.Gain1_Gain + fjgadhfas_P.Trim_Value;

  // Switch: '<S5>/Switch'
  if (fjgadhfas_B.Valid) {
    // Switch: '<S5>/Switch'
    fjgadhfas_B.Switch = fjgadhfas_B.Sum4;
  } else {
    // Switch: '<S5>/Switch' incorporates:
    //   Constant: '<S5>/Constant'

    fjgadhfas_B.Switch = fjgadhfas_P.Constant_Value_f;
  }

  // End of Switch: '<S5>/Switch'

  // Saturate: '<Root>/Saturation1'
  if (fjgadhfas_B.Switch > fjgadhfas_P.Saturation1_UpperSat) {
    // Saturate: '<Root>/Saturation1'
    fjgadhfas_B.Saturation1 = fjgadhfas_P.Saturation1_UpperSat;
  } else if (fjgadhfas_B.Switch < fjgadhfas_P.Saturation1_LowerSat) {
    // Saturate: '<Root>/Saturation1'
    fjgadhfas_B.Saturation1 = fjgadhfas_P.Saturation1_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation1'
    fjgadhfas_B.Saturation1 = fjgadhfas_B.Switch;
  }

  // End of Saturate: '<Root>/Saturation1'

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Trim1'
  //   Gain: '<S1>/Gain2'
  //   Gain: '<S1>/Gain3'

  fjgadhfas_B.Sum1 = fjgadhfas_P.Gain2_Gain_je * fjgadhfas_B.Saturation1 *
    fjgadhfas_P.Gain3_Gain + fjgadhfas_P.Trim1_Value;

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  if (rtb_AND && (fjgadhfas_DW.DiscreteTimeIntegrator_PrevRe_c <= 0)) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d =
      fjgadhfas_P.DiscreteTimeIntegrator_IC_l;
  }

  if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d >= fjgadhfas_P.I_max_Z) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d = fjgadhfas_P.I_max_Z;
  } else if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d <=
             -fjgadhfas_P.I_max_Z) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d = -fjgadhfas_P.I_max_Z;
  }

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  fjgadhfas_B.DiscreteTimeIntegrator_n =
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d;

  // Sum: '<S5>/Sum2' incorporates:
  //   Constant: '<S5>/Z_ref'

  fjgadhfas_B.dy = fjgadhfas_P.Z_ref_Value - fjgadhfas_B.Z;

  // Gain: '<S27>/Gain'
  fjgadhfas_B.Gain_n = fjgadhfas_P.Gain_Gain_d * fjgadhfas_B.dy;

  // SignalConversion generated from: '<S4>/Bus Selector'
  fjgadhfas_B.Z_n = fjgadhfas_B.In1_d.Twist.Linear.Z;

  // Gain: '<S27>/Gain2'
  fjgadhfas_B.Gain2_g = fjgadhfas_P.Gain2_Gain_b * fjgadhfas_B.Z_n;

  // MATLAB Function: '<S5>/MATLAB Function1'
  fjgadhfas_B.Sum4 = 0.5 * fjgadhfas_B.VectorConcatenate[1] + 0.5 *
    fjgadhfas_B.Sum4;
  fjgadhfas_cosd(&fjgadhfas_B.Sum4);
  fjgadhfas_B.Product2 = 0.5 * fjgadhfas_B.VectorConcatenate[0] + 0.5 *
    fjgadhfas_B.Product2;
  fjgadhfas_cosd(&fjgadhfas_B.Product2);

  // Switch: '<S5>/Switch2'
  if (fjgadhfas_B.Valid) {
    // Switch: '<S5>/Switch2' incorporates:
    //   MATLAB Function: '<S5>/MATLAB Function1'
    //   Sum: '<S27>/Sum3'

    fjgadhfas_B.Switch2 = ((fjgadhfas_B.DiscreteTimeIntegrator_n +
      fjgadhfas_B.Gain_n) - fjgadhfas_B.Gain2_g) / fjgadhfas_B.Sum4 /
      fjgadhfas_B.Product2;
  } else {
    // Switch: '<S5>/Switch2' incorporates:
    //   Constant: '<S5>/Constant2'

    fjgadhfas_B.Switch2 = fjgadhfas_P.Constant2_Value;
  }

  // End of Switch: '<S5>/Switch2'

  // Saturate: '<Root>/Saturation2'
  if (fjgadhfas_B.Switch2 > fjgadhfas_P.Saturation2_UpperSat) {
    // Saturate: '<Root>/Saturation2'
    fjgadhfas_B.Saturation2 = fjgadhfas_P.Saturation2_UpperSat;
  } else if (fjgadhfas_B.Switch2 < fjgadhfas_P.Saturation2_LowerSat) {
    // Saturate: '<Root>/Saturation2'
    fjgadhfas_B.Saturation2 = fjgadhfas_P.Saturation2_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation2'
    fjgadhfas_B.Saturation2 = fjgadhfas_B.Switch2;
  }

  // End of Saturate: '<Root>/Saturation2'

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.Sum4 = floor(fjgadhfas_B.Sum);
  if (rtIsNaN(fjgadhfas_B.Sum4) || rtIsInf(fjgadhfas_B.Sum4)) {
    fjgadhfas_B.Sum4 = 0.0;
  } else {
    fjgadhfas_B.Sum4 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[0] = static_cast<uint16_T>(fjgadhfas_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.Sum4 = floor(fjgadhfas_B.Sum1);
  if (rtIsNaN(fjgadhfas_B.Sum4) || rtIsInf(fjgadhfas_B.Sum4)) {
    fjgadhfas_B.Sum4 = 0.0;
  } else {
    fjgadhfas_B.Sum4 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[1] = static_cast<uint16_T>(fjgadhfas_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S1>/Thrust for hover'
  //   Gain: '<S1>/From motor test stand'
  //   Sum: '<S1>/Sum4'

  fjgadhfas_B.Sum4 = floor(fjgadhfas_P.Frommotorteststand_Gain *
    fjgadhfas_B.Saturation2 + fjgadhfas_P.MOT_THST_HOVER_MCS);
  if (rtIsNaN(fjgadhfas_B.Sum4) || rtIsInf(fjgadhfas_B.Sum4)) {
    fjgadhfas_B.Sum4 = 0.0;
  } else {
    fjgadhfas_B.Sum4 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[2] = static_cast<uint16_T>(fjgadhfas_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Zero2'

  fjgadhfas_B.Sum4 = floor(fjgadhfas_P.Zero2_Value);
  if (rtIsNaN(fjgadhfas_B.Sum4) || rtIsInf(fjgadhfas_B.Sum4)) {
    fjgadhfas_B.Sum4 = 0.0;
  } else {
    fjgadhfas_B.Sum4 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[3] = static_cast<uint16_T>(fjgadhfas_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero'

  fjgadhfas_B.Sum4 = floor(fjgadhfas_P.Zero_Value);
  b_varargout_1 = rtIsNaN(fjgadhfas_B.Sum4);
  tmp = rtIsInf(fjgadhfas_B.Sum4);
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[4] = static_cast<uint16_T>(fjgadhfas_B.Product2
    < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Flight Mode'

  fjgadhfas_B.Product2 = floor(fjgadhfas_P.STABILIZE);
  if (rtIsNaN(fjgadhfas_B.Product2) || rtIsInf(fjgadhfas_B.Product2)) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Product2, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[5] = static_cast<uint16_T>(fjgadhfas_B.Product2
    < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[6] = static_cast<uint16_T>(fjgadhfas_B.Product2
    < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[7] = static_cast<uint16_T>(fjgadhfas_B.Product2
    < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[8] = static_cast<uint16_T>(fjgadhfas_B.Product2
    < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[9] = static_cast<uint16_T>(fjgadhfas_B.Product2
    < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Product2)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[10] = static_cast<uint16_T>
    (fjgadhfas_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[11] = static_cast<uint16_T>
    (fjgadhfas_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[12] = static_cast<uint16_T>
    (fjgadhfas_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  fjgadhfas_B.DataTypeConversion[13] = static_cast<uint16_T>
    (fjgadhfas_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    fjgadhfas_B.Product2 = 0.0;
    fjgadhfas_B.Sum4 = 0.0;
  } else {
    fjgadhfas_B.Product2 = fmod(fjgadhfas_B.Sum4, 65536.0);
    fjgadhfas_B.Sum4 = fjgadhfas_B.Product2;
  }

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero3'

  fjgadhfas_B.DataTypeConversion[14] = static_cast<uint16_T>
    (fjgadhfas_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
       static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas_B.Product2)))) :
     static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas_B.Product2)));
  fjgadhfas_B.DataTypeConversion[15] = static_cast<uint16_T>(fjgadhfas_B.Sum4 <
    0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-static_cast<int16_T>(
    static_cast<uint16_T>(-fjgadhfas_B.Sum4)))) : static_cast<int32_T>(
    static_cast<uint16_T>(fjgadhfas_B.Sum4)));
  for (i = 0; i < 112; i++) {
    fjgadhfas_B.Sum4 = floor(fjgadhfas_P.Zero3_Value[i]);
    if (rtIsNaN(fjgadhfas_B.Sum4) || rtIsInf(fjgadhfas_B.Sum4)) {
      fjgadhfas_B.Sum4 = 0.0;
    } else {
      fjgadhfas_B.Sum4 = fmod(fjgadhfas_B.Sum4, 65536.0);
    }

    fjgadhfas_B.DataTypeConversion[i + 16] = static_cast<uint16_T>
      (fjgadhfas_B.Sum4 < 0.0 ? static_cast<int32_T>(static_cast<uint16_T>(-
         static_cast<int16_T>(static_cast<uint16_T>(-fjgadhfas_B.Sum4)))) :
       static_cast<int32_T>(static_cast<uint16_T>(fjgadhfas_B.Sum4)));
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   Constant: '<S30>/Constant'

  fjgadhfas_B.BusAssignment4 = fjgadhfas_P.Constant_Value;
  memcpy(&fjgadhfas_B.BusAssignment4.Data[0], &fjgadhfas_B.DataTypeConversion[0],
         sizeof(uint16_T) << 7U);

  // DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
  //   Constant: '<S6>/Constant'

  fjgadhfas_B.Sum4 = floor(fjgadhfas_P.Constant_Value_n);
  if (rtIsNaN(fjgadhfas_B.Sum4) || rtIsInf(fjgadhfas_B.Sum4)) {
    fjgadhfas_B.Sum4 = 0.0;
  } else {
    fjgadhfas_B.Sum4 = fmod(fjgadhfas_B.Sum4, 4.294967296E+9);
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   DataTypeConversion: '<S6>/Data Type Conversion1'

  fjgadhfas_B.BusAssignment4.Data_SL_Info.CurrentLength = fjgadhfas_B.Sum4 < 0.0
    ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>
    (-fjgadhfas_B.Sum4))) : static_cast<uint32_T>(fjgadhfas_B.Sum4);

  // Outputs for Atomic SubSystem: '<S6>/Publish'
  // MATLABSystem: '<S31>/SinkBlock'
  Pub_fjgadhfas_183.publish(&fjgadhfas_B.BusAssignment4);

  // End of Outputs for SubSystem: '<S6>/Publish'
  // S-Function (saeroclockpacer): '<Root>/Simulation Pace'
  //
  //  The Clock Pacer generates no code, it is only active in
  //  interpreted simulation.


  // Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S25>/Gain1'

  fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE += fjgadhfas_P.Gain1_Gain_jk *
    fjgadhfas_B.dx * fjgadhfas_P.DiscreteTimeIntegrator_gainval;
  if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE >= fjgadhfas_P.I_max_XY) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE = fjgadhfas_P.I_max_XY;
  } else if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE <= -fjgadhfas_P.I_max_XY)
  {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE = -fjgadhfas_P.I_max_XY;
  }

  fjgadhfas_DW.DiscreteTimeIntegrator_PrevRese = static_cast<int8_T>(rtb_AND);

  // Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S26>/Gain1'

  fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n += fjgadhfas_P.Gain1_Gain_jc *
    fjgadhfas_B.dz * fjgadhfas_P.DiscreteTimeIntegrator_gainva_g;
  if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n >= fjgadhfas_P.I_max_XY) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n = fjgadhfas_P.I_max_XY;
  } else if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n <=
             -fjgadhfas_P.I_max_XY) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n = -fjgadhfas_P.I_max_XY;
  }

  fjgadhfas_DW.DiscreteTimeIntegrator_PrevRe_b = static_cast<int8_T>(rtb_AND);

  // End of Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S27>/Gain1'

  fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d += fjgadhfas_P.Gain1_Gain_j *
    fjgadhfas_B.dy * fjgadhfas_P.DiscreteTimeIntegrator_gainva_k;
  if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d >= fjgadhfas_P.I_max_Z) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d = fjgadhfas_P.I_max_Z;
  } else if (fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d <=
             -fjgadhfas_P.I_max_Z) {
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d = -fjgadhfas_P.I_max_Z;
  }

  fjgadhfas_DW.DiscreteTimeIntegrator_PrevRe_c = static_cast<int8_T>(rtb_AND);

  // End of Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator'

  // External mode
  rtExtModeUploadCheckTrigger(1);

  {                                    // Sample time: [0.0125s, 0.0s]
    rtExtModeUpload(0, (real_T)fjgadhfas_M->Timing.taskTime0);
  }

  // signal main to stop simulation
  {                                    // Sample time: [0.0125s, 0.0s]
    if ((rtmGetTFinal(fjgadhfas_M)!=-1) &&
        !((rtmGetTFinal(fjgadhfas_M)-fjgadhfas_M->Timing.taskTime0) >
          fjgadhfas_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(fjgadhfas_M, "Simulation finished");
    }

    if (rtmGetStopRequested(fjgadhfas_M)) {
      rtmSetErrorStatus(fjgadhfas_M, "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  fjgadhfas_M->Timing.taskTime0 =
    ((time_T)(++fjgadhfas_M->Timing.clockTick0)) * fjgadhfas_M->Timing.stepSize0;
}

// Model initialize function
void fjgadhfas_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(fjgadhfas_M, -1);
  fjgadhfas_M->Timing.stepSize0 = 0.0125;

  // External mode info
  fjgadhfas_M->Sizes.checksums[0] = (283978360U);
  fjgadhfas_M->Sizes.checksums[1] = (2793354092U);
  fjgadhfas_M->Sizes.checksums[2] = (1283026776U);
  fjgadhfas_M->Sizes.checksums[3] = (1148265654U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[22];
    fjgadhfas_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&fjgadhfas_DW.EnabledSubsystem_SubsysRanBC_o;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = (sysRanDType *)&fjgadhfas_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[5] = (sysRanDType *)&fjgadhfas_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[6] = (sysRanDType *)&fjgadhfas_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[7] = (sysRanDType *)&fjgadhfas_DW.EnabledSubsystem_SubsysRanBC_d;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = (sysRanDType *)&fjgadhfas_DW.EnabledSubsystem_SubsysRanBC;
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
    rteiSetModelMappingInfoPtr(fjgadhfas_M->extModeInfo,
      &fjgadhfas_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(fjgadhfas_M->extModeInfo, fjgadhfas_M->Sizes.checksums);
    rteiSetTPtr(fjgadhfas_M->extModeInfo, rtmGetTPtr(fjgadhfas_M));
  }

  // data type transition information
  {
    static DataTypeTransInfo dtInfo;
    fjgadhfas_M->SpecialInfo.mappingInfo = (&dtInfo);
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
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE =
      fjgadhfas_P.DiscreteTimeIntegrator_IC;
    fjgadhfas_DW.DiscreteTimeIntegrator_PrevRese = 2;

    // InitializeConditions for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' 
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_n =
      fjgadhfas_P.DiscreteTimeIntegrator_IC_e;
    fjgadhfas_DW.DiscreteTimeIntegrator_PrevRe_b = 2;

    // InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' 
    fjgadhfas_DW.DiscreteTimeIntegrator_DSTATE_d =
      fjgadhfas_P.DiscreteTimeIntegrator_IC_l;
    fjgadhfas_DW.DiscreteTimeIntegrator_PrevRe_c = 2;

    // SystemInitialize for Atomic SubSystem: '<S3>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S10>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S20>/In1' incorporates:
    //   Outport: '<S20>/Out1'

    fjgadhfas_B.In1 = fjgadhfas_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S10>/Enabled Subsystem'

    // Start for MATLABSystem: '<S10>/SourceBlock'
    fjgadhfas_DW.obj_k.matlabCodegenIsDeleted = false;
    fjgadhfas_DW.obj_k.isInitialized = 1;
    for (int32_T i = 0; i < 27; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[27] = '\x00';
    Sub_fjgadhfas_39.createSubscriber(&b_zeroDelimTopic[0], 1);
    fjgadhfas_DW.obj_k.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S10>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S3>/Subscribe'

    // SystemInitialize for MATLAB Function: '<S28>/MATLAB Function'
    fjgadhfas_DW.idx = 1U;

    // SystemInitialize for Atomic SubSystem: '<S2>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S8>/In1' incorporates:
    //   Outport: '<S8>/Out1'

    fjgadhfas_B.In1_p = fjgadhfas_P.Out1_Y0_k;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'

    // Start for MATLABSystem: '<S7>/SourceBlock'
    fjgadhfas_DW.obj_d.matlabCodegenIsDeleted = false;
    fjgadhfas_DW.obj_d.isInitialized = 1;
    for (int32_T i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[16] = '\x00';
    Sub_fjgadhfas_22.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    fjgadhfas_DW.obj_d.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S2>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S4>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S21>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S22>/In1' incorporates:
    //   Outport: '<S22>/Out1'

    fjgadhfas_B.In1_d = fjgadhfas_P.Out1_Y0_e;

    // End of SystemInitialize for SubSystem: '<S21>/Enabled Subsystem'

    // Start for MATLABSystem: '<S21>/SourceBlock'
    fjgadhfas_DW.obj.matlabCodegenIsDeleted = false;
    fjgadhfas_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 39; i++) {
      fjgadhfas_B.b_zeroDelimTopic[i] = tmp_1[i];
    }

    fjgadhfas_B.b_zeroDelimTopic[39] = '\x00';
    Sub_fjgadhfas_50.createSubscriber(&fjgadhfas_B.b_zeroDelimTopic[0], 1);
    fjgadhfas_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S21>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S4>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S6>/Publish'
    // Start for MATLABSystem: '<S31>/SinkBlock'
    fjgadhfas_DW.obj_n.matlabCodegenIsDeleted = false;
    fjgadhfas_DW.obj_n.isInitialized = 1;
    for (int32_T i = 0; i < 13; i++) {
      b_zeroDelimTopic_1[i] = tmp_2[i];
    }

    b_zeroDelimTopic_1[13] = '\x00';
    Pub_fjgadhfas_183.createPublisher(&b_zeroDelimTopic_1[0], 1);
    fjgadhfas_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S31>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<S6>/Publish'
  }
}

// Model terminate function
void fjgadhfas_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S3>/Subscribe'
  // Terminate for MATLABSystem: '<S10>/SourceBlock'
  if (!fjgadhfas_DW.obj_k.matlabCodegenIsDeleted) {
    fjgadhfas_DW.obj_k.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S10>/SourceBlock'
  // End of Terminate for SubSystem: '<S3>/Subscribe'

  // Terminate for Atomic SubSystem: '<S2>/Subscribe'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!fjgadhfas_DW.obj_d.matlabCodegenIsDeleted) {
    fjgadhfas_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'
  // End of Terminate for SubSystem: '<S2>/Subscribe'

  // Terminate for Atomic SubSystem: '<S4>/Subscribe'
  // Terminate for MATLABSystem: '<S21>/SourceBlock'
  if (!fjgadhfas_DW.obj.matlabCodegenIsDeleted) {
    fjgadhfas_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S21>/SourceBlock'
  // End of Terminate for SubSystem: '<S4>/Subscribe'

  // Terminate for Atomic SubSystem: '<S6>/Publish'
  // Terminate for MATLABSystem: '<S31>/SinkBlock'
  if (!fjgadhfas_DW.obj_n.matlabCodegenIsDeleted) {
    fjgadhfas_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S31>/SinkBlock'
  // End of Terminate for SubSystem: '<S6>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
