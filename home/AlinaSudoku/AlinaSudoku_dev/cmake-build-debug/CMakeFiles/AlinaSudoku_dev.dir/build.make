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
CMAKE_SOURCE_DIR = /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AlinaSudoku_dev.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AlinaSudoku_dev.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AlinaSudoku_dev.dir/flags.make

CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.o: CMakeFiles/AlinaSudoku_dev.dir/flags.make
CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.o: /home/anton/C/home/AlinaSudoku/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.o   -c /home/anton/C/home/AlinaSudoku/main.c

CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/C/home/AlinaSudoku/main.c > CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.i

CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/C/home/AlinaSudoku/main.c -o CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.s

CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.o: CMakeFiles/AlinaSudoku_dev.dir/flags.make
CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.o: /home/anton/C/home/AlinaSudoku/init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.o   -c /home/anton/C/home/AlinaSudoku/init.c

CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anton/C/home/AlinaSudoku/init.c > CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.i

CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anton/C/home/AlinaSudoku/init.c -o CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.s

# Object files for target AlinaSudoku_dev
AlinaSudoku_dev_OBJECTS = \
"CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.o" \
"CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.o"

# External object files for target AlinaSudoku_dev
AlinaSudoku_dev_EXTERNAL_OBJECTS =

AlinaSudoku_dev: CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/main.c.o
AlinaSudoku_dev: CMakeFiles/AlinaSudoku_dev.dir/home/anton/C/home/AlinaSudoku/init.c.o
AlinaSudoku_dev: CMakeFiles/AlinaSudoku_dev.dir/build.make
AlinaSudoku_dev: CMakeFiles/AlinaSudoku_dev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable AlinaSudoku_dev"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AlinaSudoku_dev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AlinaSudoku_dev.dir/build: AlinaSudoku_dev

.PHONY : CMakeFiles/AlinaSudoku_dev.dir/build

CMakeFiles/AlinaSudoku_dev.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AlinaSudoku_dev.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AlinaSudoku_dev.dir/clean

CMakeFiles/AlinaSudoku_dev.dir/depend:
	cd /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug /home/anton/C/home/AlinaSudoku/AlinaSudoku_dev/cmake-build-debug/CMakeFiles/AlinaSudoku_dev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AlinaSudoku_dev.dir/depend

