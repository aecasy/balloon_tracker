#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "fjgadhfas2_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block fjgadhfas2/Get Autonomy Mode/Subscribe
extern SimulinkSubscriber<std_msgs::Bool, SL_Bus_fjgadhfas2_std_msgs_Bool> Sub_fjgadhfas2_22;

// For Block fjgadhfas2/Get Mocap Pose/Subscribe
extern SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_fjgadhfas2_geometry_msgs_PoseStamped> Sub_fjgadhfas2_39;

// For Block fjgadhfas2/Get Mocap Velocity/Subscribe
extern SimulinkSubscriber<geometry_msgs::TwistStamped, SL_Bus_fjgadhfas2_geometry_msgs_TwistStamped> Sub_fjgadhfas2_50;

// For Block fjgadhfas2/Publish to Pi/Publish
extern SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_fjgadhfas2_std_msgs_UInt16MultiArray> Pub_fjgadhfas2_183;

void slros_node_init(int argc, char** argv);

#endif
