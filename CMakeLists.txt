cmake_minimum_required(VERSION 3.29)
project(aoc24 C)

set(CMAKE_C_STANDARD 23)

SET(SRC_FILES
        src/01.c
        src/02.c
        src/03.c
        src/04.c
        src/05.c
        src/06.c
        src/07.c
        src/08.c
        src/main.c)

include_directories(src)

add_executable(aoc24 ${SRC_FILES})
target_link_libraries(aoc24 m)