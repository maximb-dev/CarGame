cmake_minimum_required(VERSION 3.31)
project(CarGame)

set(CMAKE_CXX_STANDARD 23)

add_executable(CarGame src/main.cpp
        src/Player.cpp
        src/Game.cpp
        src/Coordinate.cpp
        src/Car.cpp)
