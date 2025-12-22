/**
 * @file util.h
 * @brief 工具函数声明文件
 * 
 * 这个文件声明了游戏中常用的工具函数，包括：
 * - 数学运算（向量、随机数等）
 * - 碰撞检测
 * - 其他辅助函数
 * 
 * 💡 初学者提示：
 * 这个文件只有函数的"声明"（告诉编译器函数长什么样），
 * 实际的函数"实现"（具体怎么做）在 util.cpp 文件中。
 */

#pragma once

#include "type.h"
#include <cmath>

/* ============================================================================
 * 数学工具函数
 * ============================================================================
 */

/**
 * @brief 计算向量的长度
 * 
 * @param v 要计算长度的向量
 * @return 向量的长度（总是非负数）
 * 
 * 计算公式：length = √(x² + y²)
 * 
 * 使用示例：
 * ```cpp
 * Vector2 v = {3.0, 4.0};
 * double len = Length(v);  // len = 5.0
 * ```
 */
double Length(Vector2 v);

/**
 * @brief 归一化向量（变成长度为 1 的向量）
 * 
 * @param v 要归一化的向量
 * @return 归一化后的向量（长度为 1，方向不变）
 * 
 * 如果输入向量长度为 0，返回 (0, 0)
 * 
 * 用途：
 * - 保证所有方向的移动速度一致
 * - 获取纯方向向量（不关心大小）
 * 
 * 使用示例：
 * ```cpp
 * // WASD 移动
 * Vector2 direction = {0, 0};
 * if (GetKeyDown('W')) direction.y -= 1;
 * if (GetKeyDown('D')) direction.x += 1;
 * 
 * // 如果同时按 W 和 D（右上方），长度是 √2
 * // 归一化后长度变成 1，但方向不变
 * direction = Normalize(direction);
 * 
 * // 现在所有方向速度一致
 * player->x += direction.x * speed * deltaTime;
 * ```
 */
Vector2 Normalize(Vector2 v);

/**
 * @brief 向量点乘
 * 
 * @param v1 第一个向量
 * @param v2 第二个向量
 * @return 点乘结果
 * 
 * 计算公式：result = v1.x * v2.x + v1.y * v2.y
 * 
 * 用途：
 * - 判断两个向量是否垂直（点乘为 0）
 * - 计算投影长度
 * - 判断方向相似度
 */
double Dot(Vector2 v1, Vector2 v2);

/**
 * @brief 计算两点之间的距离
 * 
 * @param p1 第一个点
 * @param p2 第二个点
 * @return 两点之间的距离
 * 
 * 计算公式：distance = √((x2-x1)² + (y2-y1)²)
 * 
 * 使用示例：
 * ```cpp
 * Vector2 playerPos = {100, 200};
 * Vector2 enemyPos = {150, 250};
 * double dist = Distance(playerPos, enemyPos);
 * 
 * if (dist < 100)
 * {
 *     // 玩家和敌人距离小于 100，触发某些事件
 * }
 * ```
 */
double Distance(Vector2 p1, Vector2 p2);

/**
 * @brief 限制数值在指定范围内
 * 
 * @param value 要限制的值
 * @param min 最小值
 * @param max 最大值
 * @return 限制后的值
 * 
 * 如果 value < min，返回 min
 * 如果 value > max，返回 max
 * 否则返回 value
 * 
 * 使用示例：
 * ```cpp
 * // 限制玩家在屏幕内
 * player->x = Clamp(player->x, 0, GAME_WIDTH - player->width);
 * player->y = Clamp(player->y, 0, GAME_HEIGHT - player->height);
 * ```
 */
double Clamp(double value, double min, double max);

/**
 * @brief 线性插值
 * 
 * @param a 起始值
 * @param b 结束值
 * @param t 插值参数（0 到 1）
 * @return 插值结果
 * 
 * 计算公式：result = a + (b - a) * t
 * 当 t = 0 时，返回 a
 * 当 t = 1 时，返回 b
 * 当 t = 0.5 时，返回 a 和 b 的中间值
 * 
 * 用途：
 * - 平滑过渡
 * - 动画效果
 * - 相机跟随
 */
double Lerp(double a, double b, double t);

/* ============================================================================
 * 随机数工具函数
 * ============================================================================
 */

