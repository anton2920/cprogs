cmake_minimum_required(VERSION 3.14)
project(Sorting C)

set(CMAKE_C_STANDARD 90)

set(HEADER_FILES sorting.h)
set(SOURCE_FILES sorting.c)

add_library(Sorting SHARED ${HEADER_FILES} ${SOURCE_FILES})
add_executable(test_prog main.c ${HEADER_FILES} ${SOURCE_FILES})