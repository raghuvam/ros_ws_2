include(Crosscompile.txt)

cmake_minimum_required(VERSION 2.8)
project(hello_world)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(include)
include_directories( ${catkin_INCLUDE_DIRS})



## Declare a cpp executable
add_executable(hello_world_node src/hello_world.cpp)


target_link_libraries(hello_world_node ${catkin_LIBRARIES} ${GEN_DEPEND_LIBS})
