# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /home/anton/Загрузки/clion-2019.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/anton/Загрузки/clion-2019.1.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anton/C/home/STL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/C/home/STL/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/STL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/STL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/STL.dir/flags.make

CMakeFiles/STL.dir/STL_Stack.c.o: CMakeFiles/STL.dir/flags.make
CMakeFiles/STL.dir/STL_Stack.c.o: ../STL_Stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/C/home/STL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/STL.dir/STL_Stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/STL.dir/STL_Stack.c.o   -c /home/anton/C/home/STL/STL_Stack.c

CMakeFiles/STL.dir/STL_Stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/STL.dir/STL_Stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/C/home/STL/STL_Stack.c > CMakeFiles/STL.dir/STL_Stack.c.i

CMakeFiles/STL.dir/STL_Stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/STL.dir/STL_Stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/C/home/STL/STL_Stack.c -o CMakeFiles/STL.dir/STL_Stack.c.s

CMakeFiles/STL.dir/STL_List.c.o: CMakeFiles/STL.dir/flags.make
CMakeFiles/STL.dir/STL_List.c.o: ../STL_List.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/C/home/STL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/STL.dir/STL_List.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/STL.dir/STL_List.c.o   -c /home/anton/C/home/STL/STL_List.c

CMakeFiles/STL.dir/STL_List.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/STL.dir/STL_List.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/C/home/STL/STL_List.c > CMakeFiles/STL.dir/STL_List.c.i

CMakeFiles/STL.dir/STL_List.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/STL.dir/STL_List.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/C/home/STL/STL_List.c -o CMakeFiles/STL.dir/STL_List.c.s

# Object files for target STL
STL_OBJECTS = \
"CMakeFiles/STL.dir/STL_Stack.c.o" \
"CMakeFiles/STL.dir/STL_List.c.o"

# External object files for target STL
STL_EXTERNAL_OBJECTS =

libSTL.so: CMakeFiles/STL.dir/STL_Stack.c.o
libSTL.so: CMakeFiles/STL.dir/STL_List.c.o
libSTL.so: CMakeFiles/STL.dir/build.make
libSTL.so: CMakeFiles/STL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anton/C/home/STL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library libSTL.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/STL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/STL.dir/build: libSTL.so

.PHONY : CMakeFiles/STL.dir/build

CMakeFiles/STL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/STL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/STL.dir/clean

CMakeFiles/STL.dir/depend:
	cd /home/anton/C/home/STL/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/C/home/STL /home/anton/C/home/STL /home/anton/C/home/STL/cmake-build-debug /home/anton/C/home/STL/cmake-build-debug /home/anton/C/home/STL/cmake-build-debug/CMakeFiles/STL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/STL.dir/depend

