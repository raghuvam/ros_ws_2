# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

# Declare the name of the CMake Project
project(cam_streamer_v01)


# Find Catkin
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs sensor_msgs image_transport cv_bridge)
find_package(OpenCV)

# Declare this project as a catkin package
catkin_package()

## include vision SDK 
include(Crosscompile.txt)
include(VisionSDK.txt)

# Add the headers from roscpp
include_directories(${catkin_INCLUDE_DIRS})
include_directories(include)


add_library(streamerlink_v01 src/streamerlink_v01.c)

add_executable(cam_streamer_v01 src/cam_capture_v01.cpp)

target_link_libraries(cam_streamer_v01 streamerlink_v01 ${VisionSDK_LIBRARIES} ${VisionSDK_DEPEND_LIBS} ${catkin_LIBRARIES} ${GEN_DEPEND_LIBS} )

