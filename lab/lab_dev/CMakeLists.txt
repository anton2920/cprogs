cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c)
set(LIBS libs/libs.c libs/libs.h)
set(VISUAL visual/visual.c visual/visual.h)
set(PROCESS process/process.c process/process.h)

add_executable(lab_dev ${SOURCE_FILES} ${LIBS} ${VISUAL} ${PROCESS})

target_link_libraries(lab_dev STL_Queue STL_Algorithm STL_List STL_Vector)