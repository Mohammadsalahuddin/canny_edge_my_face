# How To use this package #

Canny Edge Detector (on my face). This package take 

### What is this repository for? ###

* opencv face detection pkg
* canny edge detector pkg
* cv_camera pkg (from ros)

### How do I get set up? ###

* Tasted with ROS indigo 
* OpenCV 3.0 (mandatory)
* The location of Haar Cascades file must in "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml" or you may change it from  face_detection.cpp file.
* It published the output on (/detection/canny_edge), the canny edge detector.
* A web cam is mandatory.

### How to run tests ###

* Clone the repository on a catkin_workspace
* catkin_make
* source devel/setup.bash
* roslaunch 

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact
