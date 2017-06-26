cmake_minimum_required(VERSION 2.8.3)
project(canny_edge)

find_package(catkin REQUIRED COMPONENTS cv_bridge image_transport roscpp sensor_msgs std_msgs message_generation)
find_package(OpenCV 2 REQUIRED)

#add_message_files(
#  FILES
#)

generate_messages(
  DEPENDENCIES
  canny_edge
)


include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

catkin_package(
#   INCLUDE_DIRS include
#  LIBRARIES canny_edge
#  CATKIN_DEPENDS cv_bridge image_transport opencv2 roscpp sensor_msgs std_msgs message_runtime
#  DEPENDS system_lib
   CATKIN_DEPENDS message_runtime
)

add_executable(canny_edge_detection src/canny_edge_detection.cpp)
target_link_libraries(canny_edge_detection ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )
