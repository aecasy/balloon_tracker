#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "test_position_control4";

// For Block test_position_control4/Get Autonomy Mode/Subscribe
SimulinkSubscriber<std_msgs::Bool, SL_Bus_test_position_control4_std_msgs_Bool> Sub_test_position_control4_22;

// For Block test_position_control4/Get Mocap Pose/Subscribe
SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_test_position_control4_geometry_msgs_PoseStamped> Sub_test_position_control4_39;

// For Block test_position_control4/Get Mocap Velocity/Subscribe
SimulinkSubscriber<geometry_msgs::TwistStamped, SL_Bus_test_position_control4_geometry_msgs_TwistStamped> Sub_test_position_control4_50;

// For Block test_position_control4/Publish to Pi/Publish
SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_test_position_control4_std_msgs_UInt16MultiArray> Pub_test_position_control4_137;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

