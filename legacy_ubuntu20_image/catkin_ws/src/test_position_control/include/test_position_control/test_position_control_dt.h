//
//  test_position_control_dt.h
//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  Code generation for model "test_position_control".
//
//  Model version              : 1.12
//  Simulink Coder version : 9.8 (R2022b) 13-May-2022
//  C++ source code generated on : Tue Dec 30 16:21:12 2025
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
  sizeof(SL_Bus_test_position_control_ros_time_Time),
  sizeof(SL_Bus_ROSVariableLengthArrayInfo),
  sizeof(SL_Bus_test_position_control_std_msgs_Header),
  sizeof(SL_Bus_test_position_control_geometry_msgs_Point),
  sizeof(SL_Bus_test_position_control_geometry_msgs_Quaternion),
  sizeof(SL_Bus_test_position_control_geometry_msgs_Pose),
  sizeof(SL_Bus_test_position_control_geometry_msgs_PoseStamped),
  sizeof(SL_Bus_test_position_control_std_msgs_MultiArrayDimension),
  sizeof(SL_Bus_test_position_control_std_msgs_MultiArrayLayout),
  sizeof(SL_Bus_test_position_control_std_msgs_UInt16MultiArray),
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
  "SL_Bus_test_position_control_ros_time_Time",
  "SL_Bus_ROSVariableLengthArrayInfo",
  "SL_Bus_test_position_control_std_msgs_Header",
  "SL_Bus_test_position_control_geometry_msgs_Point",
  "SL_Bus_test_position_control_geometry_msgs_Quaternion",
  "SL_Bus_test_position_control_geometry_msgs_Pose",
  "SL_Bus_test_position_control_geometry_msgs_PoseStamped",
  "SL_Bus_test_position_control_std_msgs_MultiArrayDimension",
  "SL_Bus_test_position_control_std_msgs_MultiArrayLayout",
  "SL_Bus_test_position_control_std_msgs_UInt16MultiArray",
  "ros_slroscpp_internal_block_S_T",
  "ros_slroscpp_internal_block_P_T",
  "uint_T",
  "char_T",
  "uchar_T",
  "time_T"
};

// data type transitions for block I/O structure
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&test_position_control_B.In1), 21, 0, 1 },

  { (char_T *)(&test_position_control_B.x), 0, 0, 13 },

  { (char_T *)(&test_position_control_B.DataTypeConversion[0]), 5, 0, 128 }
  ,

  { (char_T *)(&test_position_control_DW.obj), 25, 0, 1 },

  { (char_T *)(&test_position_control_DW.obj_m), 26, 0, 1 },

  { (char_T *)(&test_position_control_DW.DiscreteTimeIntegrator_DSTATE), 0, 0, 4
  },

  { (char_T *)(&test_position_control_DW.Scope_PWORK.LoggedData), 11, 0, 14 },

  { (char_T *)(&test_position_control_DW.EnabledSubsystem_SubsysRanBC), 2, 0, 4
  }
};

// data type transition table for block I/O structure
static DataTypeTransitionTable rtBTransTable = {
  8U,
  rtBTransitions
};

// data type transitions for Parameters structure
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&test_position_control_P.MOT_THST_HOVER_MCS), 0, 0, 2 },

  { (char_T *)(&test_position_control_P.Constant_Value), 24, 0, 1 },

  { (char_T *)(&test_position_control_P.Out1_Y0), 21, 0, 1 },

  { (char_T *)(&test_position_control_P.Constant_Value_o), 21, 0, 1 },

  { (char_T *)(&test_position_control_P.Constant_Value_b), 0, 0, 156 }
};

// data type transition table for Parameters structure
static DataTypeTransitionTable rtPTransTable = {
  5U,
  rtPTransitions
};

// [EOF] test_position_control_dt.h
