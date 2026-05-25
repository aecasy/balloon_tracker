//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: test_position_control4.h
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
#ifndef RTW_HEADER_test_position_control4_h_
#define RTW_HEADER_test_position_control4_h_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "slros_initialize.h"
#include "test_position_control4_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetInf.h"

}

#include <float.h>
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
struct B_test_position_control4_T {
  SL_Bus_test_position_control4_std_msgs_UInt16MultiArray BusAssignment4;// '<S6>/Bus Assignment4' 
  SL_Bus_test_position_control4_geometry_msgs_PoseStamped In1;// '<S20>/In1'
  SL_Bus_test_position_control4_geometry_msgs_PoseStamped b_varargout_2;
  SL_Bus_test_position_control4_geometry_msgs_TwistStamped In1_d;// '<S22>/In1'
  SL_Bus_test_position_control4_geometry_msgs_TwistStamped b_varargout_2_m;
  char_T b_zeroDelimTopic[40];
  real_T x;                            // '<S3>/Gain'
  real_T X;
  real_T Z;
  real_T VectorConcatenate[3];         // '<S12>/Vector Concatenate'
  real_T DiscreteTimeIntegrator;       // '<S25>/Discrete-Time Integrator'
  real_T Gain;                         // '<S25>/Gain'
  real_T x_d;                          // '<S4>/Gain'
  real_T Gain2;                        // '<S25>/Gain2'
  real_T DiscreteTimeIntegrator_m;     // '<S26>/Discrete-Time Integrator'
  real_T Gain_o;                       // '<S26>/Gain'
  real_T X_h;
  real_T Gain2_h;                      // '<S26>/Gain2'
  real_T Switch1;                      // '<S5>/Switch1'
  real_T Saturation;                   // '<Root>/Saturation'
  real_T Sum;                          // '<S1>/Sum'
  real_T Switch;                       // '<S5>/Switch'
  real_T Saturation1;                  // '<Root>/Saturation1'
  real_T Sum1;                         // '<S1>/Sum1'
  real_T DiscreteTimeIntegrator_i;     // '<S27>/Discrete-Time Integrator'
  real_T Gain_g;                       // '<S27>/Gain'
  real_T Z_n;
  real_T Gain2_f;                      // '<S27>/Gain2'
  real_T Switch2;                      // '<S5>/Switch2'
  real_T Saturation2;                  // '<Root>/Saturation2'
  real_T paceerror;                    // '<Root>/Simulation Pace'
  real_T d;                            // '<S28>/MATLAB Function'
  real_T v;                            // '<S28>/MATLAB Function'
  real_T dx;
  real_T dy;
  real_T dz;
  real_T Product2;                     // '<S13>/Product2'
  real_T Sum4;                         // '<S1>/Sum4'
  real_T VectorConcatenate_tmp;
  real_T VectorConcatenate_tmp_c;
  SL_Bus_test_position_control4_std_msgs_Bool In1_p;// '<S8>/In1'
  uint16_T DataTypeConversion[128];    // '<S6>/Data Type Conversion'
  uint8_T filled_;                     // '<S28>/MATLAB Function'
  boolean_T Valid;                     // '<S28>/MATLAB Function'
  boolean_T frozenNow;                 // '<S28>/MATLAB Function'
  boolean_T updated;                   // '<S28>/MATLAB Function'
};

// Block states (default storage) for system '<Root>'
struct DW_test_position_control4_T {
  ros_slroscpp_internal_block_S_T obj; // '<S21>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_k;// '<S10>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_d;// '<S7>/SourceBlock'
  ros_slroscpp_internal_block_P_T obj_e;// '<S31>/SinkBlock'
  real_T DiscreteTimeIntegrator_DSTATE;// '<S25>/Discrete-Time Integrator'
  real_T DiscreteTimeIntegrator_DSTATE_j;// '<S26>/Discrete-Time Integrator'
  real_T DiscreteTimeIntegrator_DSTATE_g;// '<S27>/Discrete-Time Integrator'
  real_T bufX[6];                      // '<S28>/MATLAB Function'
  real_T bufY[6];                      // '<S28>/MATLAB Function'
  real_T bufZ[6];                      // '<S28>/MATLAB Function'
  struct {
    void *LoggedData;
  } Scope_PWORK;                       // '<S6>/Scope'

