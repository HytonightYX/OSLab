cmake_minimum_required(VERSION 3.13)
project(OSLab C)

set(CMAKE_C_STANDARD 99)

add_executable(OSLab filetools.c)
add_executable(ProcessManager exp3/Process1.c)
add_executable(exp3-process2 exp3/Process2.c)
add_executable(exp3-systemV-1 exp3/SystemV-1.c)
add_executable(exp3-systemV-2 exp3/SystemV-2.c)
add_executable(exp3-POSIX-P exp3/POSIX-Producer.c)
add_executable(exp3-POSIX-C exp3/POSIX-Consumer.c)


add_executable(exp4-test1 exp4/Thread1.c)
add_executable(exp4-test2 exp4/Thread2.c)
