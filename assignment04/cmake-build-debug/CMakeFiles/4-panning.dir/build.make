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
include CMakeFiles/4-panning.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/4-panning.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/4-panning.dir/flags.make

CMakeFiles/4-panning.dir/4-panning.cpp.obj: CMakeFiles/4-panning.dir/flags.make
CMakeFiles/4-panning.dir/4-panning.cpp.obj: CMakeFiles/4-panning.dir/includes_CXX.rsp
CMakeFiles/4-panning.dir/4-panning.cpp.obj: ../4-panning.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/4-panning.dir/4-panning.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\4-panning.dir\4-panning.cpp.obj -c "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\4-panning.cpp"

CMakeFiles/4-panning.dir/4-panning.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4-panning.dir/4-panning.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\4-panning.cpp" > CMakeFiles\4-panning.dir\4-panning.cpp.i

CMakeFiles/4-panning.dir/4-panning.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4-panning.dir/4-panning.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\4-panning.cpp" -o CMakeFiles\4-panning.dir\4-panning.cpp.s

# Object files for target 4-panning
4__panning_OBJECTS = \
"CMakeFiles/4-panning.dir/4-panning.cpp.obj"

# External object files for target 4-panning
4__panning_EXTERNAL_OBJECTS =

4-panning.exe: CMakeFiles/4-panning.dir/4-panning.cpp.obj
4-panning.exe: CMakeFiles/4-panning.dir/build.make
4-panning.exe: CMakeFiles/4-panning.dir/linklibs.rsp
4-panning.exe: CMakeFiles/4-panning.dir/objects1.rsp
4-panning.exe: CMakeFiles/4-panning.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 4-panning.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\4-panning.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/4-panning.dir/build: 4-panning.exe
.PHONY : CMakeFiles/4-panning.dir/build

CMakeFiles/4-panning.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\4-panning.dir\cmake_clean.cmake
.PHONY : CMakeFiles/4-panning.dir/clean

CMakeFiles/4-panning.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug" "D:\data\drive\College\Forth Year\Fall Semester\Computer Graphics and Multimedia\Assignments\assignment04\cmake-build-debug\CMakeFiles\4-panning.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/4-panning.dir/depend
