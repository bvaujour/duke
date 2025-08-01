# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/injah/codes/soundTest/raylib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/injah/codes/soundTest/raylib/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/models_bone_socket.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/models_bone_socket.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/models_bone_socket.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/models_bone_socket.dir/flags.make

examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o: examples/CMakeFiles/models_bone_socket.dir/flags.make
examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o: /home/injah/codes/soundTest/raylib/examples/models/models_bone_socket.c
examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o: examples/CMakeFiles/models_bone_socket.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/injah/codes/soundTest/raylib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o"
	cd /home/injah/codes/soundTest/raylib/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o -MF CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o.d -o CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o -c /home/injah/codes/soundTest/raylib/examples/models/models_bone_socket.c

examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.i"
	cd /home/injah/codes/soundTest/raylib/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/injah/codes/soundTest/raylib/examples/models/models_bone_socket.c > CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.i

examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.s"
	cd /home/injah/codes/soundTest/raylib/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/injah/codes/soundTest/raylib/examples/models/models_bone_socket.c -o CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.s

# Object files for target models_bone_socket
models_bone_socket_OBJECTS = \
"CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o"

# External object files for target models_bone_socket
models_bone_socket_EXTERNAL_OBJECTS =

examples/models_bone_socket: examples/CMakeFiles/models_bone_socket.dir/models/models_bone_socket.c.o
examples/models_bone_socket: examples/CMakeFiles/models_bone_socket.dir/build.make
examples/models_bone_socket: raylib/libraylib.a
examples/models_bone_socket: /usr/lib/x86_64-linux-gnu/libOpenGL.so
examples/models_bone_socket: /usr/lib/x86_64-linux-gnu/libGLX.so
examples/models_bone_socket: /usr/lib/x86_64-linux-gnu/librt.a
examples/models_bone_socket: /usr/lib/x86_64-linux-gnu/libm.so
examples/models_bone_socket: examples/CMakeFiles/models_bone_socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/injah/codes/soundTest/raylib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable models_bone_socket"
	cd /home/injah/codes/soundTest/raylib/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/models_bone_socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/models_bone_socket.dir/build: examples/models_bone_socket
.PHONY : examples/CMakeFiles/models_bone_socket.dir/build

examples/CMakeFiles/models_bone_socket.dir/clean:
	cd /home/injah/codes/soundTest/raylib/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/models_bone_socket.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/models_bone_socket.dir/clean

examples/CMakeFiles/models_bone_socket.dir/depend:
	cd /home/injah/codes/soundTest/raylib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/injah/codes/soundTest/raylib /home/injah/codes/soundTest/raylib/examples /home/injah/codes/soundTest/raylib/build /home/injah/codes/soundTest/raylib/build/examples /home/injah/codes/soundTest/raylib/build/examples/CMakeFiles/models_bone_socket.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : examples/CMakeFiles/models_bone_socket.dir/depend

