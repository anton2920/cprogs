cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c libs/menu.c headers/project.h /usr/lib/x86_64-linux-gnu/libdialog.a)
add_executable(Project ${SOURCE_FILES})

target_link_libraries(Project dialog ncurses m)