  struct {
    void *LoggedData[2];
  } Scope6_PWORK;                      // '<Root>/Scope6'

  struct {
    void *LoggedData[3];
  } Scope_PWORK_c;                     // '<S27>/Scope'

  struct {
    void *LoggedData;
  } Scope3_PWORK;                      // '<Root>/Scope3'

  struct {
    void *LoggedData[3];
  } Scope3_PWORK_k;                    // '<S4>/Scope3'

  struct {
    void *LoggedData[2];
  } Scope1_PWORK;                      // '<Root>/Scope1'

  struct {
    void *LoggedData[2];
  } Scope2_PWORK;                      // '<Root>/Scope2'

  struct {
    void *LoggedData[2];
  } Scope_PWORK_m;                     // '<Root>/Scope'

  struct {
    void *LoggedData[3];
  } Scope_PWORK_a;                     // '<S26>/Scope'

  struct {
    void *LoggedData[3];
  } Scope_PWORK_p;                     // '<S25>/Scope'

  struct {
    void *LoggedData[4];
  } Scope_PWORK_k;                     // '<S28>/Scope'

  struct {
    void *LoggedData[2];
  } Scope1_PWORK_l;                    // '<S28>/Scope1'

  struct {
    void *LoggedData;
  } Scope4_PWORK;                      // '<Root>/Scope4'

  struct {
    void *LoggedData[3];
  } Scope_PWORK_d;                     // '<S3>/Scope'

  struct {
    void *LoggedData[3];
  } Scope3_PWORK_n;                    // '<S3>/Scope3'

  struct {
    void *LoggedData;
  } Scope5_PWORK;                      // '<Root>/Scope5'

  struct {
    void *LoggedData[3];
  } Scope_PWORK_kn;                    // '<S4>/Scope'

  int8_T DiscreteTimeIntegrator_PrevRese;// '<S25>/Discrete-Time Integrator'
  int8_T DiscreteTimeIntegrator_PrevRe_h;// '<S26>/Discrete-Time Integrator'
  int8_T DiscreteTimeIntegrator_PrevRe_f;// '<S27>/Discrete-Time Integrator'
  int8_T EnabledSubsystem_SubsysRanBC; // '<S21>/Enabled Subsystem'
  int8_T EnabledSubsystem_SubsysRanBC_d;// '<S10>/Enabled Subsystem'
  int8_T IfActionSubsystem2_SubsysRanBC;// '<S14>/If Action Subsystem2'
  int8_T IfActionSubsystem1_SubsysRanBC;// '<S14>/If Action Subsystem1'
  int8_T IfActionSubsystem_SubsysRanBC;// '<S14>/If Action Subsystem'
  int8_T EnabledSubsystem_SubsysRanBC_o;// '<S7>/Enabled Subsystem'
  uint8_T idx;                         // '<S28>/MATLAB Function'
  uint8_T filled;                      // '<S28>/MATLAB Function'
  uint8_T goodCnt;                     // '<S28>/MATLAB Function'
  boolean_T inLost;                    // '<S28>/MATLAB Function'
};

// Parameters (default storage)
struct P_test_position_control4_T_ {
  real_T I_max_XY;                     // Variable: I_max_XY
                                          //  Referenced by:
                                          //    '<S25>/Discrete-Time Integrator'
                                          //    '<S26>/Discrete-Time Integrator'

  real_T I_max_Z;                      // Variable: I_max_Z
                                          //  Referenced by: '<S27>/Discrete-Time Integrator'

  real_T MOT_THST_HOVER_MCS;           // Variable: MOT_THST_HOVER_MCS
                                          //  Referenced by: '<S1>/Thrust for hover'

  real_T STABILIZE;                    // Variable: STABILIZE
                                          //  Referenced by: '<Root>/Flight Mode'

  real_T time_step;                    // Variable: time_step
                                          //  Referenced by: '<S28>/Constant'

  SL_Bus_test_position_control4_std_msgs_UInt16MultiArray Constant_Value;// Computed Parameter: Constant_Value
                                                                      //  Referenced by: '<S30>/Constant'

  SL_Bus_test_position_control4_geometry_msgs_PoseStamped Out1_Y0;// Computed Parameter: Out1_Y0
                                                                     //  Referenced by: '<S20>/Out1'

