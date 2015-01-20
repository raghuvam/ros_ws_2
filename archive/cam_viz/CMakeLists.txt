cmake_minimum_required(VERSION 2.8.3)
project(cam_viz)

include(crosscompile.txt)
find_package(catkin REQUIRED COMPONENTS
  OpenCV
  message_generation
  roscpp
  sensor_msgs
  std_msgs
)

catkin_package()

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(cam_viz_node src/cam_viz_node.cpp)

target_link_libraries(cam_viz_node  ${catkin_LIBRARIES} ${GEN_DEPEND_LIBS})


