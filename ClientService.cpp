//wir benötigen noch den header des Service File als #include

#include ros/ros.h
#include //hier einfügen

int main(int argc, char **argv)
{
  ros::init(argc, argv, "client_name");
 

  ros::NodeHandle n, _nh;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);



ros::ServiceClient _subTaskVectorClient = _nh->serviceClient<youbot_msgs::pop_subTaskVector>("subTask");youbot_msgs::pop_subTaskVector 
srv;

if (_subTaskVectorClient.call(srv))
{  
//success the subtask vector is in:  
youbot_msgs::SubTaskVector subTasks = srv.response.subTasks; 
}

    marker_pub.publish(marker);
  
