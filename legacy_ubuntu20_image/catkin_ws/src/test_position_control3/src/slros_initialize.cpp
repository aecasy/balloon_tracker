#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "test_position_control3";

// For Block test_position_control3/Get Autonomy Mode/Subscribe
SimulinkSubscriber<std_msgs::Bool, SL_Bus_test_position_control3_std_msgs_Bool> Sub_test_position_control3_177;

// For Block test_position_control3/Get Mocap Pose/Subscribe
SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_test_position_control3_geometry_msgs_PoseStamped> Sub_test_position_control3_194;

// For Block test_position_control3/Get Mocap Velocity/Subscribe
SimulinkSubscriber<geometry_msgs::TwistStamped, SL_Bus_test_position_control3_geometry_msgs_TwistStamped> Sub_test_position_control3_205;

// For Block test_position_control3/Publish to Pi/Publish
SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_test_position_control3_std_msgs_UInt16MultiArray> Pub_test_position_control3_24;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