/**
 * @brief 生成指定范围内的随机整数
 * 
 * @param min 最小值（包含）
 * @param max 最大值（包含）
 * @return [min, max] 范围内的随机整数
 * 
 * 使用示例：
 * ```cpp
 * // 生成 1-6 的随机数（模拟骰子）
 * int dice = GetRandomInt(1, 6);
 * 
 * // 随机选择敌人类型（0, 1, 2）
 * int enemyType = GetRandomInt(0, 2);
 * ```
 */
int GetRandomInt(int min, int max);

/**
 * @brief 生成指定范围内的随机小数
 * 
 * @param min 最小值
 * @param max 最大值
 * @return [min, max] 范围内的随机小数
 * 
 * 使用示例：
 * ```cpp
 * // 在屏幕宽度范围内随机生成 X 坐标
 * double randomX = GetRandomDouble(0, GAME_WIDTH - ENEMY_WIDTH);
 * 
 * // 随机速度（200-300）
 * double speed = GetRandomDouble(200, 300);
 * ```
 */
double GetRandomDouble(double min, double max);

/**
 * @brief 生成随机布尔值
 * 
 * @return true 或 false（各 50% 概率）
 * 
 * 使用示例：
 * ```cpp
 * // 随机决定敌人的移动方向
 * if (GetRandomBool())
 * {
 *     enemy->moveLeft = true;
 * }
 * else
 * {
 *     enemy->moveLeft = false;
 * }
 * ```
 */
bool GetRandomBool();

/* ============================================================================
 * 碰撞检测函数
 * ============================================================================
 */

/**
 * @brief 检测两个矩形是否碰撞
 * 
 * @param rect1 第一个矩形
 * @param rect2 第二个矩形
 * @return true 表示碰撞，false 表示未碰撞
 * 
 * 碰撞条件：
 * - rect1 的右边 > rect2 的左边
 * - rect1 的左边 < rect2 的右边
 * - rect1 的下边 > rect2 的上边
 * - rect1 的上边 < rect2 的下边
 * 
 * 使用示例：
 * ```cpp
 * // 检测玩家与敌人的碰撞
 * Rect playerRect = {player->x, player->x + player->width,
 *                    player->y, player->y + player->height};
 * Rect enemyRect = {enemy->x, enemy->x + enemy->width,
 *                   enemy->y, enemy->y + enemy->height};
 * 
 * if (IsRectRectCollision(playerRect, enemyRect))
 * {
 *     // 发生碰撞！
 *     player->health--;
 * }
 * ```
 */
bool IsRectRectCollision(Rect rect1, Rect rect2);

/**
 * @brief 检测矩形与圆形是否碰撞
 * 
 * @param rect 矩形
 * @param circle 圆形
 * @return true 表示碰撞，false 表示未碰撞
 * 
 * 算法：
 * 1. 找到矩形上距离圆心最近的点
 * 2. 计算这个点到圆心的距离
 * 3. 如果距离小于半径，则碰撞
 * 
 * 使用示例：
 * ```cpp
 * // 检测子弹（圆形）与敌人（矩形）的碰撞
 * Rect enemyRect = {...};
 * Circle bulletCircle = {bullet->position, bullet->radius};
 * 
 * if (IsRectCircleCollision(enemyRect, bulletCircle))
 * {
 *     // 子弹击中敌人！
 *     enemy->health -= bullet->damage;
 * }
 * ```
 */
bool IsRectCircleCollision(Rect rect, Circle circle);

/**
 * @brief 检测两个圆形是否碰撞
 * 
 * @param circle1 第一个圆形
 * @param circle2 第二个圆形
 * @return true 表示碰撞，false 表示未碰撞
 * 
 * 碰撞条件：
 * 两个圆心之间的距离 <= 两个半径之和
 * 
 * 使用示例：
 * ```cpp
 * Circle bullet1 = {pos1, 5};
 * Circle bullet2 = {pos2, 5};
 * 
 * if (IsCircleCircleCollision(bullet1, bullet2))
 * {
 *     // 两颗子弹相撞（虽然这在游戏中不常见）
 * }
 * ```
 */
bool IsCircleCircleCollision(Circle circle1, Circle circle2);

