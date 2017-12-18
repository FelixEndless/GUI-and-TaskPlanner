#include "ros/ros.h"
#include "youbot_msgs/pop_subTaskVector.h"
#include <visualization_msgs/Marker.h>
#include<cstdlib>
#include<string>
#include<iostream>
int main(int argc, char**argv)
{
    ros::init(argc,argv,"client");
    ros::NodeHandle _nh;
    ros::ServiceClient _subTaskVectorClient = _nh.serviceClient<youbot_msgs::pop_subTaskVector>("subTask");
    float x,y,z;
    std::string message;
    std::ostringstream convert;
    ros::Rate r(30);
    youbot_msgs::pop_subTaskVector srv;
    ros:: NodeHandle n;
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker",10);
    visualization_msgs::Marker points;
    visualization_msgs::Marker *subTaskTextArr;
    int i = 0;
    while(ros::ok())
    {
    	visualization_msgs::Marker subTaskText;
    	subTaskText.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    	subTaskText.header.frame_id = "/map";
    	subTaskText.header.stamp = ros::Time::now();
    	subTaskText.ns = "client";
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
    	subTaskText.lifetime = ros::Duration();
		if (_subTaskVectorClient.call(srv))
		{
		  //success the subtask vector is in:
		  youbot_msgs::SubTaskVector subTasks = srv.response.subTasks;
		  int s=srv.response.subTasks.subtasks.size();

		  subTaskTextArr = new visualization_msgs::Marker[s];
		  while(i<s)
		  {
			  subTaskTextArr[i].type = visualization_msgs::Marker::TEXT_VIEW_FACING;
			  subTaskTextArr[i].header.frame_id = "/map";
			  subTaskTextArr[i].header.stamp = ros::Time::now();
			  subTaskTextArr[i].ns = "client";
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
			  //ROS_INFO("Nr. [%d] The X Position is: [%f]", i, srv.response.subTasks.subtasks.at(i).poseNew.position.x);
			  //ROS_INFO("Object Type: [%s]", srv.response.subTasks.subtasks.at(i).objectType.c_str());
			  marker_pub.publish(subTaskTextArr[i]);
			  i++;

		  }
		  points.header.frame_id = "/map";
		  points.header.stamp = ros::Time::now();
		  points.ns = "client";
		  points.pose.position.x = 0;
		  points.pose.position.y = 0;
		  points.pose.position.z = 0;
		  points.pose.orientation.x = 0.0;
		  points.pose.orientation.y = 0.0;
		  points.pose.orientation.z = 0.0;
		  points.pose.orientation.w = 1.0;
		  points.id = 0;
		  points.type = visualization_msgs::Marker::POINTS;
		  points.scale.x = 0.2;
		  points.scale.y = 0.2;
		  points.color.r = 0.0;
		  points.color.g = 1.0;
		  points.color.a = 1.0;
		  points.action = visualization_msgs::Marker::ADD;
			for(int i = 0; i< subTasks.subtasks.size();i++)
			{

				x = subTasks.subtasks.at(i).poseNew.position.x;
				y = subTasks.subtasks.at(i).poseNew.position.y;
				z = subTasks.subtasks.at(i).poseNew.position.z;
				geometry_msgs::Point p;
				p.x = x;
				p.y=y;
				p.z=z;
				points.points.push_back(p);
				message.append("x:");
				convert << p.x;
				message.append(convert.str());
				convert.str("");
				convert.clear();
				message.append(",y:");
				convert << p.y;
			    message.append(convert.str());
			    convert.str("");
			    convert.clear();
				message.append(",z:");
				convert << p.z;
				message.append(convert.str());
				convert.str("");
				convert.clear();
				std::cout << "output: " << message << std::endl;
				message = "";


			}

		  }
		else
		{

		}
		marker_pub.publish(points);
		r.sleep();
    }



    return 0;
}
