# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/x0221391/new_ws_arm/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/x0221391/new_ws_arm/build

# Include any dependencies generated for this target.
include cube_display/CMakeFiles/demux.dir/depend.make

# Include the progress variables for this target.
include cube_display/CMakeFiles/demux.dir/progress.make

# Include the compile flags for this target's objects.
include cube_display/CMakeFiles/demux.dir/flags.make

cube_display/CMakeFiles/demux.dir/src/demux.c.o: cube_display/CMakeFiles/demux.dir/flags.make
cube_display/CMakeFiles/demux.dir/src/demux.c.o: /home/x0221391/new_ws_arm/src/cube_display/src/demux.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/x0221391/new_ws_arm/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cube_display/CMakeFiles/demux.dir/src/demux.c.o"
	cd /home/x0221391/new_ws_arm/build/cube_display && /usr/bin/arm-linux-gnueabihf-gcc-4.6  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/demux.dir/src/demux.c.o   -c /home/x0221391/new_ws_arm/src/cube_display/src/demux.c

cube_display/CMakeFiles/demux.dir/src/demux.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/demux.dir/src/demux.c.i"
	cd /home/x0221391/new_ws_arm/build/cube_display && /usr/bin/arm-linux-gnueabihf-gcc-4.6  $(C_DEFINES) $(C_FLAGS) -E /home/x0221391/new_ws_arm/src/cube_display/src/demux.c > CMakeFiles/demux.dir/src/demux.c.i

cube_display/CMakeFiles/demux.dir/src/demux.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/demux.dir/src/demux.c.s"
	cd /home/x0221391/new_ws_arm/build/cube_display && /usr/bin/arm-linux-gnueabihf-gcc-4.6  $(C_DEFINES) $(C_FLAGS) -S /home/x0221391/new_ws_arm/src/cube_display/src/demux.c -o CMakeFiles/demux.dir/src/demux.c.s

cube_display/CMakeFiles/demux.dir/src/demux.c.o.requires:
.PHONY : cube_display/CMakeFiles/demux.dir/src/demux.c.o.requires

cube_display/CMakeFiles/demux.dir/src/demux.c.o.provides: cube_display/CMakeFiles/demux.dir/src/demux.c.o.requires
	$(MAKE) -f cube_display/CMakeFiles/demux.dir/build.make cube_display/CMakeFiles/demux.dir/src/demux.c.o.provides.build
.PHONY : cube_display/CMakeFiles/demux.dir/src/demux.c.o.provides

cube_display/CMakeFiles/demux.dir/src/demux.c.o.provides.build: cube_display/CMakeFiles/demux.dir/src/demux.c.o

# Object files for target demux
demux_OBJECTS = \
"CMakeFiles/demux.dir/src/demux.c.o"

# External object files for target demux
demux_EXTERNAL_OBJECTS =

/home/x0221391/new_ws_arm/devel/lib/libdemux.so: cube_display/CMakeFiles/demux.dir/src/demux.c.o
/home/x0221391/new_ws_arm/devel/lib/libdemux.so: cube_display/CMakeFiles/demux.dir/build.make
/home/x0221391/new_ws_arm/devel/lib/libdemux.so: cube_display/CMakeFiles/demux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library /home/x0221391/new_ws_arm/devel/lib/libdemux.so"
	cd /home/x0221391/new_ws_arm/build/cube_display && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cube_display/CMakeFiles/demux.dir/build: /home/x0221391/new_ws_arm/devel/lib/libdemux.so
.PHONY : cube_display/CMakeFiles/demux.dir/build

cube_display/CMakeFiles/demux.dir/requires: cube_display/CMakeFiles/demux.dir/src/demux.c.o.requires
.PHONY : cube_display/CMakeFiles/demux.dir/requires

cube_display/CMakeFiles/demux.dir/clean:
	cd /home/x0221391/new_ws_arm/build/cube_display && $(CMAKE_COMMAND) -P CMakeFiles/demux.dir/cmake_clean.cmake
.PHONY : cube_display/CMakeFiles/demux.dir/clean

cube_display/CMakeFiles/demux.dir/depend:
	cd /home/x0221391/new_ws_arm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/x0221391/new_ws_arm/src /home/x0221391/new_ws_arm/src/cube_display /home/x0221391/new_ws_arm/build /home/x0221391/new_ws_arm/build/cube_display /home/x0221391/new_ws_arm/build/cube_display/CMakeFiles/demux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cube_display/CMakeFiles/demux.dir/depend
