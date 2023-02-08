cmake_minimum_required(VERSION 3.6)
project(Wordle-Solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors")

set(SOURCE_FILES
        wordleSolver.cpp)

add_executable(project1 ${SOURCE_FILES})
