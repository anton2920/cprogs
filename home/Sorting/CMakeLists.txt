cmake_minimum_required(VERSION 3.14)
project(Sorting C)

set(CMAKE_C_STANDARD 90)

set(HEADER_FILES sorting.h)
set(SOURCE_FILES sorting.c adv_sorting.c compare.c convertions.c)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(Sorting SHARED ${HEADER_FILES} ${SOURCE_FILES})
add_executable(test_prog main.c ${HEADER_FILES})
target_link_libraries(test_prog Sorting -Lcmake-build-debug/)