# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/2-stick-to-ground.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/2-stick-to-ground.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2-stick-to-ground.dir/flags.make

CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.obj: CMakeFiles/2-stick-to-ground.dir/flags.make
CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.obj: CMakeFiles/2-stick-to-ground.dir/includes_CXX.rsp
CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.obj: ../2-stick-to-ground.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\2-stick-to-ground.dir\2-stick-to-ground.cpp.obj -c "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\2-stick-to-ground.cpp"

CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\2-stick-to-ground.cpp" > CMakeFiles\2-stick-to-ground.dir\2-stick-to-ground.cpp.i

CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\2-stick-to-ground.cpp" -o CMakeFiles\2-stick-to-ground.dir\2-stick-to-ground.cpp.s

# Object files for target 2-stick-to-ground
2__stick__to__ground_OBJECTS = \
"CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.obj"

# External object files for target 2-stick-to-ground
2__stick__to__ground_EXTERNAL_OBJECTS =

2-stick-to-ground.exe: CMakeFiles/2-stick-to-ground.dir/2-stick-to-ground.cpp.obj
2-stick-to-ground.exe: CMakeFiles/2-stick-to-ground.dir/build.make
2-stick-to-ground.exe: CMakeFiles/2-stick-to-ground.dir/linklibs.rsp
2-stick-to-ground.exe: CMakeFiles/2-stick-to-ground.dir/objects1.rsp
2-stick-to-ground.exe: CMakeFiles/2-stick-to-ground.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2-stick-to-ground.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\2-stick-to-ground.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2-stick-to-ground.dir/build: 2-stick-to-ground.exe
.PHONY : CMakeFiles/2-stick-to-ground.dir/build

CMakeFiles/2-stick-to-ground.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\2-stick-to-ground.dir\cmake_clean.cmake
.PHONY : CMakeFiles/2-stick-to-ground.dir/clean

CMakeFiles/2-stick-to-ground.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug\CMakeFiles\2-stick-to-ground.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/2-stick-to-ground.dir/depend

