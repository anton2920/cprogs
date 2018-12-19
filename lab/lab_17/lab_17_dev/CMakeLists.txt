cmake_minimum_required(VERSION 3.8)
project(lab_17_dev)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c libs/rwr.c libs/menu.c headers/lab.h)
add_executable(lab_17_dev ${SOURCE_FILES} libs/rwr.c libs/menu.c headers/lab.h)