  SL_Bus_test_position_control4_geometry_msgs_PoseStamped Constant_Value_p;// Computed Parameter: Constant_Value_p
                                                                      //  Referenced by: '<S10>/Constant'

  SL_Bus_test_position_control4_geometry_msgs_TwistStamped Out1_Y0_e;// Computed Parameter: Out1_Y0_e
                                                                      //  Referenced by: '<S22>/Out1'

  SL_Bus_test_position_control4_geometry_msgs_TwistStamped Constant_Value_e;// Computed Parameter: Constant_Value_e
                                                                      //  Referenced by: '<S21>/Constant'

  SL_Bus_test_position_control4_std_msgs_Bool Out1_Y0_k;// Computed Parameter: Out1_Y0_k
                                                           //  Referenced by: '<S8>/Out1'

  SL_Bus_test_position_control4_std_msgs_Bool Constant_Value_m;// Computed Parameter: Constant_Value_m
                                                                  //  Referenced by: '<S7>/Constant'

  real_T Constant_Value_ey;            // Expression: 1
                                          //  Referenced by: '<S15>/Constant'

  real_T Constant_Value_b;             // Expression: 1
                                          //  Referenced by: '<S16>/Constant'

  real_T Constant1_Value;              // Expression: 0
                                          //  Referenced by: '<S5>/Constant1'

  real_T Constant2_Value;              // Expression: 0
                                          //  Referenced by: '<S5>/Constant2'

  real_T Constant_Value_k;             // Expression: 0
                                          //  Referenced by: '<S5>/Constant'

  real_T Trim_Value;                   // Expression: 1490
                                          //  Referenced by: '<S1>/Trim'

  real_T Gain_Gain;                    // Expression: -1
                                          //  Referenced by: '<S3>/Gain'

  real_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<S25>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC;    // Expression: 0
                                          //  Referenced by: '<S25>/Discrete-Time Integrator'

  real_T X_ref_Value;                  // Expression: 0
                                          //  Referenced by: '<S5>/X_ref'

  real_T Gain_Gain_g;                  // Expression: 20
                                          //  Referenced by: '<S25>/Gain'

  real_T Gain_Gain_n;                  // Expression: -1
                                          //  Referenced by: '<S4>/Gain'

  real_T Gain2_Gain;                   // Expression: 22
                                          //  Referenced by: '<S25>/Gain2'

  real_T DiscreteTimeIntegrator_gainva_d;
                          // Computed Parameter: DiscreteTimeIntegrator_gainva_d
                             //  Referenced by: '<S26>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC_f;  // Expression: 0
                                          //  Referenced by: '<S26>/Discrete-Time Integrator'

  real_T Y_ref_Value;                  // Expression: 0
                                          //  Referenced by: '<S5>/Y_ref'

  real_T Gain_Gain_h;                  // Expression: 16
                                          //  Referenced by: '<S26>/Gain'

  real_T Gain2_Gain_j;                 // Expression: 14
                                          //  Referenced by: '<S26>/Gain2'

  real_T Saturation_UpperSat;          // Expression: 10
                                          //  Referenced by: '<Root>/Saturation'

  real_T Saturation_LowerSat;          // Expression: -10
                                          //  Referenced by: '<Root>/Saturation'

  real_T Gain_Gain_hz;                 // Expression: 1/30
                                          //  Referenced by: '<S1>/Gain'

  real_T Gain1_Gain;                   // Expression: 500
                                          //  Referenced by: '<S1>/Gain1'

  real_T Trim1_Value;                  // Expression: 1498
                                          //  Referenced by: '<S1>/Trim1'

  real_T Saturation1_UpperSat;         // Expression: 10
                                          //  Referenced by: '<Root>/Saturation1'

  real_T Saturation1_LowerSat;         // Expression: -10
                                          //  Referenced by: '<Root>/Saturation1'

  real_T Gain2_Gain_je;                // Expression: 1/30
                                          //  Referenced by: '<S1>/Gain2'

  real_T Gain3_Gain;                   // Expression: 500
                                          //  Referenced by: '<S1>/Gain3'

  real_T DiscreteTimeIntegrator_gainva_i;
                          // Computed Parameter: DiscreteTimeIntegrator_gainva_i
                             //  Referenced by: '<S27>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC_m;  // Expression: 0
                                          //  Referenced by: '<S27>/Discrete-Time Integrator'

