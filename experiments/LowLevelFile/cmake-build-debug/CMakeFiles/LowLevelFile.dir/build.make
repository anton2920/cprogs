# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/anton/Загрузки/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/anton/Загрузки/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anton/C/experiments/LowLevelFile

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/C/experiments/LowLevelFile/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LowLevelFile.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LowLevelFile.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LowLevelFile.dir/flags.make

CMakeFiles/LowLevelFile.dir/main.c.o: CMakeFiles/LowLevelFile.dir/flags.make
CMakeFiles/LowLevelFile.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/C/experiments/LowLevelFile/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/LowLevelFile.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LowLevelFile.dir/main.c.o   -c /home/anton/C/experiments/LowLevelFile/main.c

CMakeFiles/LowLevelFile.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LowLevelFile.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/C/experiments/LowLevelFile/main.c > CMakeFiles/LowLevelFile.dir/main.c.i

CMakeFiles/LowLevelFile.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LowLevelFile.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/C/experiments/LowLevelFile/main.c -o CMakeFiles/LowLevelFile.dir/main.c.s

CMakeFiles/LowLevelFile.dir/main.c.o.requires:

.PHONY : CMakeFiles/LowLevelFile.dir/main.c.o.requires

CMakeFiles/LowLevelFile.dir/main.c.o.provides: CMakeFiles/LowLevelFile.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/LowLevelFile.dir/build.make CMakeFiles/LowLevelFile.dir/main.c.o.provides.build
.PHONY : CMakeFiles/LowLevelFile.dir/main.c.o.provides

CMakeFiles/LowLevelFile.dir/main.c.o.provides.build: CMakeFiles/LowLevelFile.dir/main.c.o


CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o: CMakeFiles/LowLevelFile.dir/flags.make
CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o: ../libs/rwcul.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/C/experiments/LowLevelFile/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o   -c /home/anton/C/experiments/LowLevelFile/libs/rwcul.c

CMakeFiles/LowLevelFile.dir/libs/rwcul.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LowLevelFile.dir/libs/rwcul.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/C/experiments/LowLevelFile/libs/rwcul.c > CMakeFiles/LowLevelFile.dir/libs/rwcul.c.i

CMakeFiles/LowLevelFile.dir/libs/rwcul.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LowLevelFile.dir/libs/rwcul.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/C/experiments/LowLevelFile/libs/rwcul.c -o CMakeFiles/LowLevelFile.dir/libs/rwcul.c.s

CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.requires:

.PHONY : CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.requires

CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.provides: CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.requires
	$(MAKE) -f CMakeFiles/LowLevelFile.dir/build.make CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.provides.build
.PHONY : CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.provides

CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.provides.build: CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o


# Object files for target LowLevelFile
LowLevelFile_OBJECTS = \
"CMakeFiles/LowLevelFile.dir/main.c.o" \
"CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o"

# External object files for target LowLevelFile
LowLevelFile_EXTERNAL_OBJECTS =

LowLevelFile: CMakeFiles/LowLevelFile.dir/main.c.o
LowLevelFile: CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o
LowLevelFile: CMakeFiles/LowLevelFile.dir/build.make
LowLevelFile: CMakeFiles/LowLevelFile.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anton/C/experiments/LowLevelFile/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable LowLevelFile"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LowLevelFile.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LowLevelFile.dir/build: LowLevelFile

.PHONY : CMakeFiles/LowLevelFile.dir/build

CMakeFiles/LowLevelFile.dir/requires: CMakeFiles/LowLevelFile.dir/main.c.o.requires
CMakeFiles/LowLevelFile.dir/requires: CMakeFiles/LowLevelFile.dir/libs/rwcul.c.o.requires

.PHONY : CMakeFiles/LowLevelFile.dir/requires

CMakeFiles/LowLevelFile.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LowLevelFile.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LowLevelFile.dir/clean

CMakeFiles/LowLevelFile.dir/depend:
	cd /home/anton/C/experiments/LowLevelFile/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/C/experiments/LowLevelFile /home/anton/C/experiments/LowLevelFile /home/anton/C/experiments/LowLevelFile/cmake-build-debug /home/anton/C/experiments/LowLevelFile/cmake-build-debug /home/anton/C/experiments/LowLevelFile/cmake-build-debug/CMakeFiles/LowLevelFile.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LowLevelFile.dir/depend

