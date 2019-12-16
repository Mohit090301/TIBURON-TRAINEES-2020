#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<sstream>
#include<ros/ros.h>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
using namespace cv;
using std::cout;
int threshold_valueB = 0;
int threshold_valueG = 0;
int threshold_valueR = 0;
int num=3;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
Mat src, src_rgb, dst,rgb[3],rgb2[3];
const char* window_name = "Final Image";
const char* trackbar_valueB = "Blue";
const char* trackbar_valueG = "Green";
const char* trackbar_valueR = "Red";
void Threshold_DemoB( int, void* );
void Threshold_DemoG( int, void* );
void Threshold_DemoR( int, void* );
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{  cv::Mat frame;
  try
  { frame=cv_bridge::toCvShare(msg,"bgr8")->image;
    src=frame;
    
    cv::waitKey(1);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }

   
    split(src,rgb);
    rgb2[0]=rgb[0];
    rgb2[1]=rgb[1];
    rgb2[2]=rgb[2];
 
    dst=Mat::zeros(src.rows,src.cols,CV_8UC1);
   while(true)
	{
    createTrackbar( trackbar_valueB,
                    window_name, &threshold_valueB,
                    max_value, Threshold_DemoB ); // Create a Trackbar to choose Threshold value
     createTrackbar( trackbar_valueG,
                    window_name, &threshold_valueG,
                    max_value, Threshold_DemoG); // Create a Trackbar to choose Threshold value
    createTrackbar( trackbar_valueR,
                    window_name, &threshold_valueR,
                    max_value, Threshold_DemoR ); // Create a Trackbar to choose Threshold value
       
        cvtColor( src, src_rgb, COLOR_BGR2RGB ); // Convert the image to Gray
        Threshold_DemoB(0,0);
        Threshold_DemoG(0,0);
	Threshold_DemoR(0,0);
              cv::merge(rgb2,num,dst);
	       imshow(window_name,dst);
          int key=waitKey(30);
		if(key==27)break;
	} 
}
		
  

void Threshold_DemoB( int, void* )
{
        threshold(rgb[2],rgb2[2],threshold_valueB,max_binary_value,threshold_type);
	
}
void Threshold_DemoG( int, void* )
{
        threshold(rgb[1],rgb2[1],threshold_valueG,max_binary_value,threshold_type);
	//cv::merge(rgb2,num,dst);
	//imshow(window_name,dst);
}
void Threshold_DemoR( int, void* )
{
        threshold(rgb[0],rgb2[0],threshold_valueR,max_binary_value,threshold_type);
//	cv::merge(rgb2,num,dst);
	//imshow(window_name,dst);
}



int main( int argc, char** argv )
{     ros::init(argc, argv, "rgb_threshhold");
  ros::NodeHandle nh;
  cv::namedWindow("view2");
 
   cv::namedWindow(window_name);
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/image1", 1, imageCallback);

 // Call the function to initialize
  //  waitKey();
      ros::spin();
     //destroyWindow("view2");
    return 0;
}
