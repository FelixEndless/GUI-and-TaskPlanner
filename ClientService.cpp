int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_client");
  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;



ros::ServiceClient _subTaskVectorClient = _nh->serviceClient<youbot_msgs::pop_subTaskVector>("subTask");youbot_msgs::pop_subTaskVector 
srv;

if (_subTaskVectorClient.call(srv))
{  
//success the subtask vector is in:  
youbot_msgs::SubTaskVector subTasks = srv.response.subTasks; 
}
