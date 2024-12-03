cmake_minimum_required(VERSION 3.29)
project(aoc24 C)

set(CMAKE_C_STANDARD 23)

SET(SRC_FILES
        src/main.c
        src/01.c)

include_directories(src)

add_executable(aoc24 ${SRC_FILES})
