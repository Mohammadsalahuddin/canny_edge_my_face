cmake_minimum_required(VERSION 2.8.3)
project(face_detection)

find_package(catkin REQUIRED COMPONENTS cv_bridge image_transport roscpp sensor_msgs std_msgs message_generation)
find_package(OpenCV 2 REQUIRED)

#add_message_files(
#  FILES
#)

generate_messages(
  DEPENDENCIES
  face_detection
)


include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

catkin_package(
#   INCLUDE_DIRS include
#  LIBRARIES face_detection
#  CATKIN_DEPENDS cv_bridge image_transport opencv2 roscpp sensor_msgs std_msgs message_runtime
#  DEPENDS system_lib
   CATKIN_DEPENDS message_runtime
)

add_executable(face_detection src/face_detection.cpp)
target_link_libraries(face_detection ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )
