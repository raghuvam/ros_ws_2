cmake_minimum_required(VERSION 2.8.3)
project(capture_display)

include(crosscompile.txt)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  OpenCV
  roscpp
  sensor_msgs
  std_msgs
)

find_package(OpenCV REQUIRED)
MESSAGE(STATUS "opencv libs :  ${OpenCV_LIBRARIES} " )

catkin_package()

###########
## Build ##
###########
include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_library(demux src/demux.c)
add_library(util src/util.c)
add_library(v4l2 src/v4l2.c)
add_library(display-kms src/display-kms.c)
add_library(display-kmscube src/display-kmscube.c)
add_library(display-x11 src/display-x11.c)
add_library(esTransform src/esTransform.c)

## Declare a cpp executable
#add_executable(capture_display_node src/capture_display_node.cpp)

#add_library(dmabuftest src/dmabuftest.c)

#add_library(cv_link src/cv_link.c)

#add_library(buftest src/dmabuftest.c)
#add_executable(capture_display_node src/capture_display_node.cpp)

#add_executable(buftest src/dmabuftest.c)

#add_library(get_image src/get_image.cpp)

add_executable(main src/main.cpp src/dmabuftest.c)
#target_link_libraries(cv_link  ${OpenCV_LIBRARIES})

# add_dependencies(capture_display_node capture_display_generate_messages_cpp)

## Specify libraries to link a library or executable target against
#target_link_libraries(capture_display_node ${catkin_LIBRARIES}) buftest display-x11

target_link_libraries(main demux util display-kms display-kmscube esTransform v4l2)

target_link_libraries(main ${KMSCUBE_DEPENDS_LIBS} ${catkin_LIBRARIES} ${GEN_DEPEND_LIBS})





