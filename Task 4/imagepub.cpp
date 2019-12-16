#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> 
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>

int main(int argc, char** argv)
{
    

   cv::namedWindow("view");
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
 image_transport::Publisher pub1=it.advertise("camera/image1",1);
image_transport::Publisher pub2=it.advertise("camera/image2",1);
 
  // int ch= cv::waitKey(10);

 
  cv::VideoCapture cap(0);
 
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(50);
  while (nh.ok()) {
    cap >> frame;
     cv::imshow("view", frame);
     int ch= cv::waitKey(10);
     
     if(ch=='p')  
   {
      msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",frame).toImageMsg();
     pub1.publish(msg);
     pub2.publish(msg);
     cv::waitKey(1);
    }

    ros::spinOnce();
    loop_rate.sleep();
    
  }
 cv::destroyWindow("view");
}
