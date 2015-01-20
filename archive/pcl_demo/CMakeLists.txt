cmake_minimum_required(VERSION 2.8.3)
project(pcl_demo)

include(crosscompile.txt)

find_package(catkin REQUIRED COMPONENTS
  OpenCV
  roscpp
  std_msgs
  pcl_ros
)

#find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcl_demo_node pcl_demo_node.cpp)
target_link_libraries (pcl_demo_node ${PCL_LIBRARIES} ${catkin_LIBRARIES} ${GEN_DEPEND_LIBS})
