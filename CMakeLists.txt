Cmake_minimum_required(VERSION 3.23)
project(ece-city-1-a C)

set(CMAKE_C_STANDARD 11)

add_executable(ece-city-1-a main.c)

IF(WIN32)
    target_link_libraries(ece-city-1-a -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.8.0_2/include)
    LINK_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.8.0_2/lib)
    file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.8.0_2/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(ece-city-1-a ${LIBRARIES})
ENDIF(WIN32)