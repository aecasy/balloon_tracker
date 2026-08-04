//
//  test_position_control3_dt.h
//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  Code generation for model "test_position_control3".
//
//  Model version              : 1.22
//  Simulink Coder version : 9.8 (R2022b) 13-May-2022
//  C++ source code generated on : Tue Dec 30 19:17:00 2025
//
//  Target selection: ert.tlc
//  Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
//  Code generation objectives: Unspecified
//  Validation result: Not run


#include "ext_types.h"

// data type size table
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int32_T),
  sizeof(SL_Bus_test_position_control3_std_msgs_Bool),
  sizeof(SL_Bus_test_position_control3_ros_time_Time),
  sizeof(SL_Bus_ROSVariableLengthArrayInfo),
  sizeof(SL_Bus_test_position_control3_std_msgs_Header),
  sizeof(SL_Bus_test_position_control3_geometry_msgs_Point),
  sizeof(SL_Bus_test_position_control3_geometry_msgs_Quaternion),
  sizeof(SL_Bus_test_position_control3_geometry_msgs_Pose),
  sizeof(SL_Bus_test_position_control3_geometry_msgs_PoseStamped),
  sizeof(SL_Bus_test_position_control3_geometry_msgs_Vector3),
  sizeof(SL_Bus_test_position_control3_geometry_msgs_Twist),
  sizeof(SL_Bus_test_position_control3_geometry_msgs_TwistStamped),
  sizeof(SL_Bus_test_position_control3_std_msgs_MultiArrayDimension),
  sizeof(SL_Bus_test_position_control3_std_msgs_MultiArrayLayout),
  sizeof(SL_Bus_test_position_control3_std_msgs_UInt16MultiArray),
  sizeof(ros_slroscpp_internal_block_S_T),
  sizeof(ros_slroscpp_internal_block_P_T),
  sizeof(uint_T),
  sizeof(char_T),
  sizeof(uchar_T),
  sizeof(time_T)
};

// data type name table
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "physical_connection",
  "SL_Bus_test_position_control3_std_msgs_Bool",
  "SL_Bus_test_position_control3_ros_time_Time",
  "SL_Bus_ROSVariableLengthArrayInfo",
  "SL_Bus_test_position_control3_std_msgs_Header",
  "SL_Bus_test_position_control3_geometry_msgs_Point",
  "SL_Bus_test_position_control3_geometry_msgs_Quaternion",
  "SL_Bus_test_position_control3_geometry_msgs_Pose",
  "SL_Bus_test_position_control3_geometry_msgs_PoseStamped",
  "SL_Bus_test_position_control3_geometry_msgs_Vector3",
  "SL_Bus_test_position_control3_geometry_msgs_Twist",
  "SL_Bus_test_position_control3_geometry_msgs_TwistStamped",
  "SL_Bus_test_position_control3_std_msgs_MultiArrayDimension",
  "SL_Bus_test_position_control3_std_msgs_MultiArrayLayout",
  "SL_Bus_test_position_control3_std_msgs_UInt16MultiArray",
  "ros_slroscpp_internal_block_S_T",
  "ros_slroscpp_internal_block_P_T",
  "uint_T",
  "char_T",
  "uchar_T",
  "time_T"
};

// data type transitions for block I/O structure
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&test_position_control3_B.In1), 22, 0, 1 },

  { (char_T *)(&test_position_control3_B.In1_e), 25, 0, 1 },

  { (char_T *)(&test_position_control3_B.VectorConcatenate[0]), 0, 0, 27 },

  { (char_T *)(&test_position_control3_B.In1_l), 15, 0, 1 },

  { (char_T *)(&test_position_control3_B.DataTypeConversion[0]), 5, 0, 128 }
  ,

  { (char_T *)(&test_position_control3_DW.obj), 29, 0, 3 },

  { (char_T *)(&test_position_control3_DW.obj_m), 30, 0, 1 },

  { (char_T *)(&test_position_control3_DW.DiscreteTimeIntegrator_DSTATE), 0, 0,
    3 },

  { (char_T *)(&test_position_control3_DW.Scope_PWORK.LoggedData), 11, 0, 33 },

  { (char_T *)(&test_position_control3_DW.DiscreteTimeIntegrator_PrevRese), 2, 0,
    9 }
};

// data type transition table for block I/O structure
static DataTypeTransitionTable rtBTransTable = {
  10U,
  rtBTransitions
};

// data type transitions for Parameters structure
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&test_position_control3_P.I_max_XY), 0, 0, 4 },

  { (char_T *)(&test_position_control3_P.Constant_Value), 28, 0, 1 },

  { (char_T *)(&test_position_control3_P.Out1_Y0), 22, 0, 1 },

  { (char_T *)(&test_position_control3_P.Constant_Value_a), 22, 0, 1 },

  { (char_T *)(&test_position_control3_P.Out1_Y0_n), 25, 0, 1 },

  { (char_T *)(&test_position_control3_P.Constant_Value_a2), 25, 0, 1 },

  { (char_T *)(&test_position_control3_P.Out1_Y0_d), 15, 0, 1 },

  { (char_T *)(&test_position_control3_P.Constant_Value_f), 15, 0, 1 },

  { (char_T *)(&test_position_control3_P.Constant_Value_p), 0, 0, 154 }
};

// data type transition table for Parameters structure
static DataTypeTransitionTable rtPTransTable = {
  9U,
  rtPTransitions
};

// [EOF] test_position_control3_dt.h
