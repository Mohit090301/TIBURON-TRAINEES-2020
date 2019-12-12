#include "ros/ros.h"
#include "std_msgs/Int32.h"
ros::Publisher ch2_pubsub;
void ch1Callback(const std_msgs::Int32::ConstPtr& msg)
{
   
    std_msgs::Int32 msg2;
	msg2.data=msg->data*msg->data;
    ROS_INFO("I sent: %d", msg2.data);
   ch2_pubsub.publish(msg2); 
}
int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "N2");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("ch1", 1000, ch1Callback);
  ch2_pubsub = n.advertise<std_msgs::Int32>("ch2", 1000);
  ros::spin();
  return 0;
}
