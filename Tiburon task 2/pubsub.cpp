#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"

ros::Publisher myans_pubsub;
void take(const std_msgs::String quest)
{
    ROS_INFO("The question is :-%s\n" ,quest.data.c_str());
    ROS_INFO("1-River Ganga    2-River Nile    3-River Amazon    4-River Niger\n") ;
    std_msgs::Int32 a;	
    std::cin>>a.data;
	
    ROS_INFO("My answer is %d",a.data);
    myans_pubsub.publish(a); 
}
int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "N2");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("question", 1000, take);
  myans_pubsub = n.advertise<std_msgs::Int32>("ans", 1000);
  ros::spin();
  return 0;
}
