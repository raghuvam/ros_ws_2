#catkin_make_isolated --pkg hello_world --install --install-space ~/ubuntu_arm/rootfs/opt/ros/hydro -DCMAKE_TOOLCHAIN_FILE=/home/x0221391/ws_arm/rostoolchain_vision.cmake -DCMAKE_VERBOSE_MAKEFILE=true > log 2>&1

catkin_make -DCMAKE_TOOLCHAIN_FILE=/home/x0221391/ws_arm/rostoolchain_vision.cmake -DCMAKE_VERBOSE_MAKEFILE=true > log 2>&1

# --install  --install-space ~/cardimage_copy/rootfs/usr/share/ros/hydro

