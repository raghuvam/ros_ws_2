cmake_minimum_required(VERSION 2.8.3)
project(kmscube_v0)

include(KMScube.txt)

## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  sensor_msgs
  std_msgs
  OpenCV
)

## System dependencies are found with CMake's conventions
#find_package(Boost REQUIRED COMPONENTS system)


catkin_package()


include_directories(include)
include_directories(${catkin_INCLUDE_DIRS})


## Declare a cpp library
#add_library(kmscube
#   src/kmscube.c )
add_library(esTransform src/esTransform.c)

add_library(kmscube src/kmscube.c)

## Declare a cpp executable


add_executable(kmscube_node src/kmscube_node.cpp)

target_link_libraries(kmscube_node kmscube esTransform ${KMSCUBE_DEPENDS_LIBS} ${catkin_LIBRARIES} ${GEN_DEPEND_LIBS})




