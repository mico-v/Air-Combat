#pragma once

#include "../util/type.h"

#include <vector>

struct SDL_Renderer;

// 子弹的数据结构
struct Bullet
{
    Vector2 position;   // 位置（圆心）
    double radius;      // 半径
    int damage;         // 伤害值
    double speed;       // 移动速度（向上）
};

// ===== 子弹模块 API =====

// 在指定位置创建一颗子弹
void CreateBullet(double x, double y, int damage, double speed);

// 更新所有子弹（移动、检测超出边界、处理射击）
void UpdateBullets(double deltaTime);

// 绘制所有子弹（红色圆形）
void RenderBullets(SDL_Renderer* renderer);

// 清空所有子弹
void ClearBullets();

// 获取子弹列表（供碰撞检测使用）
std::vector<Bullet>& GetBullets();
