#pragma once

#include "type.h"

#include <cmath>

// ===== 数学函数 =====
// 计算向量的长度—勾股定理
double Length(Vector2 v);

// 将向量正规化为单位向量
Vector2 Normalize(Vector2 v);

// 两个向量的点积
double Dot(Vector2 v1, Vector2 v2);

// 计算两个点之间的欧氏距离
double Distance(Vector2 p1, Vector2 p2);

// 限制值到指定范围（夹取）
double Clamp(double value, double min, double max);

// 线性插值
double Lerp(double a, double b, double t);

// ===== 随机数函数 =====
// 给定范围内的随机整数
int GetRandomInt(int min, int max);

// 给定范围内的随机浮点数
double GetRandomDouble(double min, double max);

// 随机bool值
bool GetRandomBool();

// ===== 碰撞检测函数 =====
// 矩形与矩形碰撞检测
bool IsRectRectCollision(Rect r1, Rect r2);

// 矩形与圆形碰撞检测
bool IsRectCircleCollision(Rect rect, Circle circle);

// 圆形与圆形碰撞检测
bool IsCircleCircleCollision(Circle c1, Circle c2);

// 点在矩形内检测
bool IsPointInRect(Vector2 p, Rect r);

// 点在圆形内检测
bool IsPointInCircle(Vector2 p, Circle c);

// ===== 辅助函数 =====
// 根据位置和大小构造矩形
Rect CreateRect(Vector2 position, double width, double height);

// 根据中心和半径构造圆形
Circle CreateCircle(Vector2 center, double radius);
