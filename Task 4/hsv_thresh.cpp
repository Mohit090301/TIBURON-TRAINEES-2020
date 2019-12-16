#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<sstream>
#include<iostream>
using namespace cv;
const int max_value_H = 360/2;
const int max_value = 255;
const String window_capture_name = "Image";
const String window_detection_name = "Object Detection";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;


static void on_low_H_thresh_trackbar(int, void *)
{
    low_H = min(high_H-1, low_H);
    setTrackbarPos("Low H", window_detection_name, low_H);
}
static void on_high_H_thresh_trackbar(int, void *)
{
    high_H = max(high_H, low_H+1);
    setTrackbarPos("High H", window_detection_name, high_H);
}
static void on_low_S_thresh_trackbar(int, void *)
{
    low_S = min(high_S-1, low_S);
    setTrackbarPos("Low S", window_detection_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void *)
{
    high_S = max(high_S, low_S+1);
    setTrackbarPos("High S", window_detection_name, high_S);
}
static void on_low_V_thresh_trackbar(int, void *)
{
    low_V = min(high_V-1, low_V);
    setTrackbarPos("Low V", window_detection_name, low_V);
}
static void on_high_V_thresh_trackbar(int, void *)
{
    high_V = max(high_V, low_V+1);
    setTrackbarPos("High V", window_detection_name, high_V);
}
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{  cv::Mat src;
  try
  { src=cv_bridge::toCvShare(msg,"bgr8")->image;
  
    cv::imshow("view2",src);
    cv::waitKey(30);
    
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
   createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
    Mat frame, frame_HSV, frame_threshold;
     frame=src;

   while(true)
{      
        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
       
        inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
       
        imshow(window_detection_name, frame_threshold); int key=waitKey(30);
        if(key==27)
        break;
}}
int main(int argc, char* argv[])
{   ros::init(argc, argv, "hsv_threshhold");
    ros::NodeHandle nh;
    
    namedWindow(window_capture_name);
    namedWindow(window_detection_name);
    startWindowThread();
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("camera/image2", 1, imageCallback);
   
    
     
  
     ros::spin();
     destroyWindow("view2");
    return 0;
}
