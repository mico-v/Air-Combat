#pragma once

#include "type.h"

// ===== 窗口配置 =====
#define WINDOW_WIDTH 1000       // 窗口宽度（像素）
#define WINDOW_HEIGHT 800       // 窗口高度（像素）
#define WINDOW_TITLE "Air Combat"

// ===== 游戏区域配置 =====
#define GAME_WIDTH 1000         // 游戏可活动区域宽度
#define GAME_HEIGHT 800         // 游戏可活动区域高度

// ===== 游戏对象大小 =====
#define PLAYER_WIDTH 80         // 玩家飞机宽度
#define PLAYER_HEIGHT 120       // 玩家飞机高度
#define ENEMY_WIDTH 60          // 敌机宽度
#define ENEMY_HEIGHT 60         // 敌机高度
#define BULLET_RADIUS 5         // 子弹半径

// ===== 玩家参数 =====
#define PLAYER_INITIAL_HEALTH 3  // 初始生命值
#define PLAYER_SPEED 600.0      // 移动速度（像素/秒）
#define PLAYER_BULLET_COOLDOWN 0.1  // 射击冷却时间（秒），值越小射速越快

// ===== 子弹参数 =====
#define BULLET_SPEED 800.0      // 子弹移动速度（像素/秒）
#define BULLET_DAMAGE 1         // 每颗子弹伤害

// ===== 敌人参数 =====
#define ENEMY_SPEED 200.0       // 敌机下落速度（像素/秒）
#define ENEMY_SPAWN_INTERVAL 1.0  // 敌机生成间隔（秒），值越小敌人越多
#define ENEMY_HEALTH 1          // 敌机生命值
#define ENEMY_SCORE (ENEMY_HEALTH * 10)          // 击杀敌机获得的分数

// ===== 帧率配置 =====
#define TARGET_FPS 60           // 目标帧率
#define TIMER_INTERVAL (1000 / TARGET_FPS)  // 单帧耗时（毫秒）

// ===== 颜色常量 =====
constexpr Color COLOR_WHITE{255, 255, 255};  // 白色
constexpr Color COLOR_BLACK{0, 0, 0};        // 黑色
constexpr Color COLOR_RED{255, 0, 0};        // 红色（子弹）
constexpr Color COLOR_BLUE{0, 0, 255};       // 蓝色（玩家）
constexpr Color COLOR_GREEN{0, 255, 0};      // 绿色
