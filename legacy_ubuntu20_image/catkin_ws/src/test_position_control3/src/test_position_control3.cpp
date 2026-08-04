//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: test_position_control3.cpp
//
// Code generated for Simulink model 'test_position_control3'.
//
// Model version                  : 1.22
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Tue Dec 30 19:17:00 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "test_position_control3.h"
#include "rtwtypes.h"
#include <math.h>
#include "test_position_control3_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>
#include "test_position_control3_types.h"
#include "rt_defines.h"
#include "test_position_control3_dt.h"

// Block signals (default storage)
B_test_position_control3_T test_position_control3_B;

// Block states (default storage)
DW_test_position_control3_T test_position_control3_DW;

// Real-time model
RT_MODEL_test_position_contro_T test_position_control3_M_ =
  RT_MODEL_test_position_contro_T();
RT_MODEL_test_position_contro_T *const test_position_control3_M =
  &test_position_control3_M_;
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
void test_position_control3_step(void)
{
  SL_Bus_test_position_control3_std_msgs_Bool b_varargout_2;
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_0;
  real_T VectorConcatenate_tmp_1;
  real_T VectorConcatenate_tmp_2;
  real_T rtb_Sum2;
  real_T rtb_fcn3;
  boolean_T b_varargout_1;
  boolean_T tmp;

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control3_DW.EnabledSubsystem_SubsysRanBC_k);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control3_DW.IfActionSubsystem_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control3_DW.IfActionSubsystem1_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control3_DW.IfActionSubsystem2_SubsysRanBC);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control3_DW.EnabledSubsystem_SubsysRanBC_c);

  // Reset subsysRan breadcrumbs
  srClearBC(test_position_control3_DW.EnabledSubsystem_SubsysRanBC);

  // Outputs for Atomic SubSystem: '<S3>/Subscribe'
  // MATLABSystem: '<S10>/SourceBlock'
  b_varargout_1 = Sub_test_position_control3_194.getLatestMessage
    (&test_position_control3_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S20>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S20>/In1'
    test_position_control3_B.In1 = test_position_control3_B.b_varargout_2;
    srUpdateBC(test_position_control3_DW.EnabledSubsystem_SubsysRanBC_c);
  }

  // End of MATLABSystem: '<S10>/SourceBlock'
  // End of Outputs for SubSystem: '<S10>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S3>/Subscribe'

  // Sqrt: '<S18>/sqrt' incorporates:
  //   Product: '<S19>/Product'
  //   Product: '<S19>/Product1'
  //   Product: '<S19>/Product2'
  //   Product: '<S19>/Product3'
  //   Sum: '<S19>/Sum'

  test_position_control3_B.Product3 = sqrt
    (((test_position_control3_B.In1.Pose.Orientation.W *
       test_position_control3_B.In1.Pose.Orientation.W +
       test_position_control3_B.In1.Pose.Orientation.X *
       test_position_control3_B.In1.Pose.Orientation.X) +
      test_position_control3_B.In1.Pose.Orientation.Y *
      test_position_control3_B.In1.Pose.Orientation.Y) +
     test_position_control3_B.In1.Pose.Orientation.Z *
     test_position_control3_B.In1.Pose.Orientation.Z);

  // Product: '<S13>/Product'
  rtb_Sum2 = test_position_control3_B.In1.Pose.Orientation.W /
    test_position_control3_B.Product3;

  // Product: '<S13>/Product1'
  test_position_control3_B.Sum4 =
    test_position_control3_B.In1.Pose.Orientation.X /
    test_position_control3_B.Product3;

  // Product: '<S13>/Product2'
  test_position_control3_B.Product2 =
    test_position_control3_B.In1.Pose.Orientation.Y /
    test_position_control3_B.Product3;

  // Product: '<S13>/Product3'
  test_position_control3_B.Product3 =
    test_position_control3_B.In1.Pose.Orientation.Z /
    test_position_control3_B.Product3;

  // Fcn: '<S11>/fcn2' incorporates:
  //   Fcn: '<S11>/fcn5'

  VectorConcatenate_tmp = rtb_Sum2 * rtb_Sum2;
  VectorConcatenate_tmp_0 = test_position_control3_B.Sum4 *
    test_position_control3_B.Sum4;
  VectorConcatenate_tmp_1 = test_position_control3_B.Product2 *
    test_position_control3_B.Product2;
  VectorConcatenate_tmp_2 = test_position_control3_B.Product3 *
    test_position_control3_B.Product3;

  // Trigonometry: '<S12>/Trigonometric Function1' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn1'
  //   Fcn: '<S11>/fcn2'

  test_position_control3_B.VectorConcatenate[0] = rt_atan2d_snf
    ((test_position_control3_B.Product2 * test_position_control3_B.Product3 -
      rtb_Sum2 * test_position_control3_B.Sum4) * -2.0, ((VectorConcatenate_tmp
       - VectorConcatenate_tmp_0) - VectorConcatenate_tmp_1) +
     VectorConcatenate_tmp_2);

  // Fcn: '<S11>/fcn3'
  rtb_fcn3 = (test_position_control3_B.Sum4 * test_position_control3_B.Product3
              + rtb_Sum2 * test_position_control3_B.Product2) * 2.0;

  // If: '<S14>/If' incorporates:
  //   Constant: '<S15>/Constant'
  //   Constant: '<S16>/Constant'

  if (rtb_fcn3 > 1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    rtb_fcn3 = test_position_control3_P.Constant_Value_p;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S15>/Constant'

    srUpdateBC(test_position_control3_DW.IfActionSubsystem_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem'
  } else if (rtb_fcn3 < -1.0) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    rtb_fcn3 = test_position_control3_P.Constant_Value_m;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem1'

    // Update for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    // Update for If: '<S14>/If' incorporates:
    //   Constant: '<S16>/Constant'

    srUpdateBC(test_position_control3_DW.IfActionSubsystem1_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem1'
  } else {
    // Update for IfAction SubSystem: '<S14>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S17>/Action Port'

    // Update for If: '<S14>/If'
    srUpdateBC(test_position_control3_DW.IfActionSubsystem2_SubsysRanBC);

    // End of Update for SubSystem: '<S14>/If Action Subsystem2'
  }

  // End of If: '<S14>/If'

  // Trigonometry: '<S12>/trigFcn' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'

  if (rtb_fcn3 > 1.0) {
    rtb_fcn3 = 1.0;
  } else if (rtb_fcn3 < -1.0) {
    rtb_fcn3 = -1.0;
  }

  test_position_control3_B.VectorConcatenate[1] = asin(rtb_fcn3);

  // End of Trigonometry: '<S12>/trigFcn'

  // Trigonometry: '<S12>/Trigonometric Function3' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate'
  //   Fcn: '<S11>/fcn4'
  //   Fcn: '<S11>/fcn5'

  test_position_control3_B.VectorConcatenate[2] = rt_atan2d_snf
    ((test_position_control3_B.Sum4 * test_position_control3_B.Product2 -
      rtb_Sum2 * test_position_control3_B.Product3) * -2.0,
     ((VectorConcatenate_tmp + VectorConcatenate_tmp_0) -
      VectorConcatenate_tmp_1) - VectorConcatenate_tmp_2);

  // Outputs for Atomic SubSystem: '<S2>/Subscribe'
  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = Sub_test_position_control3_177.getLatestMessage(&b_varargout_2);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    test_position_control3_B.In1_l = b_varargout_2;
    srUpdateBC(test_position_control3_DW.EnabledSubsystem_SubsysRanBC_k);
  }

  // End of MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S2>/Subscribe'

  // DiscreteIntegrator: '<S24>/Discrete-Time Integrator'
  if (test_position_control3_B.In1_l.Data &&
      (test_position_control3_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control3_P.DiscreteTimeIntegrator_IC;
  }

  if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE >=
      test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control3_P.I_max_XY;
  } else if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE <=
             -test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE =
      -test_position_control3_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S24>/Discrete-Time Integrator'
  test_position_control3_B.DiscreteTimeIntegrator =
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE;

  // Gain: '<S3>/Gain'
  test_position_control3_B.x = test_position_control3_P.Gain_Gain *
    test_position_control3_B.In1.Pose.Position.Y;

  // Sum: '<S5>/Sum' incorporates:
  //   Constant: '<S5>/X_ref'

  rtb_fcn3 = test_position_control3_P.X_ref_Value - test_position_control3_B.x;

  // Gain: '<S24>/Gain'
  test_position_control3_B.Gain = test_position_control3_P.Gain_Gain_n *
    rtb_fcn3;

  // Outputs for Atomic SubSystem: '<S4>/Subscribe'
  // MATLABSystem: '<S21>/SourceBlock'
  b_varargout_1 = Sub_test_position_control3_205.getLatestMessage
    (&test_position_control3_B.b_varargout_2_m);

  // Outputs for Enabled SubSystem: '<S21>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S22>/Enable'

  if (b_varargout_1) {
    // SignalConversion generated from: '<S22>/In1'
    test_position_control3_B.In1_e = test_position_control3_B.b_varargout_2_m;
    srUpdateBC(test_position_control3_DW.EnabledSubsystem_SubsysRanBC);
  }

  // End of MATLABSystem: '<S21>/SourceBlock'
  // End of Outputs for SubSystem: '<S21>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S4>/Subscribe'

  // Gain: '<S4>/Gain' incorporates:
  //   SignalConversion generated from: '<S4>/Bus Selector'

  test_position_control3_B.x_m = test_position_control3_P.Gain_Gain_c *
    test_position_control3_B.In1_e.Twist.Linear.Y;

  // Gain: '<S24>/Gain2'
  test_position_control3_B.Gain2 = test_position_control3_P.Gain2_Gain *
    test_position_control3_B.x_m;

  // Sum: '<S24>/Sum3'
  rtb_Sum2 = (test_position_control3_B.DiscreteTimeIntegrator +
              test_position_control3_B.Gain) - test_position_control3_B.Gain2;

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  if (test_position_control3_B.In1_l.Data &&
      (test_position_control3_DW.DiscreteTimeIntegrator_PrevRe_p <= 0)) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a =
      test_position_control3_P.DiscreteTimeIntegrator_IC_l;
  }

  if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a >=
      test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a =
      test_position_control3_P.I_max_XY;
  } else if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a <=
             -test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a =
      -test_position_control3_P.I_max_XY;
  }

  // DiscreteIntegrator: '<S25>/Discrete-Time Integrator'
  test_position_control3_B.DiscreteTimeIntegrator_p =
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  test_position_control3_B.X = test_position_control3_B.In1.Pose.Position.X;

  // Sum: '<S5>/Sum1' incorporates:
  //   Constant: '<S5>/Y_ref'

  test_position_control3_B.Product3 = test_position_control3_P.Y_ref_Value -
    test_position_control3_B.X;

  // Gain: '<S25>/Gain'
  test_position_control3_B.Gain_d = test_position_control3_P.Gain_Gain_b *
    test_position_control3_B.Product3;

  // SignalConversion generated from: '<S4>/Bus Selector'
  test_position_control3_B.X_h = test_position_control3_B.In1_e.Twist.Linear.X;

  // Gain: '<S25>/Gain2'
  test_position_control3_B.Gain2_m = test_position_control3_P.Gain2_Gain_o *
    test_position_control3_B.X_h;

  // Sum: '<S25>/Sum3'
  test_position_control3_B.Sum4 =
    (test_position_control3_B.DiscreteTimeIntegrator_p +
     test_position_control3_B.Gain_d) - test_position_control3_B.Gain2_m;

  // MATLAB Function: '<S5>/MATLAB Function'
  test_position_control3_B.Product2 = sin
    (test_position_control3_B.VectorConcatenate[2]);
  VectorConcatenate_tmp = cos(test_position_control3_B.VectorConcatenate[2]);
  test_position_control3_B.theta_B = rtb_Sum2 * VectorConcatenate_tmp +
    test_position_control3_B.Sum4 * test_position_control3_B.Product2;
  test_position_control3_B.phi_B = -rtb_Sum2 * test_position_control3_B.Product2
    + test_position_control3_B.Sum4 * VectorConcatenate_tmp;

  // Saturate: '<Root>/Saturation'
  if (test_position_control3_B.theta_B >
      test_position_control3_P.Saturation_UpperSat) {
    // Saturate: '<Root>/Saturation'
    test_position_control3_B.Saturation =
      test_position_control3_P.Saturation_UpperSat;
  } else if (test_position_control3_B.theta_B <
             test_position_control3_P.Saturation_LowerSat) {
    // Saturate: '<Root>/Saturation'
    test_position_control3_B.Saturation =
      test_position_control3_P.Saturation_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation'
    test_position_control3_B.Saturation = test_position_control3_B.theta_B;
  }

  // End of Saturate: '<Root>/Saturation'

  // Sum: '<S1>/Sum' incorporates:
  //   Constant: '<S1>/Trim'
  //   Gain: '<S1>/Gain'
  //   Gain: '<S1>/Gain1'

  test_position_control3_B.Sum = test_position_control3_P.Gain_Gain_nr *
    test_position_control3_B.Saturation * test_position_control3_P.Gain1_Gain +
    test_position_control3_P.Trim_Value;

  // Saturate: '<Root>/Saturation1'
  if (test_position_control3_B.phi_B >
      test_position_control3_P.Saturation1_UpperSat) {
    // Saturate: '<Root>/Saturation1'
    test_position_control3_B.Saturation1 =
      test_position_control3_P.Saturation1_UpperSat;
  } else if (test_position_control3_B.phi_B <
             test_position_control3_P.Saturation1_LowerSat) {
    // Saturate: '<Root>/Saturation1'
    test_position_control3_B.Saturation1 =
      test_position_control3_P.Saturation1_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation1'
    test_position_control3_B.Saturation1 = test_position_control3_B.phi_B;
  }

  // End of Saturate: '<Root>/Saturation1'

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Trim1'
  //   Gain: '<S1>/Gain2'
  //   Gain: '<S1>/Gain3'

  test_position_control3_B.Sum1 = test_position_control3_P.Gain2_Gain_k *
    test_position_control3_B.Saturation1 * test_position_control3_P.Gain3_Gain +
    test_position_control3_P.Trim1_Value;

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  if (test_position_control3_B.In1_l.Data &&
      (test_position_control3_DW.DiscreteTimeIntegrator_PrevRe_j <= 0)) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k =
      test_position_control3_P.DiscreteTimeIntegrator_IC_g;
  }

  if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k >=
      test_position_control3_P.I_max_Z) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k =
      test_position_control3_P.I_max_Z;
  } else if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k <=
             -test_position_control3_P.I_max_Z) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k =
      -test_position_control3_P.I_max_Z;
  }

  // DiscreteIntegrator: '<S26>/Discrete-Time Integrator'
  test_position_control3_B.DiscreteTimeIntegrator_j =
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k;

  // SignalConversion generated from: '<S3>/Bus Selector3'
  test_position_control3_B.Z = test_position_control3_B.In1.Pose.Position.Z;

  // Sum: '<S5>/Sum2' incorporates:
  //   Constant: '<S5>/Z_ref'

  rtb_Sum2 = test_position_control3_P.Z_ref_Value - test_position_control3_B.Z;

  // Gain: '<S26>/Gain'
  test_position_control3_B.Gain_a = test_position_control3_P.Gain_Gain_j *
    rtb_Sum2;

  // SignalConversion generated from: '<S4>/Bus Selector'
  test_position_control3_B.Z_n = test_position_control3_B.In1_e.Twist.Linear.Z;

  // Gain: '<S26>/Gain2'
  test_position_control3_B.Gain2_i = test_position_control3_P.Gain2_Gain_b *
    test_position_control3_B.Z_n;

  // Sum: '<S26>/Sum3'
  test_position_control3_B.Sum3 =
    (test_position_control3_B.DiscreteTimeIntegrator_j +
     test_position_control3_B.Gain_a) - test_position_control3_B.Gain2_i;

  // Saturate: '<Root>/Saturation2'
  if (test_position_control3_B.Sum3 >
      test_position_control3_P.Saturation2_UpperSat) {
    // Saturate: '<Root>/Saturation2'
    test_position_control3_B.Saturation2 =
      test_position_control3_P.Saturation2_UpperSat;
  } else if (test_position_control3_B.Sum3 <
             test_position_control3_P.Saturation2_LowerSat) {
    // Saturate: '<Root>/Saturation2'
    test_position_control3_B.Saturation2 =
      test_position_control3_P.Saturation2_LowerSat;
  } else {
    // Saturate: '<Root>/Saturation2'
    test_position_control3_B.Saturation2 = test_position_control3_B.Sum3;
  }

  // End of Saturate: '<Root>/Saturation2'

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.Sum4 = floor(test_position_control3_B.Sum);
  if (rtIsNaN(test_position_control3_B.Sum4) || rtIsInf
      (test_position_control3_B.Sum4)) {
    test_position_control3_B.Sum4 = 0.0;
  } else {
    test_position_control3_B.Sum4 = fmod(test_position_control3_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[0] = static_cast<uint16_T>
    (test_position_control3_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control3_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.Sum4 = floor(test_position_control3_B.Sum1);
  if (rtIsNaN(test_position_control3_B.Sum4) || rtIsInf
      (test_position_control3_B.Sum4)) {
    test_position_control3_B.Sum4 = 0.0;
  } else {
    test_position_control3_B.Sum4 = fmod(test_position_control3_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[1] = static_cast<uint16_T>
    (test_position_control3_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control3_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S1>/Thrust for hover'
  //   Gain: '<S1>/From motor test stand'
  //   Sum: '<S1>/Sum4'

  test_position_control3_B.Sum4 = floor
    (test_position_control3_P.Frommotorteststand_Gain *
     test_position_control3_B.Saturation2 +
     test_position_control3_P.MOT_THST_HOVER_MCS);
  if (rtIsNaN(test_position_control3_B.Sum4) || rtIsInf
      (test_position_control3_B.Sum4)) {
    test_position_control3_B.Sum4 = 0.0;
  } else {
    test_position_control3_B.Sum4 = fmod(test_position_control3_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[2] = static_cast<uint16_T>
    (test_position_control3_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control3_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Zero2'

  test_position_control3_B.Sum4 = floor(test_position_control3_P.Zero2_Value);
  if (rtIsNaN(test_position_control3_B.Sum4) || rtIsInf
      (test_position_control3_B.Sum4)) {
    test_position_control3_B.Sum4 = 0.0;
  } else {
    test_position_control3_B.Sum4 = fmod(test_position_control3_B.Sum4, 65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[3] = static_cast<uint16_T>
    (test_position_control3_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control3_B.Sum4)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero'

  test_position_control3_B.Sum4 = floor(test_position_control3_P.Zero_Value);
  b_varargout_1 = rtIsNaN(test_position_control3_B.Sum4);
  tmp = rtIsInf(test_position_control3_B.Sum4);
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[4] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<
      uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<Root>/Flight Mode'

  test_position_control3_B.Product2 = floor(test_position_control3_P.STABILIZE);
  if (rtIsNaN(test_position_control3_B.Product2) || rtIsInf
      (test_position_control3_B.Product2)) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Product2,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[5] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>(static_cast<
      uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[6] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[7] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[8] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[9] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[10] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[11] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[12] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
  }

  // DataTypeConversion: '<S6>/Data Type Conversion'
  test_position_control3_B.DataTypeConversion[13] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));

  // DataTypeConversion: '<S6>/Data Type Conversion'
  if (b_varargout_1 || tmp) {
    test_position_control3_B.Product2 = 0.0;
    test_position_control3_B.Sum4 = 0.0;
  } else {
    test_position_control3_B.Product2 = fmod(test_position_control3_B.Sum4,
      65536.0);
    test_position_control3_B.Sum4 = test_position_control3_B.Product2;
  }

  // DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
  //   Constant: '<S6>/Zero3'

  test_position_control3_B.DataTypeConversion[14] = static_cast<uint16_T>
    (test_position_control3_B.Product2 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Product2)))) : static_cast<int32_T>(
      static_cast<uint16_T>(test_position_control3_B.Product2)));
  test_position_control3_B.DataTypeConversion[15] = static_cast<uint16_T>
    (test_position_control3_B.Sum4 < 0.0 ? static_cast<int32_T>
     (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
        (-test_position_control3_B.Sum4)))) : static_cast<int32_T>
     (static_cast<uint16_T>(test_position_control3_B.Sum4)));
  for (int32_T i = 0; i < 112; i++) {
    test_position_control3_B.Sum4 = floor(test_position_control3_P.Zero3_Value[i]);
    if (rtIsNaN(test_position_control3_B.Sum4) || rtIsInf
        (test_position_control3_B.Sum4)) {
      test_position_control3_B.Sum4 = 0.0;
    } else {
      test_position_control3_B.Sum4 = fmod(test_position_control3_B.Sum4,
        65536.0);
    }

    test_position_control3_B.DataTypeConversion[i + 16] = static_cast<uint16_T>
      (test_position_control3_B.Sum4 < 0.0 ? static_cast<int32_T>
       (static_cast<uint16_T>(-static_cast<int16_T>(static_cast<uint16_T>
          (-test_position_control3_B.Sum4)))) : static_cast<int32_T>(
        static_cast<uint16_T>(test_position_control3_B.Sum4)));
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   Constant: '<S27>/Constant'

  test_position_control3_B.BusAssignment4 =
    test_position_control3_P.Constant_Value;
  memcpy(&test_position_control3_B.BusAssignment4.Data[0],
         &test_position_control3_B.DataTypeConversion[0], sizeof(uint16_T) << 7U);

  // DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
  //   Constant: '<S6>/Constant'

  test_position_control3_B.Sum4 = floor
    (test_position_control3_P.Constant_Value_n);
  if (rtIsNaN(test_position_control3_B.Sum4) || rtIsInf
      (test_position_control3_B.Sum4)) {
    test_position_control3_B.Sum4 = 0.0;
  } else {
    test_position_control3_B.Sum4 = fmod(test_position_control3_B.Sum4,
      4.294967296E+9);
  }

  // BusAssignment: '<S6>/Bus Assignment4' incorporates:
  //   DataTypeConversion: '<S6>/Data Type Conversion1'

  test_position_control3_B.BusAssignment4.Data_SL_Info.CurrentLength =
    test_position_control3_B.Sum4 < 0.0 ? static_cast<uint32_T>
    (-static_cast<int32_T>(static_cast<uint32_T>(-test_position_control3_B.Sum4)))
    : static_cast<uint32_T>(test_position_control3_B.Sum4);

  // Outputs for Atomic SubSystem: '<S6>/Publish'
  // MATLABSystem: '<S28>/SinkBlock'
  Pub_test_position_control3_24.publish(&test_position_control3_B.BusAssignment4);

  // End of Outputs for SubSystem: '<S6>/Publish'
  // S-Function (saeroclockpacer): '<Root>/Simulation Pace'
  //
  //  The Clock Pacer generates no code, it is only active in
  //  interpreted simulation.


  // Update for DiscreteIntegrator: '<S24>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S24>/Gain1'

  test_position_control3_DW.DiscreteTimeIntegrator_DSTATE +=
    test_position_control3_P.Gain1_Gain_g * rtb_fcn3 *
    test_position_control3_P.DiscreteTimeIntegrator_gainval;
  if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE >=
      test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control3_P.I_max_XY;
  } else if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE <=
             -test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE =
      -test_position_control3_P.I_max_XY;
  }

  test_position_control3_DW.DiscreteTimeIntegrator_PrevRese = static_cast<int8_T>
    (test_position_control3_B.In1_l.Data);

  // Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S24>/Discrete-Time Integrator'
  //   Gain: '<S25>/Gain1'

  test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a +=
    test_position_control3_P.Gain1_Gain_e * test_position_control3_B.Product3 *
    test_position_control3_P.DiscreteTimeIntegrator_gainva_l;
  if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a >=
      test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a =
      test_position_control3_P.I_max_XY;
  } else if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a <=
             -test_position_control3_P.I_max_XY) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a =
      -test_position_control3_P.I_max_XY;
  }

  test_position_control3_DW.DiscreteTimeIntegrator_PrevRe_p = static_cast<int8_T>
    (test_position_control3_B.In1_l.Data);

  // End of Update for DiscreteIntegrator: '<S25>/Discrete-Time Integrator'

  // Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' incorporates:
  //   DiscreteIntegrator: '<S24>/Discrete-Time Integrator'
  //   Gain: '<S26>/Gain1'

  test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k +=
    test_position_control3_P.Gain1_Gain_f * rtb_Sum2 *
    test_position_control3_P.DiscreteTimeIntegrator_gainva_j;
  if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k >=
      test_position_control3_P.I_max_Z) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k =
      test_position_control3_P.I_max_Z;
  } else if (test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k <=
             -test_position_control3_P.I_max_Z) {
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k =
      -test_position_control3_P.I_max_Z;
  }

  test_position_control3_DW.DiscreteTimeIntegrator_PrevRe_j = static_cast<int8_T>
    (test_position_control3_B.In1_l.Data);

  // End of Update for DiscreteIntegrator: '<S26>/Discrete-Time Integrator'

  // External mode
  rtExtModeUploadCheckTrigger(1);

  {                                    // Sample time: [0.02s, 0.0s]
    rtExtModeUpload(0, (real_T)test_position_control3_M->Timing.taskTime0);
  }

  // signal main to stop simulation
  {                                    // Sample time: [0.02s, 0.0s]
    if ((rtmGetTFinal(test_position_control3_M)!=-1) &&
        !((rtmGetTFinal(test_position_control3_M)-
           test_position_control3_M->Timing.taskTime0) >
          test_position_control3_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(test_position_control3_M, "Simulation finished");
    }

    if (rtmGetStopRequested(test_position_control3_M)) {
      rtmSetErrorStatus(test_position_control3_M, "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  test_position_control3_M->Timing.taskTime0 =
    ((time_T)(++test_position_control3_M->Timing.clockTick0)) *
    test_position_control3_M->Timing.stepSize0;
}

// Model initialize function
void test_position_control3_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(test_position_control3_M, -1);
  test_position_control3_M->Timing.stepSize0 = 0.02;

  // External mode info
  test_position_control3_M->Sizes.checksums[0] = (513544176U);
  test_position_control3_M->Sizes.checksums[1] = (3725342490U);
  test_position_control3_M->Sizes.checksums[2] = (2016317686U);
  test_position_control3_M->Sizes.checksums[3] = (3578172542U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[17];
    test_position_control3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &test_position_control3_DW.EnabledSubsystem_SubsysRanBC_k;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = (sysRanDType *)
      &test_position_control3_DW.IfActionSubsystem_SubsysRanBC;
    systemRan[5] = (sysRanDType *)
      &test_position_control3_DW.IfActionSubsystem1_SubsysRanBC;
    systemRan[6] = (sysRanDType *)
      &test_position_control3_DW.IfActionSubsystem2_SubsysRanBC;
    systemRan[7] = (sysRanDType *)
      &test_position_control3_DW.EnabledSubsystem_SubsysRanBC_c;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = (sysRanDType *)
      &test_position_control3_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[11] = &rtAlwaysEnabled;
    systemRan[12] = &rtAlwaysEnabled;
    systemRan[13] = &rtAlwaysEnabled;
    systemRan[14] = &rtAlwaysEnabled;
    systemRan[15] = &rtAlwaysEnabled;
    systemRan[16] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test_position_control3_M->extModeInfo,
      &test_position_control3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test_position_control3_M->extModeInfo,
                        test_position_control3_M->Sizes.checksums);
    rteiSetTPtr(test_position_control3_M->extModeInfo, rtmGetTPtr
                (test_position_control3_M));
  }

  // data type transition information
  {
    static DataTypeTransInfo dtInfo;
    test_position_control3_M->SpecialInfo.mappingInfo = (&dtInfo);
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

    // InitializeConditions for DiscreteIntegrator: '<S24>/Discrete-Time Integrator' 
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE =
      test_position_control3_P.DiscreteTimeIntegrator_IC;
    test_position_control3_DW.DiscreteTimeIntegrator_PrevRese = 2;

    // InitializeConditions for DiscreteIntegrator: '<S25>/Discrete-Time Integrator' 
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_a =
      test_position_control3_P.DiscreteTimeIntegrator_IC_l;
    test_position_control3_DW.DiscreteTimeIntegrator_PrevRe_p = 2;

    // InitializeConditions for DiscreteIntegrator: '<S26>/Discrete-Time Integrator' 
    test_position_control3_DW.DiscreteTimeIntegrator_DSTATE_k =
      test_position_control3_P.DiscreteTimeIntegrator_IC_g;
    test_position_control3_DW.DiscreteTimeIntegrator_PrevRe_j = 2;

    // SystemInitialize for Atomic SubSystem: '<S3>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S10>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S20>/In1' incorporates:
    //   Outport: '<S20>/Out1'

    test_position_control3_B.In1 = test_position_control3_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S10>/Enabled Subsystem'

    // Start for MATLABSystem: '<S10>/SourceBlock'
    test_position_control3_DW.obj_l.matlabCodegenIsDeleted = false;
    test_position_control3_DW.obj_l.isInitialized = 1;
    for (int32_T i = 0; i < 27; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[27] = '\x00';
    Sub_test_position_control3_194.createSubscriber(&b_zeroDelimTopic[0], 1);
    test_position_control3_DW.obj_l.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S10>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S3>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S2>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S8>/In1' incorporates:
    //   Outport: '<S8>/Out1'

    test_position_control3_B.In1_l = test_position_control3_P.Out1_Y0_d;

    // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'

    // Start for MATLABSystem: '<S7>/SourceBlock'
    test_position_control3_DW.obj_f.matlabCodegenIsDeleted = false;
    test_position_control3_DW.obj_f.isInitialized = 1;
    for (int32_T i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[16] = '\x00';
    Sub_test_position_control3_177.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    test_position_control3_DW.obj_f.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S2>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S4>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S21>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S22>/In1' incorporates:
    //   Outport: '<S22>/Out1'

    test_position_control3_B.In1_e = test_position_control3_P.Out1_Y0_n;

    // End of SystemInitialize for SubSystem: '<S21>/Enabled Subsystem'

    // Start for MATLABSystem: '<S21>/SourceBlock'
    test_position_control3_DW.obj.matlabCodegenIsDeleted = false;
    test_position_control3_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 39; i++) {
      test_position_control3_B.b_zeroDelimTopic[i] = tmp_1[i];
    }

    test_position_control3_B.b_zeroDelimTopic[39] = '\x00';
    Sub_test_position_control3_205.createSubscriber
      (&test_position_control3_B.b_zeroDelimTopic[0], 1);
    test_position_control3_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S21>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S4>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S6>/Publish'
    // Start for MATLABSystem: '<S28>/SinkBlock'
    test_position_control3_DW.obj_m.matlabCodegenIsDeleted = false;
    test_position_control3_DW.obj_m.isInitialized = 1;
    for (int32_T i = 0; i < 13; i++) {
      b_zeroDelimTopic_1[i] = tmp_2[i];
    }

    b_zeroDelimTopic_1[13] = '\x00';
    Pub_test_position_control3_24.createPublisher(&b_zeroDelimTopic_1[0], 1);
    test_position_control3_DW.obj_m.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S28>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<S6>/Publish'
  }
}

// Model terminate function
void test_position_control3_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S3>/Subscribe'
  // Terminate for MATLABSystem: '<S10>/SourceBlock'
  if (!test_position_control3_DW.obj_l.matlabCodegenIsDeleted) {
    test_position_control3_DW.obj_l.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S10>/SourceBlock'
  // End of Terminate for SubSystem: '<S3>/Subscribe'

  // Terminate for Atomic SubSystem: '<S2>/Subscribe'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!test_position_control3_DW.obj_f.matlabCodegenIsDeleted) {
    test_position_control3_DW.obj_f.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'
  // End of Terminate for SubSystem: '<S2>/Subscribe'

  // Terminate for Atomic SubSystem: '<S4>/Subscribe'
  // Terminate for MATLABSystem: '<S21>/SourceBlock'
  if (!test_position_control3_DW.obj.matlabCodegenIsDeleted) {
    test_position_control3_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S21>/SourceBlock'
  // End of Terminate for SubSystem: '<S4>/Subscribe'

  // Terminate for Atomic SubSystem: '<S6>/Publish'
  // Terminate for MATLABSystem: '<S28>/SinkBlock'
  if (!test_position_control3_DW.obj_m.matlabCodegenIsDeleted) {
    test_position_control3_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S28>/SinkBlock'
  // End of Terminate for SubSystem: '<S6>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
