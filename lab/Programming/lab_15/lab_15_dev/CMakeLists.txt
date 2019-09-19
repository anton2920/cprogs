cmake_minimum_required(VERSION 3.8)
project(lab_15_dev)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c libs/a1.h libs/menu.c libs/rwr.c libs/struct.c)
add_executable(lab_15_dev ${SOURCE_FILES} libs/a1.h libs/menu.c libs/rwr.c libs/struct.c)