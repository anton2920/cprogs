# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/anton/Downloads/clion-2019.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/anton/Downloads/clion-2019.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anton/C/home/THL-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/C/home/THL-1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/creator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/creator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/creator.dir/flags.make

CMakeFiles/creator.dir/prog_creator.c.o: CMakeFiles/creator.dir/flags.make
CMakeFiles/creator.dir/prog_creator.c.o: ../prog_creator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/C/home/THL-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/creator.dir/prog_creator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/creator.dir/prog_creator.c.o   -c /home/anton/C/home/THL-1/prog_creator.c

CMakeFiles/creator.dir/prog_creator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/creator.dir/prog_creator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/C/home/THL-1/prog_creator.c > CMakeFiles/creator.dir/prog_creator.c.i

CMakeFiles/creator.dir/prog_creator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/creator.dir/prog_creator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/C/home/THL-1/prog_creator.c -o CMakeFiles/creator.dir/prog_creator.c.s

# Object files for target creator
creator_OBJECTS = \
"CMakeFiles/creator.dir/prog_creator.c.o"

# External object files for target creator
creator_EXTERNAL_OBJECTS =

creator: CMakeFiles/creator.dir/prog_creator.c.o
creator: CMakeFiles/creator.dir/build.make
creator: CMakeFiles/creator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anton/C/home/THL-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable creator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/creator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/creator.dir/build: creator

.PHONY : CMakeFiles/creator.dir/build

CMakeFiles/creator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/creator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/creator.dir/clean

CMakeFiles/creator.dir/depend:
	cd /home/anton/C/home/THL-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/C/home/THL-1 /home/anton/C/home/THL-1 /home/anton/C/home/THL-1/cmake-build-debug /home/anton/C/home/THL-1/cmake-build-debug /home/anton/C/home/THL-1/cmake-build-debug/CMakeFiles/creator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/creator.dir/depend
