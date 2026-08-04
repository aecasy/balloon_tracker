#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "fjgadhfas";

// For Block fjgadhfas/Get Autonomy Mode/Subscribe
SimulinkSubscriber<std_msgs::Bool, SL_Bus_fjgadhfas_std_msgs_Bool> Sub_fjgadhfas_22;

// For Block fjgadhfas/Get Mocap Pose/Subscribe
SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_fjgadhfas_geometry_msgs_PoseStamped> Sub_fjgadhfas_39;

// For Block fjgadhfas/Get Mocap Velocity/Subscribe
SimulinkSubscriber<geometry_msgs::TwistStamped, SL_Bus_fjgadhfas_geometry_msgs_TwistStamped> Sub_fjgadhfas_50;

// For Block fjgadhfas/Publish to Pi/Publish
SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_fjgadhfas_std_msgs_UInt16MultiArray> Pub_fjgadhfas_183;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

