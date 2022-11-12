Cmake_minimum_required(VERSION 3.23)
project(ece-city-1-a C)

set(CMAKE_C_STANDARD 11 )

add_executable(ece-city-1-a main.c map.c map.h boiteoutil.c boiteoutil.h element.c element.h)
add_subdirectory(raylib)
target_link_libraries(ece-city-1-a raylib)

