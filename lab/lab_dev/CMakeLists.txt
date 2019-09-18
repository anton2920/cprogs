cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(HEADER_FILES libs/libs.h)
set(SOURCE_FILES main.c libs/libs.c)
add_executable(lab_dev ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(lab_dev m)