  real_T Z_ref_Value;                  // Expression: 1.5
                                          //  Referenced by: '<S5>/Z_ref'

  real_T Gain_Gain_e;                  // Expression: 6
                                          //  Referenced by: '<S27>/Gain'

  real_T Gain2_Gain_p;                 // Expression: 5
                                          //  Referenced by: '<S27>/Gain2'

  real_T Saturation2_UpperSat;         // Expression: 3
                                          //  Referenced by: '<Root>/Saturation2'

  real_T Saturation2_LowerSat;         // Expression: -3
                                          //  Referenced by: '<Root>/Saturation2'

  real_T Frommotorteststand_Gain;      // Expression: 25
                                          //  Referenced by: '<S1>/From motor test stand'

  real_T Zero2_Value;                  // Expression: 0
                                          //  Referenced by: '<Root>/Zero2'

  real_T Zero_Value;                   // Expression: 0
                                          //  Referenced by: '<S6>/Zero'

  real_T Zero3_Value[112];             // Expression: zeros(128-16,1)
                                          //  Referenced by: '<S6>/Zero3'

  real_T Constant_Value_a;             // Expression: 16
                                          //  Referenced by: '<S6>/Constant'

  real_T Gain1_Gain_m;                 // Expression: 1.5
                                          //  Referenced by: '<S27>/Gain1'

  real_T Gain1_Gain_o;                 // Expression: 5
                                          //  Referenced by: '<S26>/Gain1'

  real_T Gain1_Gain_mj;                // Expression: 5
                                          //  Referenced by: '<S25>/Gain1'

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

  extern P_test_position_control4_T test_position_control4_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_test_position_control4_T test_position_control4_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_test_position_control4_T test_position_control4_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void test_position_control4_initialize(void);
  extern void test_position_control4_step(void);
  extern void test_position_control4_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_test_position_contro_T *const test_position_control4_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S6>/Zero-Order Hold1' : Eliminated since input and output rates are identical


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
//  '<Root>' : 'test_position_control4'
//  '<S1>'   : 'test_position_control4/Convert to PWM'
//  '<S2>'   : 'test_position_control4/Get Autonomy Mode'
//  '<S3>'   : 'test_position_control4/Get Mocap Pose'
//  '<S4>'   : 'test_position_control4/Get Mocap Velocity'
//  '<S5>'   : 'test_position_control4/Position Control'
//  '<S6>'   : 'test_position_control4/Publish to Pi'
//  '<S7>'   : 'test_position_control4/Get Autonomy Mode/Subscribe'
//  '<S8>'   : 'test_position_control4/Get Autonomy Mode/Subscribe/Enabled Subsystem'
//  '<S9>'   : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1'
//  '<S10>'  : 'test_position_control4/Get Mocap Pose/Subscribe'
//  '<S11>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles'
//  '<S12>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation'
//  '<S13>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Quaternion Normalize'
//  '<S14>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input'
//  '<S15>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem'
//  '<S16>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem1'
//  '<S17>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem2'
//  '<S18>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus'
//  '<S19>'  : 'test_position_control4/Get Mocap Pose/Quaternion to Euler (ROS)1/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
//  '<S20>'  : 'test_position_control4/Get Mocap Pose/Subscribe/Enabled Subsystem'
//  '<S21>'  : 'test_position_control4/Get Mocap Velocity/Subscribe'
//  '<S22>'  : 'test_position_control4/Get Mocap Velocity/Subscribe/Enabled Subsystem'
//  '<S23>'  : 'test_position_control4/Position Control/MATLAB Function'
//  '<S24>'  : 'test_position_control4/Position Control/MATLAB Function1'
//  '<S25>'  : 'test_position_control4/Position Control/PID X_E'
//  '<S26>'  : 'test_position_control4/Position Control/PID Y_E'
//  '<S27>'  : 'test_position_control4/Position Control/PID Z_E'
//  '<S28>'  : 'test_position_control4/Position Control/Validity Verifier'
//  '<S29>'  : 'test_position_control4/Position Control/Validity Verifier/MATLAB Function'
//  '<S30>'  : 'test_position_control4/Publish to Pi/Blank Message4'
//  '<S31>'  : 'test_position_control4/Publish to Pi/Publish'

#endif                                 // RTW_HEADER_test_position_control4_h_

//
// File trailer for generated code.
//
// [EOF]
//
