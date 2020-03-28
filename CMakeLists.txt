cmake_minimum_required(VERSION 3.13)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

#add_executable(GameOfLife MainTest.cpp grid.cpp CoordException.cpp CoordException.h zoo.cpp)
add_executable(GameOfLife catch2/catch_main.cpp tests/test_14.cpp tests/test_20.cpp grid.cpp world.cpp zoo.cpp)