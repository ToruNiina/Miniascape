project(Miniascape)
cmake_minimum_required(VERSION 2.8)
enable_testing()

add_definitions(-std=c++11)
add_definitions(-Wall -O3)
include_directories(${PROJECT_SOURCE_DIR}/extlib/pseudo)

add_subdirectory(test)
add_subdirectory(src)
