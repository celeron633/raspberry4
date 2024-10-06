cmake_minimum_required(VERSION 3.10)
project(list_test)

set(CMAKE_C_STANDARD 99)

set(SRC_FILES list.c main.c)

add_executable(list_test ${SRC_FILES})
