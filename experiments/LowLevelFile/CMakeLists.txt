cmake_minimum_required(VERSION 3.8)
project(LowLevelFile)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c headers/llfile.h libs/rwcul.c)
add_executable(LowLevelFile ${SOURCE_FILES} headers/llfile.h libs/rwcul.c)