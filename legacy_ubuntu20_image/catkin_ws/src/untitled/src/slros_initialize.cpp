#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "untitled";

// For Block untitled/Get Autonomy Mode/Subscribe
SimulinkSubscriber<std_msgs::Bool, SL_Bus_untitled_std_msgs_Bool> Sub_untitled_22;

// For Block untitled/Get Mocap Pose/Subscribe
SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_untitled_geometry_msgs_PoseStamped> Sub_untitled_39;

// For Block untitled/Get Mocap Velocity/Subscribe
SimulinkSubscriber<geometry_msgs::TwistStamped, SL_Bus_untitled_geometry_msgs_TwistStamped> Sub_untitled_50;

// For Block untitled/Publish to Pi/Publish
SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_untitled_std_msgs_UInt16MultiArray> Pub_untitled_183;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

