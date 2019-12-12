#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <sstream>
void ch1Callback(const std_msgs::Int32::ConstPtr& msg2)
{

 ROS_INFO("I received %d",msg2->data);
}
	
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "N3");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("ch2", 1000, ch1Callback);
  ros::spin();
  return 0;
}
