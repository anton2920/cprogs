cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c libs/menu.c headers/project.h libs/menu2.c libs/menu3.c libs/tree.c libs/math.c)
add_executable(Project ${SOURCE_FILES})

target_link_libraries(Project dialog ncurses m ncursesw)