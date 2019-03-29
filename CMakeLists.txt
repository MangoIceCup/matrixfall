cmake_minimum_required(VERSION 3.13)
project(NoResponseServer C)
set(CMAKE_C_STANDARD 99)
add_executable(NoResponseServer main.c linkedarray.c linkedarray.h stringutils.c stringutils.h)
target_link_libraries(NoResponseServer m)

