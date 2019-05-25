cmake_minimum_required(VERSION 3.14)
project(STL C)

set(CMAKE_C_STANDARD 90)
set(SOURCE_FILES STL_Stack.c STL_List.c)
set(HEADER_FILES STL.h)

add_library(STL SHARED ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(STL PROPERTIES PUBLIC_HEADER ${HEADER_FILES})

add_executable(main main.c)
target_link_libraries(main STL)
install(TARGETS STL LIBRARY DESTINATION lib CONFIGURATIONS Release)