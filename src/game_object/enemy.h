#pragma once

#include "../util/type.h"

#include <vector>

struct SDL_Renderer;

// 敌机的数据结构
struct Enemy
{
    Vector2 position;       // 位置（左上角坐标）
    double width;           // 宽度
    double height;          // 高度
    Attribute attributes;   // 属性（生命，分数，速度等）
};

// ===== 敌人模块 API =====

// 在指定位置创建一个敌人
void CreateEnemy(double x, double y);

// 创建一个随机位置的敌人（在屏幕上方）
void CreateRandomEnemy();

// 更新所有敌人（移动、生成新敌人、删除超出屏幕的）
void UpdateEnemies(double deltaTime);

// 绘制所有敌人（红色矩形）
void RenderEnemies(SDL_Renderer* renderer);

// 清空所有敌人
void ClearEnemies();

// 获取敌人列表（供碰撞检测使用）
std::vector<Enemy>& GetEnemies();
