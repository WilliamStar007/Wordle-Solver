cmake_minimum_required(VERSION 3.6)
project(Wordle-Solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors")

set(HEADER_FILES wordleSolver.h)
set(SOURCE_FILES wordleSolver.cpp main.cpp)

add_executable(Wordle-Solver ${SOURCE_FILES} ${HEADER_FILES})
