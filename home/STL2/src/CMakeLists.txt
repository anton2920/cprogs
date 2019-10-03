cmake_minimum_required(VERSION 3.14)
project(src C)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES STL_List/STL_List.c)
set(HEADER_FILES STL_Config.h STL_List/STL_List.h)

add_library(STL SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_executable(main main.c)
target_link_libraries(main STL)
