//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: test_position_control4_types.h
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
#ifndef RTW_HEADER_test_position_control4_types_h_
#define RTW_HEADER_test_position_control4_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_Bool_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_Bool_

// MsgType=std_msgs/Bool
struct SL_Bus_test_position_control4_std_msgs_Bool
{
  boolean_T Data;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_ros_time_Time_

// MsgType=ros_time/Time
struct SL_Bus_test_position_control4_ros_time_Time
{
  real_T Sec;
  real_T Nsec;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

struct SL_Bus_ROSVariableLengthArrayInfo
{
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_Header_

// MsgType=std_msgs/Header
struct SL_Bus_test_position_control4_std_msgs_Header
{
  uint32_T Seq;

  // MsgType=ros_time/Time
  SL_Bus_test_position_control4_ros_time_Time Stamp;

  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=FrameId_SL_Info:TruncateAction=warn 
  uint8_T FrameId[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=FrameId
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Point_

// MsgType=geometry_msgs/Point
struct SL_Bus_test_position_control4_geometry_msgs_Point
{
  real_T X;
  real_T Y;
  real_T Z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Quaternion_

// MsgType=geometry_msgs/Quaternion
struct SL_Bus_test_position_control4_geometry_msgs_Quaternion
{
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Pose_

// MsgType=geometry_msgs/Pose
struct SL_Bus_test_position_control4_geometry_msgs_Pose
{
  // MsgType=geometry_msgs/Point
  SL_Bus_test_position_control4_geometry_msgs_Point Position;

  // MsgType=geometry_msgs/Quaternion
  SL_Bus_test_position_control4_geometry_msgs_Quaternion Orientation;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_PoseStamped_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_PoseStamped_

// MsgType=geometry_msgs/PoseStamped
struct SL_Bus_test_position_control4_geometry_msgs_PoseStamped
{
  // MsgType=std_msgs/Header
  SL_Bus_test_position_control4_std_msgs_Header Header;

  // MsgType=geometry_msgs/Pose
  SL_Bus_test_position_control4_geometry_msgs_Pose Pose;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Vector3_

// MsgType=geometry_msgs/Vector3
struct SL_Bus_test_position_control4_geometry_msgs_Vector3
{
  real_T X;
  real_T Y;
  real_T Z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_Twist_

// MsgType=geometry_msgs/Twist
struct SL_Bus_test_position_control4_geometry_msgs_Twist
{
  // MsgType=geometry_msgs/Vector3
  SL_Bus_test_position_control4_geometry_msgs_Vector3 Linear;

  // MsgType=geometry_msgs/Vector3
  SL_Bus_test_position_control4_geometry_msgs_Vector3 Angular;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_TwistStamped_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_geometry_msgs_TwistStamped_

// MsgType=geometry_msgs/TwistStamped
struct SL_Bus_test_position_control4_geometry_msgs_TwistStamped
{
  // MsgType=std_msgs/Header
  SL_Bus_test_position_control4_std_msgs_Header Header;

  // MsgType=geometry_msgs/Twist
  SL_Bus_test_position_control4_geometry_msgs_Twist Twist;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_MultiArrayDimension_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_MultiArrayDimension_

// MsgType=std_msgs/MultiArrayDimension
struct SL_Bus_test_position_control4_std_msgs_MultiArrayDimension
{
  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=Label_SL_Info:TruncateAction=warn 
  uint8_T Label[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Label
  SL_Bus_ROSVariableLengthArrayInfo Label_SL_Info;
  uint32_T Size;
  uint32_T Stride;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_MultiArrayLayout_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_MultiArrayLayout_

// MsgType=std_msgs/MultiArrayLayout
struct SL_Bus_test_position_control4_std_msgs_MultiArrayLayout
{
  // MsgType=std_msgs/MultiArrayDimension:IsVarLen=1:VarLenCategory=data:VarLenElem=Dim_SL_Info:TruncateAction=warn 
  SL_Bus_test_position_control4_std_msgs_MultiArrayDimension Dim[16];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Dim
  SL_Bus_ROSVariableLengthArrayInfo Dim_SL_Info;
  uint32_T DataOffset;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_UInt16MultiArray_
#define DEFINED_TYPEDEF_FOR_SL_Bus_test_position_control4_std_msgs_UInt16MultiArray_

// MsgType=std_msgs/UInt16MultiArray
struct SL_Bus_test_position_control4_std_msgs_UInt16MultiArray
{
  // MsgType=std_msgs/MultiArrayLayout
  SL_Bus_test_position_control4_std_msgs_MultiArrayLayout Layout;

  // IsVarLen=1:VarLenCategory=data:VarLenElem=Data_SL_Info:TruncateAction=warn
  uint16_T Data[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Data
  SL_Bus_ROSVariableLengthArrayInfo Data_SL_Info;
};

#endif

#ifndef struct_ros_slroscpp_internal_block_S_T
#define struct_ros_slroscpp_internal_block_S_T

struct ros_slroscpp_internal_block_S_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                // struct_ros_slroscpp_internal_block_S_T

#ifndef struct_ros_slroscpp_internal_block_P_T
#define struct_ros_slroscpp_internal_block_P_T

struct ros_slroscpp_internal_block_P_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                // struct_ros_slroscpp_internal_block_P_T

// Parameters (default storage)
typedef struct P_test_position_control4_T_ P_test_position_control4_T;

// Forward declaration for rtModel
typedef struct tag_RTM_test_position_control_T RT_MODEL_test_position_contro_T;

#endif                            // RTW_HEADER_test_position_control4_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
