cmake_minimum_required(VERSION 3.8)
project(lab_dev)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c)
set(LIBS libs/libs.c libs/libs.h)

add_executable(lab_dev ${SOURCE_FILES} ${LIBS} ${VISUAL} ${PROCESS})
add_executable(client client.c)
add_executable(libs libs/libs.c)

target_link_libraries(lab_dev pthread)
target_link_libraries(client pthread)