cmake_minimum_required(VERSION 3.26)
project(chicken_fight)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(chicken_fight
        chicken.h
        game_read.h
        main.cpp
        bullet.h
        drawer.h)

add_executable(chicken_fight_ai
        AIPlayer/main_ai.cpp
        AIPlayer/AIController.h
        chicken.h
        bullet.h
        drawer.h
        game_read.h)
