set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)
include_directories("${PROJECT_SOURCE_DIR}/includes")

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY  NAME SDL2)

add_executable(conway conways_life_game.cpp)
target_link_libraries(conway SDL2)

add_executable(ising ising_model.cpp)
target_link_libraries(ising SDL2)

add_executable(turing turing_pattern.cpp)
target_link_libraries(turing SDL2)
