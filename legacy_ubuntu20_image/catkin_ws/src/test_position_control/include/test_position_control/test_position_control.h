//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: test_position_control.h
//
// Code generated for Simulink model 'test_position_control'.
//
// Model version                  : 1.12
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Tue Dec 30 16:21:12 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_test_position_control_h_
#define RTW_HEADER_test_position_control_h_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "slros_initialize.h"
#include "test_position_control_types.h"

extern "C"
{

#include "rtGetInf.h"

}

#include <float.h>

extern "C"
{

#include "rt_nonfinite.h"

}

#include <stddef.h>

// Macros for accessing real-time model data structure
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

// Block signals (default storage)
struct B_test_position_control_T {
  SL_Bus_test_position_control_std_msgs_UInt16MultiArray BusAssignment4;// '<S4>/Bus Assignment4' 
  SL_Bus_test_position_control_geometry_msgs_PoseStamped In1;// '<S16>/In1'
  SL_Bus_test_position_control_geometry_msgs_PoseStamped b_varargout_2;
  real_T x;                            // '<S2>/Gain'
  real_T Sum3;                         // '<S3>/Sum3'
  real_T Saturation;                   // '<Root>/Saturation'
  real_T Sum;                          // '<S1>/Sum'
  real_T X;
  real_T Gain6;                        // '<S3>/Gain6'
  real_T Saturation1;                  // '<Root>/Saturation1'
  real_T Sum1;                         // '<S1>/Sum1'
  real_T Z;
  real_T VectorConcatenate[3];         // '<S8>/Vector Concatenate'
  real_T paceerror;                    // '<Root>/Simulation Pace'
  uint16_T DataTypeConversion[128];    // '<S4>/Data Type Conversion'
  real_T Product2;                     // '<S9>/Product2'
  real_T Product1;                     // '<S9>/Product1'
  real_T Product3;                     // '<S9>/Product3'
  real_T Gain3_o;                      // '<S3>/Gain3'
  real_T Gain_p;                       // '<S3>/Gain'
  real_T fcn5;                         // '<S7>/fcn5'
  real_T fcn3;                         // '<S7>/fcn3'
};

// Block states (default storage) for system '<Root>'
struct DW_test_position_control_T {
  ros_slroscpp_internal_block_S_T obj; // '<S6>/SourceBlock'
  ros_slroscpp_internal_block_P_T obj_m;// '<S18>/SinkBlock'
  real_T DiscreteTimeIntegrator_DSTATE;// '<S3>/Discrete-Time Integrator'
  real_T DiscreteTransferFcn1_states;  // '<S3>/Discrete Transfer Fcn1'
  real_T DiscreteTimeIntegrator1_DSTATE;// '<S3>/Discrete-Time Integrator1'
  real_T DiscreteTransferFcn_states;   // '<S3>/Discrete Transfer Fcn'
  struct {
    void *LoggedData;
  } Scope_PWORK;                       // '<S4>/Scope'

  struct {
    void *LoggedData[2];
  } Scope1_PWORK;                      // '<Root>/Scope1'

  struct {
    void *LoggedData[2];
  } Scope2_PWORK;                      // '<Root>/Scope2'

  struct {
    void *LoggedData[3];
  } Scope_PWORK_g;                     // '<S2>/Scope'

  struct {
    void *LoggedData[2];
  } Scope_PWORK_c;                     // '<Root>/Scope'

  struct {
    void *LoggedData[3];
  } Scope3_PWORK;                      // '<S2>/Scope3'

  struct {
    void *LoggedData;
  } Scope5_PWORK;                      // '<Root>/Scope5'

  int8_T EnabledSubsystem_SubsysRanBC; // '<S6>/Enabled Subsystem'
  int8_T IfActionSubsystem2_SubsysRanBC;// '<S10>/If Action Subsystem2'
  int8_T IfActionSubsystem1_SubsysRanBC;// '<S10>/If Action Subsystem1'
  int8_T IfActionSubsystem_SubsysRanBC;// '<S10>/If Action Subsystem'
};

