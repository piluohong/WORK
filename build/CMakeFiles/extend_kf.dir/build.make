# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/h/hong.MD.degree/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/h/hong.MD.degree/test/build

# Include any dependencies generated for this target.
include CMakeFiles/extend_kf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/extend_kf.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/extend_kf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/extend_kf.dir/flags.make

CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o: CMakeFiles/extend_kf.dir/flags.make
CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o: /home/h/hong.MD.degree/test/src/extend_kf.cpp
CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o: CMakeFiles/extend_kf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/h/hong.MD.degree/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o -MF CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o.d -o CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o -c /home/h/hong.MD.degree/test/src/extend_kf.cpp

CMakeFiles/extend_kf.dir/src/extend_kf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/extend_kf.dir/src/extend_kf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/h/hong.MD.degree/test/src/extend_kf.cpp > CMakeFiles/extend_kf.dir/src/extend_kf.cpp.i

CMakeFiles/extend_kf.dir/src/extend_kf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/extend_kf.dir/src/extend_kf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/h/hong.MD.degree/test/src/extend_kf.cpp -o CMakeFiles/extend_kf.dir/src/extend_kf.cpp.s

# Object files for target extend_kf
extend_kf_OBJECTS = \
"CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o"

# External object files for target extend_kf
extend_kf_EXTERNAL_OBJECTS =

extend_kf: CMakeFiles/extend_kf.dir/src/extend_kf.cpp.o
extend_kf: CMakeFiles/extend_kf.dir/build.make
extend_kf: /usr/lib/x86_64-linux-gnu/libpython3.6m.so
extend_kf: CMakeFiles/extend_kf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/h/hong.MD.degree/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable extend_kf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/extend_kf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/extend_kf.dir/build: extend_kf
.PHONY : CMakeFiles/extend_kf.dir/build

CMakeFiles/extend_kf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/extend_kf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/extend_kf.dir/clean

CMakeFiles/extend_kf.dir/depend:
	cd /home/h/hong.MD.degree/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/h/hong.MD.degree/test /home/h/hong.MD.degree/test /home/h/hong.MD.degree/test/build /home/h/hong.MD.degree/test/build /home/h/hong.MD.degree/test/build/CMakeFiles/extend_kf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/extend_kf.dir/depend

