cmake_minimum_required(VERSION 3.16)

project(AirCombat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(AirCombat
    src/main.cpp
    src/core/core.cpp

    src/game_object/player.cpp
    src/game_object/enemy.cpp
    src/game_object/bullet.cpp

    src/input/input.cpp

    src/ui/hud.cpp

    src/util/util.cpp
)

target_include_directories(AirCombat PRIVATE
    src
)

target_link_libraries(AirCombat PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
if (TARGET SDL2::SDL2main)
    target_link_libraries(AirCombat PRIVATE SDL2::SDL2main)
endif()
