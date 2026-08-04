//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: test_position_control4.cpp
//
// Code generated for Simulink model 'test_position_control4'.
//
// Model version                  : 1.11
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Jan 15 17:46:59 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "test_position_control4.h"
#include "rtwtypes.h"
#include <math.h>
#include "test_position_control4_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>
#include "test_position_control4_types.h"
#include "rt_defines.h"
#include <float.h>
#include "test_position_control4_dt.h"

// Block signals (default storage)
B_test_position_control4_T test_position_control4_B;

// Block states (default storage)
DW_test_position_control4_T test_position_control4_DW;

// Real-time model
RT_MODEL_test_position_contro_T test_position_control4_M_ =
  RT_MODEL_test_position_contro_T();
RT_MODEL_test_position_contro_T *const test_position_control4_M =
  &test_position_control4_M_;

// Forward declaration for local functions
static void test_position_control4_cosd(real_T *x);
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
static void test_position_control4_cosd(real_T *x)
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
void test_position_control4_step(void)
{
  SL_Bus_test_position_control4_std_msgs_Bool b_varargout_2;
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_0;
  int32_T i;
  boolean_T b_varargout_1;
  boolean_T rtb_AND;
  boolean_T tmp;

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control4_DW.EnabledSubsystem_SubsysRanBC_o);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control4_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control4_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control4_DW.IfActionSubsystem2_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control4_DW.EnabledSubsystem_SubsysRanBC_d);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control4_DW.EnabledSubsystem_SubsysRanBC);

  // Outputs for Atomic SubSystem: '<S3>/Subscribe'
  // MATLABSystem: '<S10>/SourceBlock'
  b_varargout_1 = Sub_test_position_control4_39.getLatestMessage
    (&test_position_control4_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S20>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S20>/In1'
    test_position_control4_B.In1 = test_position_control4_B.b_varargout_2;
    srUpdateBC(test_position_control4_DW.EnabledSubsystem_SubsysRanBC_d);
  }

  // End of MATLABSystem: '<S10>/SourceBlock'
  // End of Outputs for SubSystem: '<S10>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S3>/Subscribe'

  // Gain: '<S3>/Gain'
  test_position_control4_B.x = test_position_control4_P.Gain_Gain *
    test_position_control4_B.In1.Pose.Position.Y;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  test_position_control4_B.X = test_position_control4_B.In1.Pose.Position.X;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  test_position_control4_B.Z = test_position_control4_B.In1.Pose.Position.Z;

  // MATLAB Function: '<S28>/MATLAB Function' incorporates:
  //   Constant: '<S28>/Constant'

  if (test_position_control4_DW.filled == 0) {
    test_position_control4_DW.bufX[test_position_control4_DW.idx - 1] =
      test_position_control4_B.x;
    test_position_control4_DW.bufY[test_position_control4_DW.idx - 1] =
      test_position_control4_B.X;
    test_position_control4_DW.bufZ[test_position_control4_DW.idx - 1] =
      test_position_control4_B.Z;
    test_position_control4_DW.filled = 1U;
    test_position_control4_DW.idx = 2U;
    test_position_control4_B.Valid = true;
    test_position_control4_B.frozenNow = false;
    test_position_control4_B.filled_ = 0U;
    test_position_control4_B.updated = false;
    test_position_control4_B.d = -1.0;
    test_position_control4_B.v = -1.0;
  } else {
    uint32_T qY;
    uint8_T prevIdx;
    qY = test_position_control4_DW.idx - 1U;
    if (test_position_control4_DW.idx - 1U > test_position_control4_DW.idx) {
      qY = 0U;
    }

    prevIdx = static_cast<uint8_T>(qY);
    if (static_cast<uint8_T>(qY) == 0) {
      prevIdx = 6U;
    }

    test_position_control4_B.dx = test_position_control4_B.x -
      test_position_control4_DW.bufX[prevIdx - 1];
    test_position_control4_B.dy = test_position_control4_B.X -
      test_position_control4_DW.bufY[prevIdx - 1];
    test_position_control4_B.dz = test_position_control4_B.Z -
      test_position_control4_DW.bufZ[prevIdx - 1];
    test_position_control4_B.d = sqrt((test_position_control4_B.dx *
      test_position_control4_B.dx + test_position_control4_B.dy *
      test_position_control4_B.dy) + test_position_control4_B.dz *
      test_position_control4_B.dz);
    test_position_control4_B.v = test_position_control4_B.d /
      test_position_control4_P.time_step;
    test_position_control4_B.updated = (test_position_control4_B.d > 1.0E-6);
    test_position_control4_B.frozenNow = false;
    if (test_position_control4_DW.filled >= 6) {
      boolean_T exitg1;
      test_position_control4_B.frozenNow = true;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 5)) {
        int32_T ddx_tmp_tmp;
        ddx_tmp_tmp = prevIdx - 1;
        test_position_control4_B.dx = test_position_control4_B.x -
          test_position_control4_DW.bufX[prevIdx - 1];
        test_position_control4_B.dy = test_position_control4_B.X -
          test_position_control4_DW.bufY[prevIdx - 1];
        test_position_control4_B.dz = test_position_control4_B.Z -
          test_position_control4_DW.bufZ[prevIdx - 1];
        if (sqrt((test_position_control4_B.dx * test_position_control4_B.dx +
                  test_position_control4_B.dy * test_position_control4_B.dy) +
                 test_position_control4_B.dz * test_position_control4_B.dz) >
            1.0E-6) {
          test_position_control4_B.frozenNow = false;
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

    if (!test_position_control4_DW.inLost) {
      if ((test_position_control4_B.v > 20.0) ||
          test_position_control4_B.frozenNow) {
        test_position_control4_DW.inLost = true;
        test_position_control4_DW.goodCnt = 0U;
        test_position_control4_B.Valid = false;
      } else {
        test_position_control4_B.Valid = true;
      }
    } else if (test_position_control4_B.updated && (test_position_control4_B.v <=
                20.0)) {
      if (test_position_control4_DW.goodCnt < 255) {
        test_position_control4_DW.goodCnt = static_cast<uint8_T>
          (test_position_control4_DW.goodCnt + 1U);
      }

      if (test_position_control4_DW.goodCnt >= 5) {
        test_position_control4_DW.inLost = false;
        test_position_control4_DW.goodCnt = 0U;
        test_position_control4_B.Valid = true;
      } else {
        test_position_control4_B.Valid = false;
      }
    } else {
      if (test_position_control4_B.v > 20.0) {
        test_position_control4_DW.goodCnt = 0U;
      }

      test_position_control4_B.Valid = false;
    }

    test_position_control4_DW.bufX[test_position_control4_DW.idx - 1] =
      test_position_control4_B.x;
    test_position_control4_DW.bufY[test_position_control4_DW.idx - 1] =
      test_position_control4_B.X;
    test_position_control4_DW.bufZ[test_position_control4_DW.idx - 1] =
      test_position_control4_B.Z;
    if (test_position_control4_DW.filled < 6) {
      test_position_control4_DW.filled = static_cast<uint8_T>
        (test_position_control4_DW.filled + 1U);
    }

    i = static_cast<int32_T>(test_position_control4_DW.idx + 1U);
    if (test_position_control4_DW.idx + 1U > 255U) {
      i = 255;
    }

    test_position_control4_DW.idx = static_cast<uint8_T>(i);
    if (test_position_control4_DW.idx > 6) {
      test_position_control4_DW.idx = 1U;
    }

    test_position_control4_B.filled_ = test_position_control4_DW.filled;
  }

  // End of MATLAB Function: '<S28>/MATLAB Function'

  // Sqrt: '<S18>/sqrt' incorporates:
  //   Product: '<S19>/Product'
  //   Product: '<S19>/Product1'
  //   Product: '<S19>/Product2'
  //   Product: '<S19>/Product3'
  //   Sum: '<S19>/Sum'

  test_position_control4_B.dz = sqrt
    (((test_position_control4_B.In1.Pose.Orientation.W *
       test_position_control4_B.In1.Pose.Orientation.W +
       test_position_control4_B.In1.Pose.Orientation.X *
       test_position_control4_B.In1.Pose.Orientation.X) +
      test_position_control4_B.In1.Pose.Orientation.Y *
      test_position_control4_B.In1.Pose.Orientation.Y) +
     test_position_control4_B.In1.Pose.Orientation.Z *
     test_position_control4_B.In1.Pose.Orientation.Z);

  // Product: '<S13>/Product'
  test_position_control4_B.dy = test_position_control4_B.In1.Pose.Orientation.W /
    test_position_control4_B.dz;

  // Product: '<S13>/Product1'
  test_position_control4_B.Sum4 =
    test_position_control4_B.In1.Pose.Orientation.X /
    test_position_control4_B.dz;

  // Product: '<S13>/Product2'
  test_position_control4_B.Product2 =
    test_position_control4_B.In1.Pose.Orientation.Y /
    test_position_control4_B.dz;

  // Product: '<S13>/Product3'
  test_position_control4_B.dz = test_position_control4_B.In1.Pose.Orientation.Z /
    test_position_control4_B.dz;

  // Fcn: '<S11>/fcn2' incorporates:
  //   Fcn: '<S11>/fcn5'

  test_position_control4_B.VectorConcatenate_tmp = test_position_control4_B.dy *
    test_position_control4_B.dy;
  test_position_control4_B.VectorConcatenate_tmp_c =
    test_position_control4_B.Sum4 * test_position_control4_B.Sum4;
  VectorConcatenate_tmp = test_position_control4_B.Product2 *
    test_position_control4_B.Product2;
  VectorConcatenate_tmp_0 = test_position_control4_B.dz *
    test_position_control4_B.dz;

  // Trigonometry: '<S12>/Trigonometric Function1' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn1'
  //   Fcn: '<S11>/fcn2'

  test_position_control4_B.VectorConcatenate[0] = rt_atan2d_snf
    ((test_position_control4_B.Product2 * test_position_control4_B.dz -
      test_position_control4_B.dy * test_position_control4_B.Sum4) * -2.0,
     ((test_position_control4_B.VectorConcatenate_tmp -
       test_position_control4_B.VectorConcatenate_tmp_c) - VectorConcatenate_tmp)
     + VectorConcatenate_tmp_0);

  // Fcn: '<S11>/fcn3'
  test_position_control4_B.dx = (test_position_control4_B.Sum4 *
    test_position_control4_B.dz + test_position_control4_B.dy *
    test_position_control4_B.Product2) * 2.0;

  // If: '<S14>/If' incorporates:
  //   Constant: '<S15>/Constant'
  //   Constant: '<S16>/Constant'

  if (test_position_control4_B.dx > 1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    test_position_control4_B.dx = test_position_control4_P.Constant_Value_ey;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S15>/Constant'

    srUpdateBC(test_position_control4_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem'
  } else if (test_position_control4_B.dx < -1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    test_position_control4_B.dx = test_position_control4_P.Constant_Value_b;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S16>/Constant'

    srUpdateBC(test_position_control4_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S14>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S17>/Action Port'

    // Update for If: '<S14>/If'
    srUpdateBC(test_position_control4_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem2'
  }

  // End of If: '<S14>/If'

  // Trigonometry: '<S12>/trigFcn' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'

  if (test_position_control4_B.dx > 1.0) {
    test_position_control4_B.dx = 1.0;
  } else if (test_position_control4_B.dx < -1.0) {
    test_position_control4_B.dx = -1.0;
  }

  test_position_control4_B.VectorConcatenate[1] = asin
    (test_position_control4_B.dx);

  // End of Trigonometry: '<S12>/trigFcn'

  // Trigonometry: '<S12>/Trigonometric Function3' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn4'
  //   Fcn: '<S11>/fcn5'

  test_position_control4_B.VectorConcatenate[2] = rt_atan2d_snf
    ((test_position_control4_B.Sum4 * test_position_control4_B.Product2 -
      test_position_control4_B.dy * test_position_control4_B.dz) * -2.0,
     ((test_position_control4_B.VectorConcatenate_tmp +
       test_position_control4_B.VectorConcatenate_tmp_c) - VectorConcatenate_tmp)
     - VectorConcatenate_tmp_0);

  // Outputs for Atomic SubSystem: '<S2>/Subscribe'
  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = Sub_test_position_control4_22.getLatestMessage(&b_varargout_2);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    test_position_control4_B.In1_p = b_varargout_2;
    srUpdateBC(test_position_control4_DW.EnabledSubsystem_SubsysRanBC_o);
  }

  // End of MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S2>/Subscribe'

  // Logic: '<S5>/AND'
  rtb_AND = (test_position_control4_B.Valid &&
             test_position_control4_B.In1_p.Data);

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  if (rtb_AND && (test_position_control4_DW.DiscreteTimeIntegrator_PrevRese <= 0))
  {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control4_P.DiscreteTimeIntegrator_IC;
  }

  if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE >=
      test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control4_P.I_max_XY;
  } else if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE <=
             -test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE =
      -test_position_control4_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  test_position_control4_B.DiscreteTimeIntegrator =
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE;

  // Sum: '<S5>/Sum' incorporates:
  //   Constant: '<S5>/X_ref'

  test_position_control4_B.dx = test_position_control4_P.X_ref_Value -
    test_position_control4_B.x;

  // Gain: '<S25>/Gain'
  test_position_control4_B.Gain = test_position_control4_P.Gain_Gain_g *
    test_position_control4_B.dx;

  // Outputs for Atomic SubSystem: '<S4>/Subscribe'
  // MATLABSystem: '<S21>/SourceBlock'
  b_varargout_1 = Sub_test_position_control4_50.getLatestMessage
    (&test_position_control4_B.b_varargout_2_m);

  // Outputs for Enabled SubSystem: '<S21>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S22>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S22>/In1'
    test_position_control4_B.In1_d = test_position_control4_B.b_varargout_2_m;
    srUpdateBC(test_position_control4_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S21>/SourceBlock'
  // End of Outputs for SubSystem: '<S21>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S4>/Subscribe'

  // Gain: '<S4>/Gain' incorporates:
  //   SignalConversion generated from: '<S4>/Bus Selector'

  test_position_control4_B.x_d = test_position_control4_P.Gain_Gain_n *
    test_position_control4_B.In1_d.Twist.Linear.Y;

  // Gain: '<S25>/Gain2'
  test_position_control4_B.Gain2 = test_position_control4_P.Gain2_Gain *
    test_position_control4_B.x_d;

  // Sum: '<S25>/Sum3'
  test_position_control4_B.dy = (test_position_control4_B.DiscreteTimeIntegrator
    + test_position_control4_B.Gain) - test_position_control4_B.Gain2;

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  if (rtb_AND && (test_position_control4_DW.DiscreteTimeIntegrator_PrevRe_h <= 0))
  {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j =
      test_position_control4_P.DiscreteTimeIntegrator_IC_f;
  }

  if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j >=
      test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j =
      test_position_control4_P.I_max_XY;
  } else if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j <=
             -test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j =
      -test_position_control4_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  test_position_control4_B.DiscreteTimeIntegrator_m =
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j;

  // Sum: '<S5>/Sum1' incorporates:
  //   Constant: '<S5>/Y_ref'

  test_position_control4_B.dz = test_position_control4_P.Y_ref_Value -
    test_position_control4_B.X;

  // Gain: '<S26>/Gain'
  test_position_control4_B.Gain_o = test_position_control4_P.Gain_Gain_h *
    test_position_control4_B.dz;

  // SignalConversion generated from: '<S4>/Bus Selector'
  test_position_control4_B.X_h = test_position_control4_B.In1_d.Twist.Linear.X;

  // Gain: '<S26>/Gain2'
  test_position_control4_B.Gain2_h = test_position_control4_P.Gain2_Gain_j *
    test_position_control4_B.X_h;

  // Sum: '<S26>/Sum3'
  test_position_control4_B.Product2 =
    (test_position_control4_B.DiscreteTimeIntegrator_m +
     test_position_control4_B.Gain_o) - test_position_control4_B.Gain2_h;

  // MATLAB Function: '<S5>/MATLAB Function'
  test_position_control4_B.VectorConcatenate_tmp = cos
    (test_position_control4_B.VectorConcatenate[2]);
  test_position_control4_B.VectorConcatenate_tmp_c = sin
    (test_position_control4_B.VectorConcatenate[2]);
  test_position_control4_B.Sum4 = -test_position_control4_B.Product2 *
    test_position_control4_B.VectorConcatenate_tmp_c -
    test_position_control4_B.dy * test_position_control4_B.VectorConcatenate_tmp;
  test_position_control4_B.Product2 = -test_position_control4_B.Product2 *
    test_position_control4_B.VectorConcatenate_tmp + test_position_control4_B.dy
    * test_position_control4_B.VectorConcatenate_tmp_c;

  // Switch: '<S5>/Switch1'
  if (test_position_control4_B.Valid) {
    // Switch: '<S5>/Switch1'
    test_position_control4_B.Switch1 = test_position_control4_B.Product2;
  } else {
    // Switch: '<S5>/Switch1' incorporates:
    //   Constant: '<S5>/Constant1'

    test_position_control4_B.Switch1 = test_position_control4_P.Constant1_Value;
  }

  // End of Switch: '<S5>/Switch1'

  // Saturate: '<Root>/Saturation'
  if (test_position_control4_B.Switch1 >
      test_position_control4_P.Saturation_UpperSat) {
    // Saturate: '<Root>/Saturation'
    test_position_control4_B.Saturation =
      test_position_control4_P.Saturation_UpperSat;
  } else if (test_position_control4_B.Switch1 <
             test_position_control4_P.Saturation_LowerSat) {
    // Saturate: '<Root>/Saturation'
    test_position_control4_B.Saturation =
      test_position_control4_P.Saturation_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation'
    test_position_control4_B.Saturation = test_position_control4_B.Switch1;
  }

  // End of Saturate: '<Root>/Saturation'

  // Sum: '<S1>/Sum' incorporates:
  //   Constant: '<S1>/Trim'
  //   Gain: '<S1>/Gain'
  //   Gain: '<S1>/Gain1'

  test_position_control4_B.Sum = test_position_control4_P.Gain_Gain_hz *
    test_position_control4_B.Saturation * test_position_control4_P.Gain1_Gain +
    test_position_control4_P.Trim_Value;

  // Switch: '<S5>/Switch'
  if (test_position_control4_B.Valid) {
    // Switch: '<S5>/Switch'
    test_position_control4_B.Switch = test_position_control4_B.Sum4;
  } else {
    // Switch: '<S5>/Switch' incorporates:
    //   Constant: '<S5>/Constant'

    test_position_control4_B.Switch = test_position_control4_P.Constant_Value_k;
  }

  // End of Switch: '<S5>/Switch'

  // Saturate: '<Root>/Saturation1'
  if (test_position_control4_B.Switch >
      test_position_control4_P.Saturation1_UpperSat) {
    // Saturate: '<Root>/Saturation1'
    test_position_control4_B.Saturation1 =
      test_position_control4_P.Saturation1_UpperSat;
  } else if (test_position_control4_B.Switch <
             test_position_control4_P.Saturation1_LowerSat) {
    // Saturate: '<Root>/Saturation1'
    test_position_control4_B.Saturation1 =
      test_position_control4_P.Saturation1_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation1'
    test_position_control4_B.Saturation1 = test_position_control4_B.Switch;
  }

  // End of Saturate: '<Root>/Saturation1'

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Trim1'
  //   Gain: '<S1>/Gain2'
  //   Gain: '<S1>/Gain3'

  test_position_control4_B.Sum1 = test_position_control4_P.Gain2_Gain_je *
    test_position_control4_B.Saturation1 * test_position_control4_P.Gain3_Gain +
    test_position_control4_P.Trim1_Value;

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  if (rtb_AND && (test_position_control4_DW.DiscreteTimeIntegrator_PrevRe_f <= 0))
  {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g =
      test_position_control4_P.DiscreteTimeIntegrator_IC_m;
  }

  if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g >=
      test_position_control4_P.I_max_Z) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g =
      test_position_control4_P.I_max_Z;
  } else if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g <=
             -test_position_control4_P.I_max_Z) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g =
      -test_position_control4_P.I_max_Z;
  }

  // DiscreteIntegrator: '<S27>/Discrete-Time Integrator'
  test_position_control4_B.DiscreteTimeIntegrator_i =
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g;

  // Sum: '<S5>/Sum2' incorporates:
  //   Constant: '<S5>/Z_ref'

  test_position_control4_B.dy = test_position_control4_P.Z_ref_Value -
    test_position_control4_B.Z;

  // Gain: '<S27>/Gain'
  test_position_control4_B.Gain_g = test_position_control4_P.Gain_Gain_e *
    test_position_control4_B.dy;

  // SignalConversion generated from: '<S4>/Bus Selector'
  test_position_control4_B.Z_n = test_position_control4_B.In1_d.Twist.Linear.Z;

  // Gain: '<S27>/Gain2'
  test_position_control4_B.Gain2_f = test_position_control4_P.Gain2_Gain_p *
    test_position_control4_B.Z_n;

  // MATLAB Function: '<S5>/MATLAB Function1'
  test_position_control4_B.Sum4 = 0.5 *
    test_position_control4_B.VectorConcatenate[1] + 0.5 *
    test_position_control4_B.Sum4;
  test_position_control4_cosd(&test_position_control4_B.Sum4);
  test_position_control4_B.Product2 = 0.5 *
    test_position_control4_B.VectorConcatenate[0] + 0.5 *
    test_position_control4_B.Product2;
  test_position_control4_cosd(&test_position_control4_B.Product2);

  // Switch: '<S5>/Switch2'
  if (test_position_control4_B.Valid) {
    // Switch: '<S5>/Switch2' incorporates:
    //   MATLAB Function: '<S5>/MATLAB Function1'
    //   Sum: '<S27>/Sum3'

    test_position_control4_B.Switch2 =
      ((test_position_control4_B.DiscreteTimeIntegrator_i +
        test_position_control4_B.Gain_g) - test_position_control4_B.Gain2_f) /
      test_position_control4_B.Sum4 / test_position_control4_B.Product2;
  } else {
    // Switch: '<S5>/Switch2' incorporates:
    //   Constant: '<S5>/Constant2'

    test_position_control4_B.Switch2 = test_position_control4_P.Constant2_Value;
  }

  // End of Switch: '<S5>/Switch2'

  // Saturate: '<Root>/Saturation2'
  if (test_position_control4_B.Switch2 >
      test_position_control4_P.Saturation2_UpperSat) {
    // Saturate: '<Root>/Saturation2'
    test_position_control4_B.Saturation2 =
      test_position_control4_P.Saturation2_UpperSat;
  } else if (test_position_control4_B.Switch2 <
             test_position_control4_P.Saturation2_LowerSat) {
    // Saturate: '<Root>/Saturation2'
    test_position_control4_B.Saturation2 =
      test_position_control4_P.Saturation2_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation2'
    test_position_control4_B.Saturation2 = test_position_control4_B.Switch2;
  }

  // End of Saturate: '<Root>/Saturation2'

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.Sum4 = floor(test_position_control4_B.Sum);
  if (rtIsNaN(test_position_control4_B.Sum4) || rtIsInf
      (test_position_control4_B.Sum4)) {
    test_position_control4_B.Sum4 = 0.0;
  } else {
    test_position_control4_B.Sum4 = fmod(test_position_control4_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[0] = static_cast<uint16_T>
    (test_position_control4_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control4_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.Sum4 = floor(test_position_control4_B.Sum1);
  if (rtIsNaN(test_position_control4_B.Sum4) || rtIsInf
      (test_position_control4_B.Sum4)) {
    test_position_control4_B.Sum4 = 0.0;
  } else {
    test_position_control4_B.Sum4 = fmod(test_position_control4_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[1] = static_cast<uint16_T>
    (test_position_control4_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control4_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S1>/Thrust for hover'
  //   Gain: '<S1>/From motor test stand'
  //   Sum: '<S1>/Sum4'

  test_position_control4_B.Sum4 = floor
    (test_position_control4_P.Frommotorteststand_Gain *
     test_position_control4_B.Saturation2 +
     test_position_control4_P.MOT_THST_HOVER_MCS);
  if (rtIsNaN(test_position_control4_B.Sum4) || rtIsInf
      (test_position_control4_B.Sum4)) {
    test_position_control4_B.Sum4 = 0.0;
  } else {
    test_position_control4_B.Sum4 = fmod(test_position_control4_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[2] = static_cast<uint16_T>
    (test_position_control4_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control4_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Zero2'

  test_position_control4_B.Sum4 = floor(test_position_control4_P.Zero2_Value);
  if (rtIsNaN(test_position_control4_B.Sum4) || rtIsInf
      (test_position_control4_B.Sum4)) {
    test_position_control4_B.Sum4 = 0.0;
  } else {
    test_position_control4_B.Sum4 = fmod(test_position_control4_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[3] = static_cast<uint16_T>
    (test_position_control4_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control4_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero'

  test_position_control4_B.Sum4 = floor(test_position_control4_P.Zero_Value);
  b_varargout_1 = rtIsNaN(test_position_control4_B.Sum4);
  tmp = rtIsInf(test_position_control4_B.Sum4);
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[4] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<
      uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Flight Mode'

  test_position_control4_B.Product2 = floor(test_position_control4_P.STABILIZE);
  if (rtIsNaN(test_position_control4_B.Product2) || rtIsInf
      (test_position_control4_B.Product2)) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Product2,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[5] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<
      uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[6] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[7] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[8] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[9] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[10] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[11] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[12] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control4_B.DataTypeConversion[13] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control4_B.Product2 = 0.0;
    test_position_control4_B.Sum4 = 0.0;
  } else {
    test_position_control4_B.Product2 = fmod(test_position_control4_B.Sum4,
      65536.0);
    test_position_control4_B.Sum4 = test_position_control4_B.Product2;
  }

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero3'

  test_position_control4_B.DataTypeConversion[14] = static_cast<uint16_T>
    (test_position_control4_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control4_B.Product2)));
  test_position_control4_B.DataTypeConversion[15] = static_cast<uint16_T>
    (test_position_control4_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control4_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control4_B.Sum4)));
  for (i = 0; i < 112; i++) {
    test_position_control4_B.Sum4 = floor(test_position_control4_P.Zero3_Value[i]);
    if (rtIsNaN(test_position_control4_B.Sum4) || rtIsInf
        (test_position_control4_B.Sum4)) {
      test_position_control4_B.Sum4 = 0.0;
    } else {
      test_position_control4_B.Sum4 = fmod(test_position_control4_B.Sum4,
        65536.0);
    }

    test_position_control4_B.DataTypeConversion[i + 16] = static_cast<uint16_T>
      (test_position_control4_B.Sum4 < 0.0 ? static_cast<int32_T>
       (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
          (-test_position_control4_B.Sum4)))) : static_cast<int32_T>(
        static_cast<uint16_T>(test_position_control4_B.Sum4)));
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   Constant: '<S30>/Constant'

  test_position_control4_B.BusAssignment4 =
    test_position_control4_P.Constant_Value;
  memcpy(&test_position_control4_B.BusAssignment4.Data[0],
         &test_position_control4_B.DataTypeConversion[0], sizeof(uint16_T) << 7U);

  // DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
  //   Constant: '<S6>/Constant'

  test_position_control4_B.Sum4 = floor
    (test_position_control4_P.Constant_Value_a);
  if (rtIsNaN(test_position_control4_B.Sum4) || rtIsInf
      (test_position_control4_B.Sum4)) {
    test_position_control4_B.Sum4 = 0.0;
  } else {
    test_position_control4_B.Sum4 = fmod(test_position_control4_B.Sum4,
      4.294967296E+9);
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   DataTypeConversion: '<S6>/Data Type Conversion1'

  test_position_control4_B.BusAssignment4.Data_SL_Info.CurrentLength =
    test_position_control4_B.Sum4 < 0.0 ? static_cast<uint32_T>
    (-static_cast<int32_T>(static_cast<uint32_T>(-test_position_control4_B.Sum4)))
    : static_cast<uint32_T>(test_position_control4_B.Sum4);

  // Outputs for Atomic SubSystem: '<S6>/Publish'
  // MATLABSystem: '<S31>/SinkBlock'
  Pub_test_position_control4_137.publish
    (&test_position_control4_B.BusAssignment4);

  // End of Outputs for SubSystem: '<S6>/Publish'
  // S-Function (saeroclockpacer): '<Root>/Simulation Pace'
  //
  //  The Clock Pacer generates no code, it is only active in
  //  interpreted simulation.


  // Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S25>/Gain1'

  test_position_control4_DW.DiscreteTimeIntegrator_DSTATE +=
    test_position_control4_P.Gain1_Gain_mj * test_position_control4_B.dx *
    test_position_control4_P.DiscreteTimeIntegrator_gainval;
  if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE >=
      test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control4_P.I_max_XY;
  } else if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE <=
             -test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE =
      -test_position_control4_P.I_max_XY;
  }

  test_position_control4_DW.DiscreteTimeIntegrator_PrevRese = static_cast<int8_T>
    (rtb_AND);

  // Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S26>/Gain1'

  test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j +=
    test_position_control4_P.Gain1_Gain_o * test_position_control4_B.dz *
    test_position_control4_P.DiscreteTimeIntegrator_gainva_d;
  if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j >=
      test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j =
      test_position_control4_P.I_max_XY;
  } else if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j <=
             -test_position_control4_P.I_max_XY) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j =
      -test_position_control4_P.I_max_XY;
  }

  test_position_control4_DW.DiscreteTimeIntegrator_PrevRe_h = static_cast<int8_T>
    (rtb_AND);

  // End of Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  //   Gain: '<S27>/Gain1'

  test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g +=
    test_position_control4_P.Gain1_Gain_m * test_position_control4_B.dy *
    test_position_control4_P.DiscreteTimeIntegrator_gainva_i;
  if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g >=
      test_position_control4_P.I_max_Z) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g =
      test_position_control4_P.I_max_Z;
  } else if (test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g <=
             -test_position_control4_P.I_max_Z) {
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g =
      -test_position_control4_P.I_max_Z;
  }

  test_position_control4_DW.DiscreteTimeIntegrator_PrevRe_f = static_cast<int8_T>
    (rtb_AND);

  // End of Update for DiscreteIntegrator: '<S27>/Discrete-Time Integrator'

  // External mode
  rtExtModeUploadCheckTrigger(1);

  {                                    // Sample time: [0.0125s, 0.0s]
    rtExtModeUpload(0, (real_T)test_position_control4_M->Timing.taskTime0);
  }

  // signal main to stop simulation
  {                                    // Sample time: [0.0125s, 0.0s]
    if ((rtmGetTFinal(test_position_control4_M)!=-1) &&
        !((rtmGetTFinal(test_position_control4_M)-
           test_position_control4_M->Timing.taskTime0) >
          test_position_control4_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(test_position_control4_M, "Simulation finished");
    }

    if (rtmGetStopRequested(test_position_control4_M)) {
      rtmSetErrorStatus(test_position_control4_M, "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  test_position_control4_M->Timing.taskTime0 =
    ((time_T)(++test_position_control4_M->Timing.clockTick0)) *
    test_position_control4_M->Timing.stepSize0;
}

// Model initialize function
void test_position_control4_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(test_position_control4_M, -1);
  test_position_control4_M->Timing.stepSize0 = 0.0125;

  // External mode info
  test_position_control4_M->Sizes.checksums[0] = (660936932U);
  test_position_control4_M->Sizes.checksums[1] = (2103336317U);
  test_position_control4_M->Sizes.checksums[2] = (719634648U);
  test_position_control4_M->Sizes.checksums[3] = (3843670039U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[22];
    test_position_control4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &test_position_control4_DW.EnabledSubsystem_SubsysRanBC_o;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = (sysRanDType *)
      &test_position_control4_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[5] = (sysRanDType *)
      &test_position_control4_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[6] = (sysRanDType *)
      &test_position_control4_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[7] = (sysRanDType *)
      &test_position_control4_DW.EnabledSubsystem_SubsysRanBC_d;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = (sysRanDType *)
      &test_position_control4_DW.EnabledSubsystem_SubsysRanBC;
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
    rteiSetModelMappingInfoPtr(test_position_control4_M->extModeInfo,
      &test_position_control4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test_position_control4_M->extModeInfo,
                        test_position_control4_M->Sizes.checksums);
    rteiSetTPtr(test_position_control4_M->extModeInfo, rtmGetTPtr
                (test_position_control4_M));
  }

  // data type transition information
  {
    static DataTypeTransInfo dtInfo;
    test_position_control4_M->SpecialInfo.mappingInfo = (&dtInfo);
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
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control4_P.DiscreteTimeIntegrator_IC;
    test_position_control4_DW.DiscreteTimeIntegrator_PrevRese = 2;

    // InitializeConditions for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' 
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_j =
      test_position_control4_P.DiscreteTimeIntegrator_IC_f;
    test_position_control4_DW.DiscreteTimeIntegrator_PrevRe_h = 2;

    // InitializeConditions for DiscreteIntegrator: '<S27>/Discrete-Time Integrator' 
    test_position_control4_DW.DiscreteTimeIntegrator_DSTATE_g =
      test_position_control4_P.DiscreteTimeIntegrator_IC_m;
    test_position_control4_DW.DiscreteTimeIntegrator_PrevRe_f = 2;

    // SystemInitialize for Atomic SubSystem: '<S3>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S10>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S20>/In1' incorporates:
    //   Outport: '<S20>/Out1'

    test_position_control4_B.In1 = test_position_control4_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S10>/Enabled Subsystem'

    // Start for MATLABSystem: '<S10>/SourceBlock'
    test_position_control4_DW.obj_k.matlabCodegenIsDeleted = false;
    test_position_control4_DW.obj_k.isInitialized = 1;
    for (int32_T i = 0; i < 27; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[27] = '\x00';
    Sub_test_position_control4_39.createSubscriber(&b_zeroDelimTopic[0], 1);
    test_position_control4_DW.obj_k.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S10>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S3>/Subscribe'

    // SystemInitialize for MATLAB Function: '<S28>/MATLAB Function'
    test_position_control4_DW.idx = 1U;

    // SystemInitialize for Atomic SubSystem: '<S2>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S8>/In1' incorporates:
    //   Outport: '<S8>/Out1'

    test_position_control4_B.In1_p = test_position_control4_P.Out1_Y0_k;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'

    // Start for MATLABSystem: '<S7>/SourceBlock'
    test_position_control4_DW.obj_d.matlabCodegenIsDeleted = false;
    test_position_control4_DW.obj_d.isInitialized = 1;
    for (int32_T i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[16] = '\x00';
    Sub_test_position_control4_22.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    test_position_control4_DW.obj_d.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S2>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S4>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S21>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S22>/In1' incorporates:
    //   Outport: '<S22>/Out1'

    test_position_control4_B.In1_d = test_position_control4_P.Out1_Y0_e;

    // End of SystemInitialize for SubSystem: '<S21>/Enabled Subsystem'

    // Start for MATLABSystem: '<S21>/SourceBlock'
    test_position_control4_DW.obj.matlabCodegenIsDeleted = false;
    test_position_control4_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 39; i++) {
      test_position_control4_B.b_zeroDelimTopic[i] = tmp_1[i];
    }

    test_position_control4_B.b_zeroDelimTopic[39] = '\x00';
    Sub_test_position_control4_50.createSubscriber
      (&test_position_control4_B.b_zeroDelimTopic[0], 1);
    test_position_control4_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S21>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S4>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S6>/Publish'
    // Start for MATLABSystem: '<S31>/SinkBlock'
    test_position_control4_DW.obj_e.matlabCodegenIsDeleted = false;
    test_position_control4_DW.obj_e.isInitialized = 1;
    for (int32_T i = 0; i < 13; i++) {
      b_zeroDelimTopic_1[i] = tmp_2[i];
    }

    b_zeroDelimTopic_1[13] = '\x00';
    Pub_test_position_control4_137.createPublisher(&b_zeroDelimTopic_1[0], 1);
    test_position_control4_DW.obj_e.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S31>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<S6>/Publish'
  }
}

// Model terminate function
void test_position_control4_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S3>/Subscribe'
  // Terminate for MATLABSystem: '<S10>/SourceBlock'
  if (!test_position_control4_DW.obj_k.matlabCodegenIsDeleted) {
    test_position_control4_DW.obj_k.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S10>/SourceBlock'
  // End of Terminate for SubSystem: '<S3>/Subscribe'

  // Terminate for Atomic SubSystem: '<S2>/Subscribe'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!test_position_control4_DW.obj_d.matlabCodegenIsDeleted) {
    test_position_control4_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'
  // End of Terminate for SubSystem: '<S2>/Subscribe'

  // Terminate for Atomic SubSystem: '<S4>/Subscribe'
  // Terminate for MATLABSystem: '<S21>/SourceBlock'
  if (!test_position_control4_DW.obj.matlabCodegenIsDeleted) {
    test_position_control4_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S21>/SourceBlock'
  // End of Terminate for SubSystem: '<S4>/Subscribe'

  // Terminate for Atomic SubSystem: '<S6>/Publish'
  // Terminate for MATLABSystem: '<S31>/SinkBlock'
  if (!test_position_control4_DW.obj_e.matlabCodegenIsDeleted) {
    test_position_control4_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S31>/SinkBlock'
  // End of Terminate for SubSystem: '<S6>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
