// ROS Node for Face detection
// author: Uddin
// uddin@dis.uniroma1.it
// build from opencv face detection sample



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
 
class face_detection
{
	ros::NodeHandle nh_;
	ros::NodeHandle n;
 	ros::Publisher pub ;
  	image_transport::ImageTransport it_;    
  	image_transport::Subscriber image_sub_; 
  	image_transport::Publisher image_pub_; 
  	image_transport::Publisher image_pub_face_;  
  	std_msgs::String msg;
	CascadeClassifier face_cascade;

public:
 	face_detection()
    	: it_(nh_)
  {
 	// The input stream
     	image_sub_ = it_.subscribe("/cv_camera_node/image_raw", 1, &face_detection::imageCb, this);
	// ros publisher for output stream
     	image_pub_face_= it_.advertise("/detection/face",1); 
      
	//Load the cascades (please provide the correct cascade location)
	if( !face_cascade.load( "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml" ) ) printf("--(!)Error loading face cascade\n");
	else printf("Wow! I found the face cascade\n");
 
 
  }
 
  ~face_detection()
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
	
	// code for face detection 
	Mat gray_out;
	Mat face_img;
	vector<cv::Rect> faces;
	Rect rect;
	
	cvtColor(cv_ptr->image, gray_out, CV_BGR2GRAY);
	equalizeHist( gray_out, gray_out);

      // Detect faces
       face_cascade.detectMultiScale( gray_out, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

/*
    // Draw circles on the detected faces
    for( int i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( gray_out, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    }
*/

    // Draw rectangle on the detected faces
    for( int i = 0; i < faces.size(); i++ )
    {
   	rectangle( cv_ptr->image, cvPoint(faces[i].x, faces[i].y), cvPoint(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(255,0,255),4,8,0);
	rect.x = faces[i].x ;
	rect.y = faces[i].y;
	rect.width = faces[i].width;
	rect.height = faces[i].height;
	face_img = cv_ptr->image(rect);
    }




	// Dispaly the video
	imshow( "CAMERA FEED", cv_ptr->image);
	//cv::imshow( "FACE DETECTION",gray_out);
	if (!face_img.empty())
	imshow( "FACE DETECTION",face_img);
	cvWaitKey(2);
 

      // Publish the face image ROS publisher 
	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8",face_img ).toImageMsg();
	image_pub_face_.publish(msg);
}
};
 
 
 
int main(int argc, char** argv)
{
  ros::init(argc, argv, "face_detection");
  face_detection face;
  ros::spin();
 
  return 0;
}
