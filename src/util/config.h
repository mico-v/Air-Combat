#pragma once

#include "type.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Air Combat"

#define GAME_WIDTH 800
#define GAME_HEIGHT 800

#define PLAYER_WIDTH 80
#define PLAYER_HEIGHT 120
#define ENEMY_WIDTH 80
#define ENEMY_HEIGHT 80
#define BULLET_RADIUS 5

#define PLAYER_INITIAL_HEALTH 3
#define PLAYER_SPEED 500.0
#define PLAYER_BULLET_COOLDOWN 0.1

#define BULLET_SPEED 800.0
#define BULLET_DAMAGE 1

#define ENEMY_SPEED 200.0
#define ENEMY_SPAWN_INTERVAL 1.0
#define ENEMY_HEALTH 1
#define ENEMY_SCORE 10

#define TARGET_FPS 60
#define TIMER_INTERVAL (1000 / TARGET_FPS)

constexpr Color COLOR_WHITE{255, 255, 255};
constexpr Color COLOR_BLACK{0, 0, 0};
constexpr Color COLOR_RED{255, 0, 0};
constexpr Color COLOR_BLUE{0, 0, 255};
constexpr Color COLOR_GREEN{0, 255, 0};
