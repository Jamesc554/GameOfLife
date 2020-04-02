cmake_minimum_required(VERSION 3.13)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameOfLife catch2/catch_main.cpp tests/test_1.cpp tests/test_2.cpp tests/test_3.cpp tests/test_4.cpp tests/test_5.cpp
        tests/test_6.cpp tests/test_7.cpp tests/test_8.cpp tests/test_9.cpp tests/test_10.cpp tests/test_11.cpp tests/test_12.cpp tests/test_13.cpp
        tests/test_14.cpp tests/test_15.cpp tests/test_16.cpp tests/test_17.cpp tests/test_18.cpp tests/test_19.cpp tests/test_20.cpp tests/test_21.cpp
        tests/test_22.cpp grid.cpp world.cpp zoo.cpp)