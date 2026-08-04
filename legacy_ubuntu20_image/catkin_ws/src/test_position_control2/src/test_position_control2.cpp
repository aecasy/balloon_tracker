//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: test_position_control2.cpp
//
// Code generated for Simulink model 'test_position_control2'.
//
// Model version                  : 1.13
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Tue Dec 30 16:34:23 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "test_position_control2.h"
#include "rtwtypes.h"
#include <math.h>

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>
#include "test_position_control2_private.h"
#include "rt_defines.h"
#include "test_position_control2_dt.h"

// Block signals (default storage)
B_test_position_control2_T test_position_control2_B;

// Block states (default storage)
DW_test_position_control2_T test_position_control2_DW;

// Real-time model
RT_MODEL_test_position_contro_T test_position_control2_M_ =
  RT_MODEL_test_position_contro_T();
RT_MODEL_test_position_contro_T *const test_position_control2_M =
  &test_position_control2_M_;
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

// Model step function
void test_position_control2_step(void)
{
  real_T DiscreteTransferFcn1_tmp;
  real_T DiscreteTransferFcn_tmp;
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_0;
  real_T VectorConcatenate_tmp_1;
  real_T VectorConcatenate_tmp_2;
  boolean_T b_varargout_1;
  boolean_T tmp;

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control2_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control2_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control2_DW.IfActionSubsystem2_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control2_DW.EnabledSubsystem_SubsysRanBC);

  // Outputs for Atomic SubSystem: '<S2>/Subscribe'
  // MATLABSystem: '<S6>/SourceBlock'
  b_varargout_1 = Sub_test_position_control2_15.getLatestMessage
    (&test_position_control2_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S16>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S16>/In1'
    test_position_control2_B.In1 = test_position_control2_B.b_varargout_2;
    srUpdateBC(test_position_control2_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S6>/SourceBlock'
  // End of Outputs for SubSystem: '<S6>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S2>/Subscribe'

  // Gain: '<S2>/Gain'
  test_position_control2_B.x = test_position_control2_P.Gain_Gain *
    test_position_control2_B.In1.Pose.Position.Y;

  // Sum: '<S3>/Sum' incorporates:
  //   Constant: '<S3>/X_ref'

  test_position_control2_B.Product2 = test_position_control2_P.X_ref_Value -
    test_position_control2_B.x;

  // DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn1' incorporates:
  //   Gain: '<S3>/Gain2'
  //   Gain: '<S3>/Gain7'

  DiscreteTransferFcn1_tmp = (test_position_control2_P.Gain7_Gain *
    test_position_control2_B.x * test_position_control2_P.Gain2_Gain -
    test_position_control2_P.DiscreteTransferFcn1_DenCoef[1] *
    test_position_control2_DW.DiscreteTransferFcn1_states) /
    test_position_control2_P.DiscreteTransferFcn1_DenCoef[0];

  // Sum: '<S3>/Sum3' incorporates:
  //   DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
  //   DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn1'
  //   Gain: '<S3>/Gain1'

  test_position_control2_B.Sum3 = (test_position_control2_P.Gain1_Gain *
    test_position_control2_B.Product2 +
    test_position_control2_DW.DiscreteTimeIntegrator_DSTATE) +
    (test_position_control2_P.DiscreteTransferFcn1_NumCoef[0] *
     DiscreteTransferFcn1_tmp +
     test_position_control2_P.DiscreteTransferFcn1_NumCoef[1] *
     test_position_control2_DW.DiscreteTransferFcn1_states);

  // Saturate: '<Root>/Saturation'
  if (test_position_control2_B.Sum3 >
      test_position_control2_P.Saturation_UpperSat) {
    // Saturate: '<Root>/Saturation'
    test_position_control2_B.Saturation =
      test_position_control2_P.Saturation_UpperSat;
  } else if (test_position_control2_B.Sum3 <
             test_position_control2_P.Saturation_LowerSat) {
    // Saturate: '<Root>/Saturation'
    test_position_control2_B.Saturation =
      test_position_control2_P.Saturation_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation'
    test_position_control2_B.Saturation = test_position_control2_B.Sum3;
  }

  // End of Saturate: '<Root>/Saturation'

  // Sum: '<S1>/Sum' incorporates:
  //   Constant: '<S1>/Trim'
  //   Gain: '<S1>/Gain'
  //   Gain: '<S1>/Gain1'

  test_position_control2_B.Sum = test_position_control2_P.Gain_Gain_o *
    test_position_control2_B.Saturation * test_position_control2_P.Gain1_Gain_c
    + test_position_control2_P.Trim_Value;

  // SignalConversion generated from: '<S2>/Bus Selector3'
  test_position_control2_B.X = test_position_control2_B.In1.Pose.Position.X;

  // Sum: '<S3>/Sum1' incorporates:
  //   Constant: '<S3>/Y_Ref'

  test_position_control2_B.Product1 = test_position_control2_P.Y_Ref_Value -
    test_position_control2_B.X;

  // DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn' incorporates:
  //   Gain: '<S3>/Gain5'
  //   Gain: '<S3>/Gain8'

  DiscreteTransferFcn_tmp = (test_position_control2_P.Gain8_Gain *
    test_position_control2_B.X * test_position_control2_P.Gain5_Gain -
    test_position_control2_P.DiscreteTransferFcn_DenCoef[1] *
    test_position_control2_DW.DiscreteTransferFcn_states) /
    test_position_control2_P.DiscreteTransferFcn_DenCoef[0];

  // Gain: '<S3>/Gain6' incorporates:
  //   DiscreteIntegrator: '<S3>/Discrete-Time Integrator1'
  //   DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn'
  //   Gain: '<S3>/Gain4'
  //   Sum: '<S3>/Sum2'

  test_position_control2_B.Gain6 = ((test_position_control2_P.Gain4_Gain *
    test_position_control2_B.Product1 +
    test_position_control2_DW.DiscreteTimeIntegrator1_DSTATE) +
    (test_position_control2_P.DiscreteTransferFcn_NumCoef[0] *
     DiscreteTransferFcn_tmp +
     test_position_control2_P.DiscreteTransferFcn_NumCoef[1] *
     test_position_control2_DW.DiscreteTransferFcn_states)) *
    test_position_control2_P.Gain6_Gain;

  // Saturate: '<Root>/Saturation1'
  if (test_position_control2_B.Gain6 >
      test_position_control2_P.Saturation1_UpperSat) {
    // Saturate: '<Root>/Saturation1'
    test_position_control2_B.Saturation1 =
      test_position_control2_P.Saturation1_UpperSat;
  } else if (test_position_control2_B.Gain6 <
             test_position_control2_P.Saturation1_LowerSat) {
    // Saturate: '<Root>/Saturation1'
    test_position_control2_B.Saturation1 =
      test_position_control2_P.Saturation1_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation1'
    test_position_control2_B.Saturation1 = test_position_control2_B.Gain6;
  }

  // End of Saturate: '<Root>/Saturation1'

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Trim'
  //   Gain: '<S1>/Gain2'
  //   Gain: '<S1>/Gain3'

  test_position_control2_B.Sum1 = test_position_control2_P.Gain2_Gain_m *
    test_position_control2_B.Saturation1 * test_position_control2_P.Gain3_Gain +
    test_position_control2_P.Trim_Value;

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.Gain3_o = floor(test_position_control2_B.Sum);
  if (rtIsNaN(test_position_control2_B.Gain3_o) || rtIsInf
      (test_position_control2_B.Gain3_o)) {
    test_position_control2_B.Gain3_o = 0.0;
  } else {
    test_position_control2_B.Gain3_o = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[0] = static_cast<uint16_T>
    (test_position_control2_B.Gain3_o < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain3_o)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain3_o)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.Gain3_o = floor(test_position_control2_B.Sum1);
  if (rtIsNaN(test_position_control2_B.Gain3_o) || rtIsInf
      (test_position_control2_B.Gain3_o)) {
    test_position_control2_B.Gain3_o = 0.0;
  } else {
    test_position_control2_B.Gain3_o = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[1] = static_cast<uint16_T>
    (test_position_control2_B.Gain3_o < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain3_o)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain3_o)));

  // DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
  //   Constant: '<S1>/Thrust for hover'
  //   Sum: '<S1>/Sum4'

  test_position_control2_B.Gain3_o = floor
    (test_position_control2_P.MOT_THST_HOVER_MCS);
  if (rtIsNaN(test_position_control2_B.Gain3_o) || rtIsInf
      (test_position_control2_B.Gain3_o)) {
    test_position_control2_B.Gain3_o = 0.0;
  } else {
    test_position_control2_B.Gain3_o = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[2] = static_cast<uint16_T>
    (test_position_control2_B.Gain3_o < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain3_o)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain3_o)));

  // DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Zero2'

  test_position_control2_B.Gain3_o = floor(test_position_control2_P.Zero2_Value);
  if (rtIsNaN(test_position_control2_B.Gain3_o) || rtIsInf
      (test_position_control2_B.Gain3_o)) {
    test_position_control2_B.Gain3_o = 0.0;
  } else {
    test_position_control2_B.Gain3_o = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[3] = static_cast<uint16_T>
    (test_position_control2_B.Gain3_o < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain3_o)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain3_o)));

  // DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
  //   Constant: '<S4>/Zero'

  test_position_control2_B.Gain3_o = floor(test_position_control2_P.Zero_Value);
  b_varargout_1 = rtIsNaN(test_position_control2_B.Gain3_o);
  tmp = rtIsInf(test_position_control2_B.Gain3_o);
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[4] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Flight Mode'

  test_position_control2_B.Gain_p = floor(test_position_control2_P.STABILIZE);
  if (rtIsNaN(test_position_control2_B.Gain_p) || rtIsInf
      (test_position_control2_B.Gain_p)) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain_p,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[5] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[6] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[7] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[8] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[9] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[10] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[11] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[12] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
  }

  // DataTypeConversion: '<S4>/Data Type Conversion'
  test_position_control2_B.DataTypeConversion[13] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));

  // DataTypeConversion: '<S4>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control2_B.Gain_p = 0.0;
    test_position_control2_B.Gain3_o = 0.0;
  } else {
    test_position_control2_B.Gain_p = fmod(test_position_control2_B.Gain3_o,
      65536.0);
    test_position_control2_B.Gain3_o = test_position_control2_B.Gain_p;
  }

  // DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
  //   Constant: '<S4>/Zero3'

  test_position_control2_B.DataTypeConversion[14] = static_cast<uint16_T>
    (test_position_control2_B.Gain_p < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain_p)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain_p)));
  test_position_control2_B.DataTypeConversion[15] = static_cast<uint16_T>
    (test_position_control2_B.Gain3_o < 0.0 ? static_cast<int32_T>(static_cast<
      uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control2_B.Gain3_o)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control2_B.Gain3_o)));
  for (int32_T i = 0; i < 112; i++) {
    test_position_control2_B.Gain3_o = floor
      (test_position_control2_P.Zero3_Value[i]);
    if (rtIsNaN(test_position_control2_B.Gain3_o) || rtIsInf
        (test_position_control2_B.Gain3_o)) {
      test_position_control2_B.Gain3_o = 0.0;
    } else {
      test_position_control2_B.Gain3_o = fmod(test_position_control2_B.Gain3_o,
        65536.0);
    }

    test_position_control2_B.DataTypeConversion[i + 16] = static_cast<uint16_T>
      (test_position_control2_B.Gain3_o < 0.0 ? static_cast<int32_T>(
        static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
          (-test_position_control2_B.Gain3_o)))) : static_cast<int32_T>(
        static_cast<uint16_T>(test_position_control2_B.Gain3_o)));
  }

  // BusAssignment: '<S4>/Bus Assignment4' incorporates:
  //   Constant: '<S17>/Constant'

  test_position_control2_B.BusAssignment4 =
    test_position_control2_P.Constant_Value;
  memcpy(&test_position_control2_B.BusAssignment4.Data[0],
         &test_position_control2_B.DataTypeConversion[0], sizeof(uint16_T) << 7U);

  // DataTypeConversion: '<S4>/Data Type Conversion1' incorporates:
  //   Constant: '<S4>/Constant'

  test_position_control2_B.Gain3_o = floor
    (test_position_control2_P.Constant_Value_n);
  if (rtIsNaN(test_position_control2_B.Gain3_o) || rtIsInf
      (test_position_control2_B.Gain3_o)) {
    test_position_control2_B.Gain3_o = 0.0;
  } else {
    test_position_control2_B.Gain3_o = fmod(test_position_control2_B.Gain3_o,
      4.294967296E+9);
  }

  // BusAssignment: '<S4>/Bus Assignment4' incorporates:
  //   DataTypeConversion: '<S4>/Data Type Conversion1'

  test_position_control2_B.BusAssignment4.Data_SL_Info.CurrentLength =
    test_position_control2_B.Gain3_o < 0.0 ? static_cast<uint32_T>(-static_cast<
    int32_T>(static_cast<uint32_T>(-test_position_control2_B.Gain3_o))) :
    static_cast<uint32_T>(test_position_control2_B.Gain3_o);

  // Outputs for Atomic SubSystem: '<S4>/Publish'
  // MATLABSystem: '<S18>/SinkBlock'
  Pub_test_position_control2_24.publish(&test_position_control2_B.BusAssignment4);

  // End of Outputs for SubSystem: '<S4>/Publish'
  // Gain: '<S3>/Gain3'
  test_position_control2_B.Gain3_o = test_position_control2_P.Gain3_Gain_f *
    test_position_control2_B.Product1;

  // SignalConversion generated from: '<S2>/Bus Selector3'
  test_position_control2_B.Z = test_position_control2_B.In1.Pose.Position.Z;

  // Gain: '<S3>/Gain'
  test_position_control2_B.Gain_p = test_position_control2_P.Gain_Gain_c *
    test_position_control2_B.Product2;

  // Sqrt: '<S14>/sqrt' incorporates:
  //   Product: '<S15>/Product'
  //   Product: '<S15>/Product1'
  //   Product: '<S15>/Product2'
  //   Product: '<S15>/Product3'
  //   Sum: '<S15>/Sum'

  test_position_control2_B.Product3 = sqrt
    (((test_position_control2_B.In1.Pose.Orientation.W *
       test_position_control2_B.In1.Pose.Orientation.W +
       test_position_control2_B.In1.Pose.Orientation.X *
       test_position_control2_B.In1.Pose.Orientation.X) +
      test_position_control2_B.In1.Pose.Orientation.Y *
      test_position_control2_B.In1.Pose.Orientation.Y) +
     test_position_control2_B.In1.Pose.Orientation.Z *
     test_position_control2_B.In1.Pose.Orientation.Z);

  // Product: '<S9>/Product'
  test_position_control2_B.fcn5 =
    test_position_control2_B.In1.Pose.Orientation.W /
    test_position_control2_B.Product3;

  // Product: '<S9>/Product1'
  test_position_control2_B.Product1 =
    test_position_control2_B.In1.Pose.Orientation.X /
    test_position_control2_B.Product3;

  // Product: '<S9>/Product2'
  test_position_control2_B.Product2 =
    test_position_control2_B.In1.Pose.Orientation.Y /
    test_position_control2_B.Product3;

  // Product: '<S9>/Product3'
  test_position_control2_B.Product3 =
    test_position_control2_B.In1.Pose.Orientation.Z /
    test_position_control2_B.Product3;

  // Fcn: '<S7>/fcn2' incorporates:
  //   Fcn: '<S7>/fcn5'

  VectorConcatenate_tmp = test_position_control2_B.fcn5 *
    test_position_control2_B.fcn5;
  VectorConcatenate_tmp_0 = test_position_control2_B.Product1 *
    test_position_control2_B.Product1;
  VectorConcatenate_tmp_1 = test_position_control2_B.Product2 *
    test_position_control2_B.Product2;
  VectorConcatenate_tmp_2 = test_position_control2_B.Product3 *
    test_position_control2_B.Product3;

  // Trigonometry: '<S8>/Trigonometric Function1' incorporates:
  //   Concatenate: '<S8>/Vector Concatenate'
  //   Fcn: '<S7>/fcn1'
  //   Fcn: '<S7>/fcn2'

  test_position_control2_B.VectorConcatenate[0] = rt_atan2d_snf
    ((test_position_control2_B.Product2 * test_position_control2_B.Product3 -
      test_position_control2_B.fcn5 * test_position_control2_B.Product1) * -2.0,
     ((VectorConcatenate_tmp - VectorConcatenate_tmp_0) -
      VectorConcatenate_tmp_1) + VectorConcatenate_tmp_2);

  // Fcn: '<S7>/fcn3'
  test_position_control2_B.fcn3 = (test_position_control2_B.Product1 *
    test_position_control2_B.Product3 + test_position_control2_B.fcn5 *
    test_position_control2_B.Product2) * 2.0;

  // If: '<S10>/If' incorporates:
  //   Constant: '<S11>/Constant'
  //   Constant: '<S12>/Constant'

  if (test_position_control2_B.fcn3 > 1.0) {
    // Outputs for IfAction SubSystem: '<S10>/If Action Subsystem' incorporates:
    //   ActionPort: '<S11>/Action Port'

    test_position_control2_B.fcn3 = test_position_control2_P.Constant_Value_b;

    // End of Outputs for SubSystem: '<S10>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S10>/If Action Subsystem' incorporates:
    //   ActionPort: '<S11>/Action Port'

    // Update for If: '<S10>/If' incorporates:
    //   Constant: '<S11>/Constant'

    srUpdateBC(test_position_control2_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S10>/If Action Subsystem'
  } else if (test_position_control2_B.fcn3 < -1.0) {
    // Outputs for IfAction SubSystem: '<S10>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S12>/Action Port'

    test_position_control2_B.fcn3 = test_position_control2_P.Constant_Value_m;

    // End of Outputs for SubSystem: '<S10>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S10>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S12>/Action Port'

    // Update for If: '<S10>/If' incorporates:
    //   Constant: '<S12>/Constant'

    srUpdateBC(test_position_control2_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S10>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S10>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // Update for If: '<S10>/If'
    srUpdateBC(test_position_control2_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S10>/If Action Subsystem2'
  }

  // End of If: '<S10>/If'

  // Trigonometry: '<S8>/Trigonometric Function3' incorporates:
  //   Concatenate: '<S8>/Vector Concatenate'
  //   Fcn: '<S7>/fcn4'
  //   Fcn: '<S7>/fcn5'

  test_position_control2_B.VectorConcatenate[2] = rt_atan2d_snf
    ((test_position_control2_B.Product1 * test_position_control2_B.Product2 -
      test_position_control2_B.fcn5 * test_position_control2_B.Product3) * -2.0,
     ((VectorConcatenate_tmp + VectorConcatenate_tmp_0) -
      VectorConcatenate_tmp_1) - VectorConcatenate_tmp_2);

  // Trigonometry: '<S8>/trigFcn' incorporates:
  //   Concatenate: '<S8>/Vector Concatenate'

  if (test_position_control2_B.fcn3 > 1.0) {
    test_position_control2_B.fcn3 = 1.0;
  } else if (test_position_control2_B.fcn3 < -1.0) {
    test_position_control2_B.fcn3 = -1.0;
  }

  test_position_control2_B.VectorConcatenate[1] = asin
    (test_position_control2_B.fcn3);

  // End of Trigonometry: '<S8>/trigFcn'
  // S-Function (saeroclockpacer): '<Root>/Simulation Pace'
  //
  //  The Clock Pacer generates no code, it is only active in
  //  interpreted simulation.


  // Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
  test_position_control2_DW.DiscreteTimeIntegrator_DSTATE +=
    test_position_control2_P.DiscreteTimeIntegrator_gainval *
    test_position_control2_B.Gain_p;

  // Update for DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn1'
  test_position_control2_DW.DiscreteTransferFcn1_states =
    DiscreteTransferFcn1_tmp;

  // Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator1'
  test_position_control2_DW.DiscreteTimeIntegrator1_DSTATE +=
    test_position_control2_P.DiscreteTimeIntegrator1_gainval *
    test_position_control2_B.Gain3_o;

  // Update for DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn'
  test_position_control2_DW.DiscreteTransferFcn_states = DiscreteTransferFcn_tmp;

  // External mode
  rtExtModeUploadCheckTrigger(1);

  {                                    // Sample time: [0.02s, 0.0s]
    rtExtModeUpload(0, (real_T)test_position_control2_M->Timing.taskTime0);
  }

  // signal main to stop simulation
  {                                    // Sample time: [0.02s, 0.0s]
    if ((rtmGetTFinal(test_position_control2_M)!=-1) &&
        !((rtmGetTFinal(test_position_control2_M)-
           test_position_control2_M->Timing.taskTime0) >
          test_position_control2_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(test_position_control2_M, "Simulation finished");
    }

    if (rtmGetStopRequested(test_position_control2_M)) {
      rtmSetErrorStatus(test_position_control2_M, "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  test_position_control2_M->Timing.taskTime0 =
    ((time_T)(++test_position_control2_M->Timing.clockTick0)) *
    test_position_control2_M->Timing.stepSize0;
}

// Model initialize function
void test_position_control2_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(test_position_control2_M, -1);
  test_position_control2_M->Timing.stepSize0 = 0.02;

  // External mode info
  test_position_control2_M->Sizes.checksums[0] = (880591119U);
  test_position_control2_M->Sizes.checksums[1] = (3124811345U);
  test_position_control2_M->Sizes.checksums[2] = (3573945894U);
  test_position_control2_M->Sizes.checksums[3] = (3128659438U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[10];
    test_position_control2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &test_position_control2_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[2] = (sysRanDType *)
      &test_position_control2_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[3] = (sysRanDType *)
      &test_position_control2_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[4] = (sysRanDType *)
      &test_position_control2_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test_position_control2_M->extModeInfo,
      &test_position_control2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test_position_control2_M->extModeInfo,
                        test_position_control2_M->Sizes.checksums);
    rteiSetTPtr(test_position_control2_M->extModeInfo, rtmGetTPtr
                (test_position_control2_M));
  }

  // data type transition information
  {
    static DataTypeTransInfo dtInfo;
    test_position_control2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 31;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    // Block I/O transition table
    dtInfo.BTransTable = &rtBTransTable;

    // Parameters transition table
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    char_T b_zeroDelimTopic[28];
    char_T b_zeroDelimTopic_0[14];
    static const char_T tmp[27] = { '/', 'v', 'r', 'p', 'n', '_', 'c', 'l', 'i',
      'e', 'n', 't', '_', 'n', 'o', 'd', 'e', '/', 'Q', 'u', 'a', 'd', '/', 'p',
      'o', 's', 'e' };

    static const char_T tmp_0[13] = { 'q', 'u', 'a', 'd', '_', 'c', 'o', 'm',
      'm', 'a', 'n', 'd', 's' };

    // InitializeConditions for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' 
    test_position_control2_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control2_P.DiscreteTimeIntegrator_IC;

    // InitializeConditions for DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn1' 
    test_position_control2_DW.DiscreteTransferFcn1_states =
      test_position_control2_P.DiscreteTransferFcn1_InitialSta;

    // InitializeConditions for DiscreteIntegrator: '<S3>/Discrete-Time Integrator1' 
    test_position_control2_DW.DiscreteTimeIntegrator1_DSTATE =
      test_position_control2_P.DiscreteTimeIntegrator1_IC;

    // InitializeConditions for DiscreteTransferFcn: '<S3>/Discrete Transfer Fcn' 
    test_position_control2_DW.DiscreteTransferFcn_states =
      test_position_control2_P.DiscreteTransferFcn_InitialStat;

    // SystemInitialize for Atomic SubSystem: '<S2>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S16>/In1' incorporates:
    //   Outport: '<S16>/Out1'

    test_position_control2_B.In1 = test_position_control2_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem'

    // Start for MATLABSystem: '<S6>/SourceBlock'
    test_position_control2_DW.obj.matlabCodegenIsDeleted = false;
    test_position_control2_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 27; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[27] = '\x00';
    Sub_test_position_control2_15.createSubscriber(&b_zeroDelimTopic[0], 1);
    test_position_control2_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S6>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S2>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S4>/Publish'
    // Start for MATLABSystem: '<S18>/SinkBlock'
    test_position_control2_DW.obj_m.matlabCodegenIsDeleted = false;
    test_position_control2_DW.obj_m.isInitialized = 1;
    for (int32_T i = 0; i < 13; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[13] = '\x00';
    Pub_test_position_control2_24.createPublisher(&b_zeroDelimTopic_0[0], 1);
    test_position_control2_DW.obj_m.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S18>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<S4>/Publish'
  }
}

// Model terminate function
void test_position_control2_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S2>/Subscribe'
  // Terminate for MATLABSystem: '<S6>/SourceBlock'
  if (!test_position_control2_DW.obj.matlabCodegenIsDeleted) {
    test_position_control2_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S6>/SourceBlock'
  // End of Terminate for SubSystem: '<S2>/Subscribe'

  // Terminate for Atomic SubSystem: '<S4>/Publish'
  // Terminate for MATLABSystem: '<S18>/SinkBlock'
  if (!test_position_control2_DW.obj_m.matlabCodegenIsDeleted) {
    test_position_control2_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S18>/SinkBlock'
  // End of Terminate for SubSystem: '<S4>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
