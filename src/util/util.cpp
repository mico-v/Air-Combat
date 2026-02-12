#include "util.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace
{
    // 标记是否已经初始化随机数生成器
    bool g_randomInitialized = false;
}

// 初始化随机数生成器一次
// 使用当前时间作为seed以保证每次运行有不同的随机序列
static void InitRandom()
{
    if (!g_randomInitialized)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        g_randomInitialized = true;
    }
}

// ===== 数学函数实现 =====

// 计算 2D 向量的长度根据勾股定理: sqrt(x^2 + y^2)
double Length(Vector2 v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// 将向量正规化为单位向量（方向不变，长度变为1）
// 特殊情况：向量为0时返回 (0, 0)
Vector2 Normalize(Vector2 v)
{
    double len = Length(v);
    if (len <= 0.000001)  // 不为0以避免除以0错误
        return {0.0, 0.0};
    return {v.x / len, v.y / len};
}

// 计算两个向量的点积（数量积）
double Dot(Vector2 v1, Vector2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

// 计算两个点之间的欧氏距离
double Distance(Vector2 p1, Vector2 p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

// 限制值到指定范围（夹取函数）
double Clamp(double value, double min, double max)
{
    if (value < min)
 
           return min;
    if (value > max)
        return max;
    return value;
}

// 线性插值（于 a 和 b 之间按比例 t 作插值）
double Lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

// ===== 随机数函数实现 =====

// 给定范围 [min, max] 内的随机整数
int GetRandomInt(int min, int max)
{
    InitRandom();
    return min + std::rand() % (max - min + 1);
}

// 给定范围 [min, max] 内的随机浮点数
double GetRandomDouble(double min, double max)
{
    InitRandom();
    double r = std::rand() / static_cast<double>(RAND_MAX);  // 归一化到 [0, 1]
    return min + r * (max - min);  // 撥伴到 [min, max]
}

// 随机返回 true 或 false
bool GetRandomBool()
{
    InitRandom();
    return (std::rand() % 2) == 1;
}

// ===== 碰撞检测实现 =====

// 矩形 r1 与矩形 r2 是否碰撞（一敌个轴无法帮交则无碰撞）
bool IsRectRectCollision(Rect r1, Rect r2)
{
    // 检查 x 轴是否分离
    if (r1.right < r2.left || r1.left > r2.right)
        return false;
    // 检查 y 轴是否分离
    if (r1.bottom < r2.top || r1.top > r2.bottom)
        return false;
    return true;  // 两个轴都有锅叠，故碰撞
}

// 矩形与圆是否碰撞
// 不是値接检查圆心距离，而检查最接近的点
bool IsRectCircleCollision(Rect rect, Circle circle)
{
    // 找到矩形上与圆心最接近的点
    double closestX = Clamp(circle.center.x, rect.left, rect.right);
    double closestY = Clamp(circle.center.y, rect.top, rect.bottom);
    
    // 计算最近点距圆心的距离
    double dx = circle.center.x - closestX;
    double dy = circle.center.y - closestY;
    double distSq = dx * dx + dy * dy;
    
    // 如果距离 ≤ 半径，则碰撞
    return distSq <= circle.radius * circle.radius;
}

// 圆与圆是否碰撞
// 两圆圆心距离 ≤ 两半径之和时碰撞
bool IsCircleCircleCollision(Circle c1, Circle c2)
{
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double r = c1.radius + c2.radius;
    return (dx * dx + dy * dy) <= r * r;  // 使用龠次方避免需根号
}

// 点 p 是否在矩形内
bool IsPointInRect(Vector2 p, Rect r)
{
    return p.x >= r.left && p.x <= r.right && p.y >= r.top && p.y <= r.bottom;
}

// 点 p 是否在圆形内
bool IsPointInCircle(Vector2 p, Circle c)
{
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    return (dx * dx + dy * dy) <= c.radius * c.radius;
}

// ===== 辅助函数实现 =====

// 根据位置和大小构造一个矩形
Rect CreateRect(Vector2 position, double width, double height)
{
    // position 是左上角，需要计算右下角
    return {position.x, position.x + width, position.y, position.y + height};
}

// 根据中心和半径构造一个圆形
Circle CreateCircle(Vector2 center, double radius)
{
    return {center, radius};
}
