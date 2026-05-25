#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "fjgadhfas_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block fjgadhfas/Get Autonomy Mode/Subscribe
extern SimulinkSubscriber<std_msgs::Bool, SL_Bus_fjgadhfas_std_msgs_Bool> Sub_fjgadhfas_22;

// For Block fjgadhfas/Get Mocap Pose/Subscribe
extern SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_fjgadhfas_geometry_msgs_PoseStamped> Sub_fjgadhfas_39;

// For Block fjgadhfas/Get Mocap Velocity/Subscribe
extern SimulinkSubscriber<geometry_msgs::TwistStamped, SL_Bus_fjgadhfas_geometry_msgs_TwistStamped> Sub_fjgadhfas_50;

// For Block fjgadhfas/Publish to Pi/Publish
extern SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_fjgadhfas_std_msgs_UInt16MultiArray> Pub_fjgadhfas_183;

void slros_node_init(int argc, char** argv);

#endif
