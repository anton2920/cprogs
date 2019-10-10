cmake_minimum_required(VERSION 3.14)
project(src C)

set(CMAKE_C_STANDARD 90)

set(STL_LIST STL_List/STL_List.c STL_List/STL_List.h)
set(STL_QUEUE STL_Queue/STL_Queue.c STL_Queue/STL_Queue.h)

add_library(STL SHARED ${STL_LIST} ${STL_QUEUE})
add_executable(main main.c)
target_link_libraries(main STL)
