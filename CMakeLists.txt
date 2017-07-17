project(Miniascape)
cmake_minimum_required(VERSION 2.8)
enable_testing()

add_definitions(-std=c++11)
add_definitions(-Wall -O3)

add_subdirectory(test)
add_subdirectory(src)
