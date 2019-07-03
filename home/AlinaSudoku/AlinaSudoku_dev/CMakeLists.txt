cmake_minimum_required(VERSION 3.14)
project(AlinaSudoku_dev C)

set(CMAKE_C_STANDARD 90)
set(HEADER_FILES Header.h)
set(SOURCE_FILES ../main.c ../init.c)

add_executable(AlinaSudoku_dev ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(AlinaSudoku_dev m SDL2 SDL2_image SDL2_mixer SDL2_ttf)