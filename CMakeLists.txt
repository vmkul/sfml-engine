cmake_minimum_required(VERSION 3.19)
project(sfml_engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(
        sfml_engine
        src/main.cpp
        src/EventManager.cpp
        src/EventManager.h
        src/GUI.cpp
        src/GUI.h
        src/GameBoard.cpp src/GameBoard.h)

target_link_libraries(sfml_engine sfml-graphics sfml-window sfml-system)
