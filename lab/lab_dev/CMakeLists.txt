cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c)
set(LIBS libs/libs.c libs/libs.h)
set(PROCESS libs/process.c libs/process.h)
set(VISUAL libs/visual.c libs/visual.h)

add_executable(lab_dev ${SOURCE_FILES} ${LIBS} ${PROCESS} ${VISUAL})

target_link_libraries(lab_dev STL_Queue STL_Algorithm STL_Vector STL_List)