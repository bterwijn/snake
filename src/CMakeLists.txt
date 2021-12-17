cmake_minimum_required(VERSION 3.7)

project(snake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(snake snake.cpp)
target_link_libraries(snake ${SDL2_LIBRARIES} -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf)
