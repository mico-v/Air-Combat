/**
 * @file util.cpp
 * @brief 工具函数实现文件
 * 
 * 这个文件实现了 util.h 中声明的所有工具函数。
 * 
 * 💡 学习提示：
 * 阅读这些函数的实现可以学习到：
 * - 如何进行数学计算
 * - 如何实现碰撞检测算法
 * - 如何处理边界情况
 */

#include "util.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <tchar.h>
#include <cstdarg>

// 初始化随机数生成器（在程序开始时调用一次）
static bool randomInitialized = false;

/**
 * @brief 初始化随机数生成器
 * 
 * 使用当前时间作为随机数种子，确保每次运行程序时随机数序列不同
 */
static void InitRandom()
{
    if (!randomInitialized)
    {
        srand((unsigned int)time(NULL));
        randomInitialized = true;
    }
}

/* ============================================================================
 * 数学工具函数实现
 * ============================================================================
 */

/**
 * @brief 计算向量长度
 * 
 * 实现原理：
 * 使用勾股定理：length = √(x² + y²)
 */
double Length(Vector2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

/**
 * @brief 归一化向量
 * 
 * 实现原理：
 * 1. 计算向量长度
 * 2. 如果长度不为 0，将 x 和 y 都除以长度
 * 3. 如果长度为 0，返回零向量
 * 
 * 💡 为什么要检查长度为 0？
 * 因为不能除以 0，否则会导致程序崩溃或产生 NaN（Not a Number）
 */
Vector2 Normalize(Vector2 v)
{
    double len = Length(v);
    
    // 防止除以零
    if (len < 0.0001)  // 使用小的阈值而不是直接比较 == 0
    {
        return {0, 0};
    }
    
    // 归一化：向量的每个分量都除以长度
    Vector2 result;
    result.x = v.x / len;
    result.y = v.y / len;
    return result;
}

/**
 * @brief 向量点乘
 * 
 * 实现原理：
 * 点乘 = v1.x * v2.x + v1.y * v2.y
 */
double Dot(Vector2 v1, Vector2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/**
 * @brief 计算两点之间的距离
 * 
 * 实现原理：
 * 1. 计算 x 方向的差值 dx = p2.x - p1.x
 * 2. 计算 y 方向的差值 dy = p2.y - p1.y
 * 3. 使用勾股定理：distance = √(dx² + dy²)
 */
double Distance(Vector2 p1, Vector2 p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

/**
 * @brief 限制数值在指定范围内
 * 
 * 实现原理：
 * 使用标准库的 min 和 max 函数
 */
double Clamp(double value, double min, double max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * @brief 线性插值
 * 
 * 实现原理：
 * result = a + (b - a) * t
 * 
 * 推导：
 * - 当 t = 0: result = a + (b - a) * 0 = a
 * - 当 t = 1: result = a + (b - a) * 1 = b
 * - 当 t = 0.5: result = a + (b - a) * 0.5 = (a + b) / 2
 */
double Lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

/* ============================================================================
 * 随机数工具函数实现
 * ============================================================================
 */

/**
 * @brief 生成随机整数
 * 
 * 实现原理：
 * 1. 初始化随机数生成器（如果还没初始化）
 * 2. 使用 rand() 生成 [0, RAND_MAX] 范围的随机数
 * 3. 通过取模和偏移映射到 [min, max] 范围
 */
int GetRandomInt(int min, int max)
{
    InitRandom();
    
    // rand() 返回 [0, RAND_MAX]
    // rand() % (max - min + 1) 返回 [0, max - min]
    // 再加上 min 就得到 [min, max]
    return min + rand() % (max - min + 1);
}

/**
 * @brief 生成随机小数
 * 
 * 实现原理：
 * 1. 生成 [0, 1] 的随机小数
 * 2. 线性映射到 [min, max] 范围
 */
double GetRandomDouble(double min, double max)
{
    InitRandom();
    
    // rand() / (double)RAND_MAX 生成 [0, 1] 的随机小数
    double random01 = rand() / (double)RAND_MAX;
    
    // 映射到 [min, max]
    return min + random01 * (max - min);
}

/**
 * @brief 生成随机布尔值
 * 
 * 实现原理：
 * rand() % 2 返回 0 或 1，转换为 bool 类型
 */
bool GetRandomBool()
{
    InitRandom();
    return (rand() % 2) == 1;
}

/* ============================================================================
 * 碰撞检测函数实现
 * ============================================================================
 */

/**
 * @brief 矩形与矩形碰撞检测
 * 
 * 实现原理（AABB 碰撞检测 - Axis-Aligned Bounding Box）：
 * 两个矩形碰撞当且仅当：
 * - 它们在 X 轴上有重叠
 * - 并且在 Y 轴上有重叠
 * 
 * X 轴重叠条件：rect1.right > rect2.left && rect1.left < rect2.right
 * Y 轴重叠条件：rect1.bottom > rect2.top && rect1.top < rect2.bottom
 * 
 * 💡 为什么不用 >= 和 <=？
 * 因为边界刚好接触（没有重叠）不算碰撞
 */
bool IsRectRectCollision(Rect rect1, Rect rect2)
{
    // X 轴重叠检测
    bool xOverlap = (rect1.right > rect2.left) && (rect1.left < rect2.right);
    
    // Y 轴重叠检测
    bool yOverlap = (rect1.bottom > rect2.top) && (rect1.top < rect2.bottom);
    
    // 两个轴都重叠才算碰撞
    return xOverlap && yOverlap;
}

/**
 * @brief 矩形与圆形碰撞检测
 * 
 * 实现原理：
 * 1. 找到矩形上距离圆心最近的点
 * 2. 计算这个点到圆心的距离
 * 3. 如果距离 <= 半径，则碰撞
 * 
 * 如何找最近的点？
 * - X 坐标：将圆心 X 限制在矩形的左右边界之间
 * - Y 坐标：将圆心 Y 限制在矩形的上下边界之间
 */
bool IsRectCircleCollision(Rect rect, Circle circle)
{
    // 找到矩形上距离圆心最近的点
    double closestX = Clamp(circle.center.x, rect.left, rect.right);
    double closestY = Clamp(circle.center.y, rect.top, rect.bottom);
    
    // 计算最近点到圆心的距离
    double dx = circle.center.x - closestX;
    double dy = circle.center.y - closestY;
    double distanceSquared = dx * dx + dy * dy;
    
    // 比较距离的平方和半径的平方（避免开方运算，提高性能）
    return distanceSquared <= (circle.radius * circle.radius);
}

/**
 * @brief 圆形与圆形碰撞检测
 * 
 * 实现原理：
 * 两个圆碰撞当且仅当：
 * 圆心距离 <= 两个半径之和
 * 
 * 💡 性能优化：
 * 比较距离的平方，避免开方运算
 */
bool IsCircleCircleCollision(Circle circle1, Circle circle2)
{
    // 计算圆心距离的平方
    double dx = circle2.center.x - circle1.center.x;
    double dy = circle2.center.y - circle1.center.y;
    double distanceSquared = dx * dx + dy * dy;
    
    // 计算半径和的平方
    double radiusSum = circle1.radius + circle2.radius;
    double radiusSumSquared = radiusSum * radiusSum;
    
    // 比较平方值
    return distanceSquared <= radiusSumSquared;
}

/**
 * @brief 点是否在矩形内
 * 
 * 实现原理：
 * 点在矩形内当且仅当：
 * - 点的 X 坐标在矩形的左右边界之间
 * - 并且点的 Y 坐标在矩形的上下边界之间
 */
bool IsPointInRect(Vector2 point, Rect rect)
{
    return (point.x >= rect.left && point.x <= rect.right &&
            point.y >= rect.top && point.y <= rect.bottom);
}

/**
 * @brief 点是否在圆形内
 * 
 * 实现原理：
 * 点在圆内当且仅当：
 * 点到圆心的距离 <= 半径
 */
bool IsPointInCircle(Vector2 point, Circle circle)
{
    double dx = point.x - circle.center.x;
    double dy = point.y - circle.center.y;
    double distanceSquared = dx * dx + dy * dy;
    
    return distanceSquared <= (circle.radius * circle.radius);
}

/* ============================================================================
 * 坐标转换函数实现
 * ============================================================================
 */

/**
 * @brief 创建矩形（便捷函数）
 */
Rect CreateRect(Vector2 position, double width, double height)
{
    Rect rect;
    rect.left = position.x;
    rect.right = position.x + width;
    rect.top = position.y;
    rect.bottom = position.y + height;
    return rect;
}

/**
 * @brief 创建圆形（便捷函数）
 */
Circle CreateCircle(Vector2 center, double radius)
{
    Circle circle;
    circle.center = center;
    circle.radius = radius;
    return circle;
}

/* ============================================================================
 * 调试辅助函数实现
 * ============================================================================
 */

/**
 * @brief 输出日志到状态栏
 * 
 * 实现说明：
 * 这个函数需要访问窗口句柄，实际实现可能在 info.cpp 中
 * 这里提供一个简化版本的声明
 * 
 * 💡 实际使用中，这个函数会在 info.cpp 中完整实现
 */
// extern void Log(int statusBarIndex, const TCHAR* format, ...);
// （实际实现在其他文件中）

/**
 * @brief 格式化字符串
 * 
 * 实现原理：
 * 使用 Windows API 的 StringCchVPrintf 函数进行格式化
 */
void FormatString(TCHAR* buffer, int bufferSize, const TCHAR* format, ...)
{
    va_list args;
    va_start(args, format);

    // Cross-compiler friendly formatting.
    _vsntprintf(buffer, bufferSize - 1, format, args);
    buffer[bufferSize - 1] = 0;

    va_end(args);
}


/* ============================================================================
 * 使用示例和测试
 * ============================================================================
 * 
 * 以下是一些使用示例（在实际代码中不会包含这些测试代码）
 * 
 * 示例 1：检测玩家与敌人的碰撞
 * ```cpp
 * Player* player = GetPlayer();
 * Rect playerRect = CreateRect(player->position, player->width, player->height);
 * 
 * for (Enemy* enemy : GetEnemies())
 * {
 *     Rect enemyRect = CreateRect(enemy->position, enemy->width, enemy->height);
 *     
 *     if (IsRectRectCollision(playerRect, enemyRect))
 *     {
 *         // 玩家与敌人碰撞
 *         player->attributes.health--;
 *         player->attributes.score += enemy->attributes.score;
 *         DestroyEnemy(enemy);
 *     }
 * }
 * ```
 * 
 * 示例 2：检测子弹与敌人的碰撞
 * ```cpp
 * for (Enemy* enemy : GetEnemies())
 * {
 *     Rect enemyRect = CreateRect(enemy->position, enemy->width, enemy->height);
 *     
 *     for (Bullet* bullet : GetBullets())
 *     {
 *         Circle bulletCircle = CreateCircle(bullet->position, bullet->radius);
 *         
 *         if (IsRectCircleCollision(enemyRect, bulletCircle))
 *         {
 *             // 子弹击中敌人
 *             enemy->attributes.health -= bullet->damage;
 *             if (enemy->attributes.health <= 0)
 *             {
 *                 GetPlayer()->attributes.score += enemy->attributes.score;
 *                 DestroyEnemy(enemy);
 *             }
 *             DestroyBullet(bullet);
 *             break;  // 子弹已销毁，跳出内层循环
 *         }
 *     }
 * }
 * ```
 * 
 * 示例 3：平滑移动
 * ```cpp
 * // 使用 WASD 移动，并归一化方向保证所有方向速度一致
 * Vector2 direction = {0, 0};
 * if (GetKeyDown('W')) direction.y -= 1;
 * if (GetKeyDown('S')) direction.y += 1;
 * if (GetKeyDown('A')) direction.x -= 1;
 * if (GetKeyDown('D')) direction.x += 1;
 * 
 * direction = Normalize(direction);
 * 
 * player->position.x += direction.x * player->attributes.speed * deltaTime;
 * player->position.y += direction.y * player->attributes.speed * deltaTime;
 * 
 * // 限制在屏幕内
 * player->position.x = Clamp(player->position.x, 0, GAME_WIDTH - player->width);
 * player->position.y = Clamp(player->position.y, 0, GAME_HEIGHT - player->height);
 * ```
 * 
 * 示例 4：定时生成敌人
 * ```cpp
 * static double lastSpawnTime = 0;
 * double currentTime = GetGameTime();
 * 
 * if (currentTime - lastSpawnTime > ENEMY_SPAWN_INTERVAL)
 * {
 *     // 在随机位置生成敌人
 *     double randomX = GetRandomDouble(0, GAME_WIDTH - ENEMY_WIDTH);
 *     CreateEnemy(randomX, -ENEMY_HEIGHT);  // 从屏幕上方生成
 *     
 *     lastSpawnTime = currentTime;
 * }
 * ```
 * 
 * ============================================================================
 */
