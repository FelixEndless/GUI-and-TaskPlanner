#include <ros/ros.h>
//#include //hier einfügen
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <ros/service_traits.h>
#include <interactive_markers/interactive_marker_server.h>
#include <sstream>

using namespace visualization_msgs;


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

  ros::ServiceClient _subTaskVectorClient = _nh.serviceClient<youbot_msgs::pop_subTaskVector>("subTask");
  youbot_msgs::pop_subTaskVector srv;
  while (ros::ok())
{

	visualization_msgs::Marker subTaskText;
    subTaskText.type = Marker::TEXT_VIEW_FACING;
	subTaskText.header.frame_id = "/map";
	subTaskText.header.stamp = ros::Time::now();
	subTaskText.ns = "test_ros";
	subTaskText.id = 0;
	subTaskText.action = visualization_msgs::Marker::ADD;
	subTaskText.pose.position.x = 0.0;
	subTaskText.pose.position.y = 0.0;
	subTaskText.pose.position.z = 1.0;
	subTaskText.pose.orientation.x = 0.0;
	subTaskText.pose.orientation.y = 0.0;
	subTaskText.pose.orientation.z = 0.0;
	subTaskText.pose.orientation.w = 1.0;
	subTaskText.scale.x = 0.5;
	subTaskText.scale.y = 0.5;
	subTaskText.scale.z = 0.5;
	subTaskText.color.r = 1.0f;
	subTaskText.color.g = 1.0f;
	subTaskText.color.b = 1.0f;
	subTaskText.color.a = 1.0;
	subTaskText.lifetime =  ros::Duration();

	if (_subTaskVectorClient.call(srv))
	{
		//success the subtask vector is in:
		subTasks = srv.response.subTasks;
		 int s=srv.response.subTasks.subtasks.size();
		 visualization_msgs::Marker *subTaskTextArr;
		 subTaskTextArr = new visualization_msgs::Marker[s];

		 for(int i=0;i<s;i++)
		 	   {

			  subTaskTextArr[i].type = Marker::TEXT_VIEW_FACING;
			  subTaskTextArr[i].header.frame_id = "/map";
			  subTaskTextArr[i].header.stamp = ros::Time::now();
			  subTaskTextArr[i].ns = "test_ros";
			  subTaskTextArr[i].id = i;
			  subTaskTextArr[i].action = visualization_msgs::Marker::ADD;
			  subTaskTextArr[i].pose.position.x = subTasks.subtasks.at(i).poseNew.position.x;
			  subTaskTextArr[i].pose.position.y = subTasks.subtasks.at(i).poseNew.position.y;
			  subTaskTextArr[i].pose.position.z = subTasks.subtasks.at(i).poseNew.position.z+0.4;
			  for(int j=0;j<i;j++)
			  {

				  if(subTaskTextArr[i].pose.position.x==subTaskTextArr[j].pose.position.x && subTaskTextArr[i].pose.position.y==subTaskTextArr[j].pose.position.y)
				  {
					  //ROS_INFO("i=[%d], j=[%d]", i, j);
					  subTaskTextArr[i].pose.position.z = subTaskTextArr[i].pose.position.z+0.15;
				  }
			  }

			  subTaskTextArr[i].pose.orientation.x = 0.0;
			  subTaskTextArr[i].pose.orientation.y = 0.0;
			  subTaskTextArr[i].pose.orientation.z = 0.0;
			  subTaskTextArr[i].pose.orientation.w = 1.0;
			  subTaskTextArr[i].scale.x = 0.2;
			  subTaskTextArr[i].scale.y = 0.2;
			  subTaskTextArr[i].scale.z = 0.2;
			  subTaskTextArr[i].color.r = 1.0f;
			  subTaskTextArr[i].color.g = 1.0f;
			  subTaskTextArr[i].color.b = 1.0f;
			  subTaskTextArr[i].color.a = 1.0;
			  subTaskTextArr[i].lifetime =  ros::Duration();
			  std::ostringstream ss;
			  ss << i;

			  subTaskTextArr[i].text = ss.str() + std::string(". ") + subTasks.subtasks.at(i).subTasktType.c_str() + std::string(" ") + subTasks.subtasks.at(i).objectType.c_str();

		 	  ROS_INFO("Nr. [%d] The X Position is: [%f]", i, srv.response.subTasks.subtasks.at(i).poseNew.position.x);
		 	  //ROS_INFO("Object Type: [%s]", srv.response.subTasks.subtasks.at(i).objectType.c_str());
		 	  marker_pub.publish(subTaskTextArr[i]);


		 }

		//subTaskText.text = subTasks.subtasks.at(0).subTasktType.c_str();
		//ROS_INFO("I heard :[%s]", subTaskText.text.c_str());
		//marker_pub.publish(subTaskText);
	}
	else
	{
		//ROS_ERROR("No Server found!");
	}

	r.sleep();
}



  return 0;
}
