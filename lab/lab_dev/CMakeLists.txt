cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

set(SOURCE_FILES main.c)
set(LIBS libs/libs.c libs/libs.h)
set(MAP libs/hash_map.c libs/hash_map.h)

add_executable(lab_dev ${SOURCE_FILES} ${LIBS} ${MAP})

target_link_libraries(lab_dev STL_String)