/**
 * @brief 检测点是否在矩形内
 * 
 * @param point 点的坐标
 * @param rect 矩形
 * @return true 表示点在矩形内，false 表示不在
 * 
 * 使用示例：
 * ```cpp
 * Vector2 mousePos = {GetMouseX(), GetMouseY()};
 * Rect buttonRect = {100, 300, 200, 300};
 * 
 * if (IsPointInRect(mousePos, buttonRect))
 * {
 *     // 鼠标在按钮上
 * }
 * ```
 */
bool IsPointInRect(Vector2 point, Rect rect);

/**
 * @brief 检测点是否在圆形内
 * 
 * @param point 点的坐标
 * @param circle 圆形
 * @return true 表示点在圆形内，false 表示不在
 * 
 * 判断方法：点到圆心的距离 <= 半径
 */
bool IsPointInCircle(Vector2 point, Circle circle);

/* ============================================================================
 * 坐标转换函数
 * ============================================================================
 */

/**
 * @brief 从游戏对象创建碰撞矩形
 * 
 * @param position 对象位置（左上角）
 * @param width 对象宽度
 * @param height 对象高度
 * @return 碰撞矩形
 * 
 * 这是一个便捷函数，快速从游戏对象创建碰撞矩形
 * 
 * 使用示例：
 * ```cpp
 * Rect playerRect = CreateRect(player->position, player->width, player->height);
 * ```
 */
Rect CreateRect(Vector2 position, double width, double height);

/**
 * @brief 从游戏对象创建碰撞圆形
 * 
 * @param center 圆心坐标
 * @param radius 半径
 * @return 碰撞圆形
 */
Circle CreateCircle(Vector2 center, double radius);

/* ============================================================================
 * 调试辅助函数
 * ============================================================================
 */

/**
 * @brief 输出日志信息到状态栏
 * 
 * @param statusBarIndex 状态栏索引（0 或 1）
 * @param format 格式化字符串（类似 printf）
 * @param ... 可变参数
 * 
 * 使用示例：
 * ```cpp
 * Log(1, TEXT("玩家位置: x=%f, y=%f"), player->x, player->y);
 * Log(1, TEXT("敌人数量: %d"), enemies.size());
 * Log(1, TEXT("当前 FPS: %d"), fps);
 * ```
 * 
 * 💡 提示：
 * - 状态栏 0 通常用于显示 FPS
 * - 状态栏 1 用于显示其他信息
 * - 字符串必须使用 TEXT 宏包围
 */
void Log(int statusBarIndex, const TCHAR* format, ...);

/* ============================================================================
 * 字符串处理函数
 * ============================================================================
 */

/**
 * @brief 格式化输出到字符串
 * 
 * @param buffer 输出缓冲区
 * @param bufferSize 缓冲区大小
 * @param format 格式化字符串
 * @param ... 可变参数
 * 
 * 使用示例：
 * ```cpp
 * TCHAR buffer[128];
 * FormatString(buffer, 128, TEXT("分数: %d, 生命: %d"), 
 *              score, health);
 * 
 * // 然后可以用 DrawText 显示
 * DrawText(hdc, buffer, -1, &rect, DT_CENTER);
 * ```
 */
void FormatString(TCHAR* buffer, int bufferSize, const TCHAR* format, ...);

/* ============================================================================
 * 使用建议
 * ============================================================================
 * 
 * 1. 优先使用这些工具函数，而不是自己重新实现
 *    ✅ 好：double len = Length(v);
 *    ❌ 差：double len = sqrt(v.x*v.x + v.y*v.y);
 * 
 * 2. 碰撞检测时选择合适的形状
 *    - 矩形：适合方形物体（飞机、敌人）
 *    - 圆形：适合圆形物体（子弹、爆炸范围）
 *    - 点：适合精确检测（鼠标点击）
 * 
 * 3. 性能考虑
 *    - Distance 函数涉及开方，比较慢
 *    - 如果只是比较距离，可以比较距离的平方（避免开方）
 *    - 示例：
 *      double distSq = (dx*dx + dy*dy);  // 距离的平方
 *      if (distSq < range*range)  // 比较平方值
 * 
 * 4. 调试时善用 Log 函数
 *    - 输出关键变量的值
 *    - 检查函数是否被调用
 *    - 验证逻辑是否正确
 * 
 * ============================================================================
 */
