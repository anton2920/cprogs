cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(HEADER_FILES input/input.h proj_folder/source.h)
set(SOURCE_FILES main.c input/input.c proj_folder/source.c)
add_executable(lab_dev ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(lab_dev m SDL2 SDL2_image SDL2_ttf SDL2_mixer)

# SDL2
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${lab_dev_SOURCE_DIR}/cmake")
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})
#target_link_libraries(lab_dev ${SDL2_LIBRARY})