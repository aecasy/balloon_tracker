#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "untitled_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block untitled/Get Autonomy Mode/Subscribe
extern SimulinkSubscriber<std_msgs::Bool, SL_Bus_untitled_std_msgs_Bool> Sub_untitled_22;

// For Block untitled/Get Mocap Pose/Subscribe
extern SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_untitled_geometry_msgs_PoseStamped> Sub_untitled_39;

// For Block untitled/Get Mocap Velocity/Subscribe
extern SimulinkSubscriber<geometry_msgs::TwistStamped, SL_Bus_untitled_geometry_msgs_TwistStamped> Sub_untitled_50;

// For Block untitled/Publish to Pi/Publish
extern SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_untitled_std_msgs_UInt16MultiArray> Pub_untitled_183;

void slros_node_init(int argc, char** argv);

#endif
