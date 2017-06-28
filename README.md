# How To use this package #

Canny Edge Detector (on my face). This package take 

### What is this repository for? ###

* opencv face detection pkg
* canny edge detector pkg
* cv_camera pkg (from ros)

### How do I get set up? ###

* Operating system : Ubuntu 14.04 (64 bit)
* Tasted with ROS Indigo 
* OpenCV 3.0 (mandatory)
* The location of Haar Cascades file must in "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml" or you may change it from  face_detection.cpp file.
* It published the output on (/detection/canny_edge), the canny edge detector.
* A web cam is mandatory.

### How to run tests ###

* Clone the workspace
* inside the workspace run: catkin_make
* source devel/setup.bash
* roslaunch canny_edge canny_edge_detector.launch
* If everything is okay then you will see there image window on your screen.(check the sample screenshot.png)
* You can also use rqt for visualization
* cheers

### Contact information ###

* Mohammad Salah Uddin
* uddin@dis.uniroma1.it
* akash.bangla@gmail.com
