cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(HEADER_FILES libs/libs.h)
set(SOURCE_FILES main.c libs/libs.c)
set(TREE_FILES tree/tree.c tree/tree.h)

set(STL_SOURCE /home/anton/C/home/STL2/src/STL_List/STL_List.c)

add_library(STL ${STL_SOURCE})
add_executable(lab_dev ${HEADER_FILES} ${SOURCE_FILES} ${TREE_FILES})

target_link_libraries(lab_dev m STL)