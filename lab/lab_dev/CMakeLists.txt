cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c input/input.c input/input.h)
add_executable(lab_dev ${SOURCE_FILES} input/input.c input/input.h)

target_link_libraries(lab_dev m)