// Parameters (default storage)
struct P_test_position_control_T_ {
  real_T MOT_THST_HOVER_MCS;           // Variable: MOT_THST_HOVER_MCS
                                          //  Referenced by: '<S1>/Thrust for hover'

  real_T STABILIZE;                    // Variable: STABILIZE
                                          //  Referenced by: '<Root>/Flight Mode'

  SL_Bus_test_position_control_std_msgs_UInt16MultiArray Constant_Value;// Computed Parameter: Constant_Value
                                                                      //  Referenced by: '<S17>/Constant'

  SL_Bus_test_position_control_geometry_msgs_PoseStamped Out1_Y0;// Computed Parameter: Out1_Y0
                                                                    //  Referenced by: '<S16>/Out1'

  SL_Bus_test_position_control_geometry_msgs_PoseStamped Constant_Value_o;// Computed Parameter: Constant_Value_o
                                                                      //  Referenced by: '<S6>/Constant'

  real_T Constant_Value_b;             // Expression: 1
                                          //  Referenced by: '<S11>/Constant'

  real_T Constant_Value_m;             // Expression: 1
                                          //  Referenced by: '<S12>/Constant'

  real_T X_ref_Value;                  // Expression: 0
                                          //  Referenced by: '<S3>/X_ref'

  real_T Gain_Gain;                    // Expression: -1
                                          //  Referenced by: '<S2>/Gain'

  real_T Gain1_Gain;                   // Expression: 10
                                          //  Referenced by: '<S3>/Gain1'

  real_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<S3>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC;    // Expression: 0
                                          //  Referenced by: '<S3>/Discrete-Time Integrator'

  real_T Gain7_Gain;                   // Expression: -1
                                          //  Referenced by: '<S3>/Gain7'

  real_T Gain2_Gain;                   // Expression: 5
                                          //  Referenced by: '<S3>/Gain2'

  real_T DiscreteTransferFcn1_NumCoef[2];// Expression: [50 -50]
                                            //  Referenced by: '<S3>/Discrete Transfer Fcn1'

  real_T DiscreteTransferFcn1_DenCoef[2];// Expression: [1 -0.3679]
                                            //  Referenced by: '<S3>/Discrete Transfer Fcn1'

  real_T DiscreteTransferFcn1_InitialSta;// Expression: 0
                                            //  Referenced by: '<S3>/Discrete Transfer Fcn1'

  real_T Saturation_UpperSat;          // Expression: 10
                                          //  Referenced by: '<Root>/Saturation'

  real_T Saturation_LowerSat;          // Expression: -10
                                          //  Referenced by: '<Root>/Saturation'

  real_T Gain_Gain_o;                  // Expression: 1/30
                                          //  Referenced by: '<S1>/Gain'

  real_T Gain1_Gain_c;                 // Expression: 500
                                          //  Referenced by: '<S1>/Gain1'

  real_T Trim_Value;                   // Expression: 1500
                                          //  Referenced by: '<S1>/Trim'

  real_T Y_Ref_Value;                  // Expression: 0
                                          //  Referenced by: '<S3>/Y_Ref'

  real_T Gain4_Gain;                   // Expression: 10
                                          //  Referenced by: '<S3>/Gain4'

  real_T DiscreteTimeIntegrator1_gainval;
                          // Computed Parameter: DiscreteTimeIntegrator1_gainval
                             //  Referenced by: '<S3>/Discrete-Time Integrator1'

  real_T DiscreteTimeIntegrator1_IC;   // Expression: 0
                                          //  Referenced by: '<S3>/Discrete-Time Integrator1'

  real_T Gain8_Gain;                   // Expression: -1
                                          //  Referenced by: '<S3>/Gain8'

  real_T Gain5_Gain;                   // Expression: 5
                                          //  Referenced by: '<S3>/Gain5'

  real_T DiscreteTransferFcn_NumCoef[2];// Expression: [50 -50]
                                           //  Referenced by: '<S3>/Discrete Transfer Fcn'

