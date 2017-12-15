#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <youbot_msgs/pop_subTaskVector.h>
#include <turtlesim/Pose.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ClientService");


  ros::NodeHandle n, _nh;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);



  ros::ServiceClient _subTaskVectorClient = _nh.serviceClient<youbot_msgs::pop_subTaskVector>("subTask");

  youbot_msgs::pop_subTaskVector srv;

  while (ros::ok())
    {





	   int i=0;

	   //for(i=0; i<=0; i++)


  if(!_subTaskVectorClient.call(srv))

  {

  }
	// ROS_ERROR("could not call the service...")


  else
  {
	  int s=srv.response.subTasks.subtasks.size();
	  while(i<s)
	  {

	  ROS_INFO("Nr. [%d] The X Position is: [%f]", i, srv.response.subTasks.subtasks.at(i).poseNew.position.x);
	  ROS_INFO("Object Type: [%s]", srv.response.subTasks.subtasks.at(i).objectType.c_str());

	  i++;
	  }
	  }



    }

if (_subTaskVectorClient.call(srv))
{
//success the subtask vector is in:

youbot_msgs::SubTaskVector subTasks = srv.response.subTasks;

}

  //marker_pub.publish(marker);

}
