#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "test_position_control2_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block test_position_control2/Get Mocap Position/Subscribe
extern SimulinkSubscriber<geometry_msgs::PoseStamped, SL_Bus_test_position_control2_geometry_msgs_PoseStamped> Sub_test_position_control2_15;

// For Block test_position_control2/Publish to Pi/Publish
extern SimulinkPublisher<std_msgs::UInt16MultiArray, SL_Bus_test_position_control2_std_msgs_UInt16MultiArray> Pub_test_position_control2_24;

void slros_node_init(int argc, char** argv);

#endif
