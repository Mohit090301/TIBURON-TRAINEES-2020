#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <sstream>
int ans;
void result(const std_msgs::Int32::ConstPtr& a)
{
    ans = a->data;
 
}
void checking(const std_msgs::Int32::ConstPtr& a1)
{
 if(a1->data==ans)
 ROS_INFO("Congratulations!!Your answer is correct\n");
 else
 ROS_INFO("Sorry,wrong answer");
}
	
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "N3");
  ros::NodeHandle n;
  ros::Subscriber sub1 = n.subscribe("ans", 1000,result);
  ros::Subscriber sub2 = n.subscribe("answer", 1000, checking);
  ros::spin();
  return 0;
}

