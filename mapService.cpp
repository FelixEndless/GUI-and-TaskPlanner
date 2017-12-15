#include <ros/ros.h>
//#include //hier einfügen
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <ros/service_traits.h>


//#include <youbot_msgs/pop_subTaskVectorRequest.h>
//#include <youbot_msgs/pop_subTaskVectorResponse.h>

#include <string>
#include <vector>
#include <youbot_msgs/pop_subTaskVector.h>

#include <youbot_msgs/SubTaskVector.h>
#include <std_msgs/Bool.h>

youbot_msgs::SubTaskVector subTasks;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_ros");
 

  ros::NodeHandle n, _nh;
  ros::Rate r(10);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);


  uint32_t shape = visualization_msgs::Marker::TEXT_VIEW_FACING;

  ros::ServiceClient _subTaskVectorClient = _nh.serviceClient<youbot_msgs::pop_subTaskVector>("subTask");
  youbot_msgs::pop_subTaskVector srv;
  while (ros::ok())
{
	visualization_msgs::Marker subTaskText;
    subTaskText.type = shape;
	subTaskText.header.frame_id = "/my_frame";
	subTaskText.header.stamp = ros::Time::now();
	subTaskText.ns = "test_ros";
	subTaskText.id = 0;
	subTaskText.type = shape;
	subTaskText.action = visualization_msgs::Marker::ADD;
	subTaskText.pose.position.x = 0.0;
	subTaskText.pose.position.y = 0.0;
	subTaskText.pose.position.z = 0.0;
	subTaskText.pose.orientation.x = 0.0;
	subTaskText.pose.orientation.y = 0.0;
	subTaskText.pose.orientation.z = 0.0;
	subTaskText.pose.orientation.w = 1.0;
	subTaskText.scale.x = 10;
	subTaskText.scale.y = 10;
	subTaskText.scale.z = 10;
	subTaskText.color.r = 1.0f;
	subTaskText.color.g = 1.0f;
	subTaskText.color.b = 1.0f;
	subTaskText.color.a = 1.0;
	subTaskText.lifetime =  ros::Duration();

	if (_subTaskVectorClient.call(srv))
	{
		//success the subtask vector is in:
		subTasks = srv.response.subTasks;
		ROS_INFO("I heard :[%s]", subTasks.subtasks.at(0).subTasktType.c_str());
		subTaskText.text = "This is a test";//subTasks.subtasks.at(0).subTasktType.c_str();

	}
	else
	{
		//ROS_ERROR("No Server found!");
	}
	marker_pub.publish(subTaskText);
	r.sleep();
}



  return 0;
}
