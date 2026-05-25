#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "test_position_control2";

// For Block test_position_control2/Get Mocap Position/Subscribe
SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_test_position_control2_geometry_msgs_PoseStamped> Sub_test_position_control2_15;

// For Block test_position_control2/Publish to Pi/Publish
SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_test_position_control2_std_msgs_UInt16MultiArray> Pub_test_position_control2_24;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

