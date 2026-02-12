#pragma once

// 二维向量，用于表示位置、方向或速度
struct Vector2
{
    double x;  // 水平坐标
    double y;  // 竖直坐标
};

// 矩形，用于多边形碰撞检测和绘制
// 存储相对坐标：left/right/top/bottom
struct Rect
{
    double left;    // 左边界 x 坐标
    double right;   // 右边界 x 坐标
    double top;     // 上边界 y 坐标
    double bottom;  // 下边界 y 坐标
};

// 圆形，用于子弹碰撞检测
struct Circle
{
    Vector2 center;   // 圆心
    double radius;    // 半径
};

// 游戏对象的属性（生命值、分数、速度等）
struct Attribute
{
    int health;          // 当前生命值
    int score;           // 累计得分
    double speed;        // 移动速度（像素/秒）
    double maxBulletCd;  // 射击冷却时间上限（秒）
    double bulletCd;     // 当前射击冷却时间（秒）
};

// RGB 颜色，用于 SDL2 绘制
struct Color
{
    unsigned char r;  // 红色分量 0-255
    unsigned char g;  // 绿色分量 0-255
    unsigned char b;  // 蓝色分量 0-255
};
