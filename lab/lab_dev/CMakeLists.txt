cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
set(LIBS libs/libs.c libs/libs.h)

add_executable(lab_dev ${SOURCE_FILES} ${LIBS})

target_link_libraries(lab_dev)