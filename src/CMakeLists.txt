set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
include_directories("${CMAKE_SOURCE_DIR}/includes")

add_executable(conway conways_life_game.cpp)
target_link_libraries(conway SDL2)
