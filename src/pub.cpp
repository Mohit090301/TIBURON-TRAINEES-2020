#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <sstream>
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "N1");

  
  ros::NodeHandle n;

  ros::Publisher ch1_pub = n.advertise<std_msgs::Int32>("ch1", 1000);

  ros::Rate loop_rate(0.5);

  
  int count = 1;
  while (ros::ok())
  {
    
    std_msgs::Int32 msg;
	msg.data=count;
    ROS_INFO("sent: %d", msg.data);
    ch1_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    count++;
   
  }
  return 0;
}
 
