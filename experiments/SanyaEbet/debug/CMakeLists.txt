cmake_minimum_required(VERSION 3.8)
project(debug)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c libs/input.h libs/getch.c libs/getint.c)
add_executable(debug ${SOURCE_FILES} libs/input.h libs/getch.c libs/getint.c)