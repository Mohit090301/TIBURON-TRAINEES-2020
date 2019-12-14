#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>




image_transport::Publisher sub;
 

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{ 
  try
  {   
     cv::Mat img=cv_bridge::toCvShare(msg, "bgr8")->image;
       cv::imshow("view", img);
   int ch= cv::waitKey(10);
     
     if(ch=='p')  
     {     
    
     sub.publish(msg);
     }
     else if(ch=='s')
     cv::imwrite("saved.jpg",img);
        
  
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "video_listener");
   ros::NodeHandle nh;
  
image_transport::ImageTransport it(nh);
  sub = it.advertise("camera/image2", 1);
  cv::namedWindow("view");
  cv::startWindowThread();
  ROS_INFO("Enter s for saving the frame and p for transferring the frame to another node\n");
  

  
  image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);
  ros::spin();
  cv::destroyWindow("view");
}
