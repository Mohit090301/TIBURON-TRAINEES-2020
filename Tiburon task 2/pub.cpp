#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "N1");

  
  ros::NodeHandle n;

  
  ros::Publisher question_pub = n.advertise<std_msgs::String>("question", 1000);
  ros::Publisher answer_pub = n.advertise<std_msgs::Int32>("answer", 1000);
 ros::Rate loop_rate(0.5);

  

    while(ros::ok())
{
    
    std_msgs::String quest;
    std_msgs::Int32 ans;
    

    ROS_INFO("Name the longest river in the world\n ");
        
   
    quest.data = "Name the longest river in the world\n ";
    ans.data= 2;
   

   
    question_pub.publish(quest);
    answer_pub.publish(ans);
 loop_rate.sleep();  

    ros::spinOnce();
    
  }
   
  


  return 0;
}

 
