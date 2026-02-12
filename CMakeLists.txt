cmake_minimum_required(VERSION 3.16)

project(AirCombat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

# Find SDL2_ttf - try CONFIG first, then pkg-config (Linux fallback)
find_package(SDL2_ttf CONFIG QUIET)
if(NOT SDL2_ttf_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(SDL2_TTF IMPORTED_TARGET SDL2_ttf)
        if(NOT SDL2_TTF_FOUND)
            pkg_check_modules(SDL2_TTF IMPORTED_TARGET sdl2-ttf)
        endif()
        if(SDL2_TTF_FOUND)
            add_library(SDL2_ttf::SDL2_ttf ALIAS PkgConfig::SDL2_TTF)
        else()
            message(FATAL_ERROR "SDL2_ttf not found via pkg-config")
        endif()
    else()
        message(FATAL_ERROR "SDL2_ttf not found and pkg-config not available")
    endif()
endif()

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
