# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

# Declare the name of the CMake Project
project(video_streamer)


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


add_executable(video_streamer src/video_streamer.cpp)

target_link_libraries(video_streamer  ${catkin_LIBRARIES} ${GEN_DEPEND_LIBS})

