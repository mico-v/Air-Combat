#pragma once

#include "../util/type.h"

struct SDL_Renderer;

// 玩家飞机的数据结构
struct Player
{
    Vector2 position;       // 位置（左上角坐标）
    double width;           // 宽度
    double height;          // 高度
    Attribute attributes;   // 属性（生命，分数，速度等）
};

// ===== 玩家模块 API =====

// 初始化并创建玩家
// 玩家会在屏幕中下方居中
void CreatePlayer();

// 获取玩家对象指针
// 返回 nullptr 表示玩家已销毁
Player* GetPlayer();

// 更新玩家状态（移动、射击、冷却）
void UpdatePlayer(double deltaTime);

// 渲染玩家（绘制蓝色矩形）
void RenderPlayer(SDL_Renderer* renderer);

// 销毁玩家对象
void DestroyPlayer();
