cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c)
set(TREE_FILES tree/tree.c tree/tree.h)

add_executable(lab_dev ${SOURCE_FILES} ${TREE_FILES})

target_link_libraries(lab_dev m)