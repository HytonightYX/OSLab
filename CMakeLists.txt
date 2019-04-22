cmake_minimum_required(VERSION 3.13)
project(OSLab C)

set(CMAKE_C_STANDARD 99)

add_executable(OSLab filetools.c)
add_executable(ProcessManager ProcessCreator.c)
add_executable(Shm shm.c)
add_executable(exp4-test1 exp4/Thread1.c)
add_executable(exp4-test2 exp4/Thread2.c)
