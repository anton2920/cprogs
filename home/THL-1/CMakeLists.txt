cmake_minimum_required(VERSION 3.15)
project(THL_1 C)

set(CMAKE_C_STANDARD 99)

set(ALU alu.h)
set(REG register.h)
set(RAM ram.h)
set(PC pc.h)
set(CU control.c control.h)

add_executable(THL_1 main.c ${ALU} ${REG} ${RAM} ${PC} ${CU})