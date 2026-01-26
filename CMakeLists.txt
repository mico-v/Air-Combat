cmake_minimum_required(VERSION 3.16)

project(AirCombat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AirCombat WIN32
    src/core/main.cpp
    src/core/core.cpp
    src/core/info.cpp

    src/scene/scene.cpp
    src/scene/scene1.cpp
    src/scene/scene2.cpp

    src/resource/resource.cpp

    src/ui/button.cpp

    src/game_object/player.cpp
    src/game_object/enemy.cpp
    src/game_object/bullet.cpp

    src/util/util.cpp
    src/util/keyboard.cpp
    src/util/mouse.cpp
)

target_include_directories(AirCombat PRIVATE
    src
)

target_compile_definitions(AirCombat PRIVATE
    UNICODE
    _UNICODE
)

if (MINGW)
    target_link_options(AirCombat PRIVATE -municode)
endif()

target_link_libraries(AirCombat PRIVATE
    user32
    gdi32
    comctl32
    msimg32
)