  real_T DiscreteTransferFcn_DenCoef[2];// Expression: [1 -0.3679]
                                           //  Referenced by: '<S3>/Discrete Transfer Fcn'

  real_T DiscreteTransferFcn_InitialStat;// Expression: 0
                                            //  Referenced by: '<S3>/Discrete Transfer Fcn'

  real_T Gain6_Gain;                   // Expression: -1
                                          //  Referenced by: '<S3>/Gain6'

  real_T Saturation1_UpperSat;         // Expression: 10
                                          //  Referenced by: '<Root>/Saturation1'

  real_T Saturation1_LowerSat;         // Expression: -10
                                          //  Referenced by: '<Root>/Saturation1'

  real_T Gain2_Gain_m;                 // Expression: 1/30
                                          //  Referenced by: '<S1>/Gain2'

  real_T Gain3_Gain;                   // Expression: 500
                                          //  Referenced by: '<S1>/Gain3'

  real_T Zero2_Value;                  // Expression: 0
                                          //  Referenced by: '<Root>/Zero2'

  real_T Zero_Value;                   // Expression: 0
                                          //  Referenced by: '<S4>/Zero'

  real_T Zero3_Value[112];             // Expression: zeros(128-16,1)
                                          //  Referenced by: '<S4>/Zero3'

  real_T Constant_Value_n;             // Expression: 16
                                          //  Referenced by: '<S4>/Constant'

  real_T Gain3_Gain_f;                 // Expression: 0
                                          //  Referenced by: '<S3>/Gain3'

  real_T Gain_Gain_c;                  // Expression: 0
                                          //  Referenced by: '<S3>/Gain'

  real_T SimulationPace_P1;            // Expression: SimulationPace
                                          //  Referenced by: '<Root>/Simulation Pace'

  real_T SimulationPace_P2;            // Expression: 2
                                          //  Referenced by: '<Root>/Simulation Pace'

  real_T SimulationPace_P3;            // Expression: OutputPaceError
                                          //  Referenced by: '<Root>/Simulation Pace'

  real_T SimulationPace_P4;            // Expression: SampleTime
                                          //  Referenced by: '<Root>/Simulation Pace'

};

// Real-time Model Data Structure
struct tag_RTM_test_position_control_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    uint32_T checksums[4];
  } Sizes;

  //
  //  SpecialInfo:
  //  The following substructure contains special information
  //  related to other components that are dependent on RTW.

  struct {
    const void *mappingInfo;
  } SpecialInfo;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_test_position_control_T test_position_control_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_test_position_control_T test_position_control_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_test_position_control_T test_position_control_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void test_position_control_initialize(void);
  extern void test_position_control_step(void);
  extern void test_position_control_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_test_position_contro_T *const test_position_control_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S4>/Zero-Order Hold1' : Eliminated since input and output rates are identical


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'test_position_control'
//  '<S1>'   : 'test_position_control/Convert to PWM'
//  '<S2>'   : 'test_position_control/Get Mocap Position'
//  '<S3>'   : 'test_position_control/Position Control'
//  '<S4>'   : 'test_position_control/Publish to Pi'
//  '<S5>'   : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1'
//  '<S6>'   : 'test_position_control/Get Mocap Position/Subscribe'
//  '<S7>'   : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles'
//  '<S8>'   : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation'
//  '<S9>'   : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Quaternion Normalize'
//  '<S10>'  : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input'
//  '<S11>'  : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem'
//  '<S12>'  : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem1'
//  '<S13>'  : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem2'
//  '<S14>'  : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus'
//  '<S15>'  : 'test_position_control/Get Mocap Position/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
//  '<S16>'  : 'test_position_control/Get Mocap Position/Subscribe/Enabled Subsystem'
//  '<S17>'  : 'test_position_control/Publish to Pi/Blank Message4'
//  '<S18>'  : 'test_position_control/Publish to Pi/Publish'

#endif                                 // RTW_HEADER_test_position_control_h_

//
// File trailer for generated code.
//
// [EOF]
//
