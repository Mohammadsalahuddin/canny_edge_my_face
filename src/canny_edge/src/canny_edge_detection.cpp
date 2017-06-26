#include <ros/ros.h>
#include <stdio.h>
#include <iostream>
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>     
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>
#include <cvaux.h>
#include <math.h>
#include <cxcore.h>
#include <highgui.h>
 

 
using namespace std;
using namespace cv;
namespace enc = sensor_msgs::image_encodings;
 
static const char WINDOW[] = "Image window";
 
class canny_edge_detection
{
	ros::NodeHandle nh_;
	ros::NodeHandle n;
 	ros::Publisher pub ;
  	image_transport::ImageTransport it_;    
  	image_transport::Subscriber image_sub_; //image subscriber 
  	image_transport::Publisher image_pub_; //image publisher(we subscribe to ardrone image_raw)
  	image_transport::Publisher image_pub_edge_;  
  	std_msgs::String msg;
public:
 	canny_edge_detection()
    	: it_(nh_)
  {
 
     	image_sub_ = it_.subscribe("/cv_camera_node/image_raw", 1, &canny_edge_detection::imageCb, this);
     	image_pub_= it_.advertise("/camera/image_processed",1);
     	image_pub_edge_= it_.advertise("/detection/canny_edge",1);
 
 
  }
 
  ~canny_edge_detection()
  {
    cv::destroyWindow(WINDOW);
  }


  void imageCb(const sensor_msgs::ImageConstPtr& original_image)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

      Mat out1;
      Mat gray_out;
      Mat canny_out;
      Mat gray_out1;
      Mat img1;

      cv::cvtColor(cv_ptr->image, gray_out, CV_BGR2GRAY);
      cv::GaussianBlur(gray_out, gray_out, Size(3, 3), 0, 0);
      cv::Canny(gray_out, canny_out, 50, 125, 3);
      cv::cvtColor(canny_out, gray_out1, CV_GRAY2BGR);

      cv::imshow( "CAMERA FEED", cv_ptr->image);
      // cv::imshow( "GRAY CAMERA", gray_out);
      // cv::imshow( "CANNY CAMERA", canny_out);
       cv::imshow( "CANNY EDGE DETECTION",gray_out1);
      cvWaitKey(2);
 
 	/// Create a Trackbar for user to enter threshold
  	//createTrackbar( "Min Threshold:", "Canny Edge Detection", &lowThreshold, max_lowThreshold, CannyThreshold );
     
      // publish the raw image 
	image_pub_.publish(cv_ptr->toImageMsg());

      // Publish the image from after edge detection
  	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", gray_out1).toImageMsg();
	image_pub_edge_.publish(msg);
 
}
};
 
 
 
int main(int argc, char** argv)
{
  ros::init(argc, argv, "canny_edge_detection");
  canny_edge_detection edge;
  ros::spin();
 
  return 0;
}
