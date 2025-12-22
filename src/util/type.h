/**
 * @file type.h
 * @brief 数据类型定义文件
 * 
 * 这个文件定义了游戏中使用的各种数据结构和类型。
 * 包括：
 * - 基础数学类型（向量、矩形、圆形）
 * - 游戏对象属性
 * - 其他自定义类型
 * 
 * 💡 初学者提示：
 * 结构体(struct)就像一个"容器"，可以把相关的数据组织在一起。
 * 比如，Vector2 结构体把 x 和 y 坐标放在一起，表示一个点或向量。
 */

#pragma once

/* ============================================================================
 * 基础数学类型
 * ============================================================================
 */

/**
 * @brief 二维向量结构体
 * 
 * 用途：
 * 1. 表示位置坐标 (x, y)
 * 2. 表示移动方向
 * 3. 表示速度向量
 * 
 * 使用示例：
 * ```cpp
 * // 创建一个向量表示位置
 * Vector2 position = {100.0, 200.0};  // x=100, y=200
 * 
 * // 创建一个向量表示向右的方向
 * Vector2 direction = {1.0, 0.0};     // 向右
 * 
 * // 修改向量
 * position.x += 10;  // x 增加 10
 * position.y -= 5;   // y 减少 5
 * ```
 */
struct Vector2
{
    double x;  // X 坐标（横向，向右为正）
    double y;  // Y 坐标（纵向，向下为正）
    
    /**
     * 💡 坐标系说明：
     * 在屏幕坐标系中：
     * - 原点 (0, 0) 在左上角
     * - X 轴向右递增
     * - Y 轴向下递增
     * 
     *  (0,0) ────────→ X
     *    │
     *    │
     *    │
     *    ↓
     *    Y
     */
};

/**
 * @brief 矩形结构体
 * 
 * 用途：
 * 1. 表示游戏对象的边界（用于碰撞检测）
 * 2. 表示一个矩形区域
 * 
 * 使用示例：
 * ```cpp
 * // 创建一个矩形
 * Rect rect;
 * rect.left = 100;    // 左边界
 * rect.right = 200;   // 右边界
 * rect.top = 50;      // 上边界
 * rect.bottom = 150;  // 下边界
 * 
 * // 计算矩形的宽度和高度
 * double width = rect.right - rect.left;    // 100
 * double height = rect.bottom - rect.top;   // 100
 * ```
 * 
 * 💡 注意：
 * - left 必须小于 right
 * - top 必须小于 bottom
 */
struct Rect
{
    double left;    // 左边界的 X 坐标
    double right;   // 右边界的 X 坐标
    double top;     // 上边界的 Y 坐标
    double bottom;  // 下边界的 Y 坐标
    
    /**
     * 矩形示意图：
     * 
     *        top
     *    ┌────────┐
     *    │        │
     * left        right
     *    │        │
     *    └────────┘
     *       bottom
     */
};

/**
 * @brief 圆形结构体
 * 
 * 用途：
 * 1. 表示圆形游戏对象（如子弹）
 * 2. 用于圆形碰撞检测
 * 
 * 使用示例：
 * ```cpp
 * // 创建一个圆形
 * Circle circle;
 * circle.center.x = 100;  // 圆心 X 坐标
 * circle.center.y = 200;  // 圆心 Y 坐标
 * circle.radius = 10;     // 半径
 * 
 * // 判断点是否在圆内
 * Vector2 point = {105, 205};
 * double dx = point.x - circle.center.x;
 * double dy = point.y - circle.center.y;
 * double distance = sqrt(dx*dx + dy*dy);
 * if (distance <= circle.radius)
 * {
 *     // 点在圆内
 * }
 * ```
 */
struct Circle
{
    Vector2 center;  // 圆心坐标
    double radius;   // 半径
    
    /**
     * 圆形示意图：
     * 
     *         ╱─╲
     *       ╱  *  ╲    * = center (圆心)
     *      │   │   │   │ = radius (半径)
     *       ╲  │  ╱
     *         ╲─╱
     */
};

/* ============================================================================
 * 游戏对象属性
 * ============================================================================
 */

/**
 * @brief 游戏对象属性结构体
 * 
 * 这个结构体包含了游戏对象的各种属性，如生命值、分数、速度等。
 * 
 * 用途：
 * - 存储玩家的属性（生命、分数、速度等）
 * - 存储敌人的属性
 * - 其他需要这些属性的游戏对象
 * 
 * 使用示例：
 * ```cpp
 * // 创建玩家属性
 * Attribute playerAttr;
 * playerAttr.health = 3;          // 3 条命
 * playerAttr.score = 0;           // 初始分数为 0
 * playerAttr.speed = 500.0;       // 移动速度 500 像素/秒
 * playerAttr.maxBulletCd = 0.1;   // 子弹冷却时间 0.1 秒
 * playerAttr.bulletCd = 0.0;      // 当前冷却为 0
 * 
 * // 在游戏中使用
 * if (playerAttr.bulletCd <= 0)
 * {
 *     // 可以发射子弹
 *     FireBullet();
 *     playerAttr.bulletCd = playerAttr.maxBulletCd;
 * }
 * 
 * // 每帧更新
 * playerAttr.bulletCd -= deltaTime;
 * ```
 */
struct Attribute
{
    // 生命值
    // - 对于玩家：生命值为 0 时游戏结束
    // - 对于敌人：生命值为 0 时被摧毁
    int health;
    
    // 分数
    // - 对于玩家：当前获得的总分数
    // - 对于敌人：击败后玩家获得的分数
    int score;
    
    // 移动速度（单位：像素/秒）
    // 💡 提示：配合 deltaTime 使用才能保证匀速运动
    // 公式：距离 = 速度 × 时间
    double speed;
    
    // 最大子弹冷却时间（单位：秒）
    // 表示两次射击之间至少要间隔多长时间
    // 💡 例如：0.1 秒表示每秒最多射击 10 次
    double maxBulletCd;
    
    // 当前子弹冷却时间（单位：秒）
    // 倒计时变量，从 maxBulletCd 开始递减
    // 当 bulletCd <= 0 时，可以发射子弹
    double bulletCd;
    
    /**
     * 💡 冷却系统工作原理：
     * 
     * 1. 初始化：bulletCd = 0（可以立即射击）
     * 
     * 2. 发射子弹时：
     *    if (bulletCd <= 0)
     *    {
     *        // 发射子弹
     *        bulletCd = maxBulletCd;  // 重置冷却
     *    }
     * 
     * 3. 每帧更新（在 Update 函数中）：
     *    bulletCd -= deltaTime;  // 冷却时间递减
     *    if (bulletCd < 0) bulletCd = 0;
     * 
     * 这样就实现了射击间隔控制！
     */
};

/* ============================================================================
 * 其他类型定义
 * ============================================================================
 */

/**
 * @brief 游戏对象基类结构体
 * 
 * 这是一个通用的游戏对象结构，包含了所有游戏对象都需要的基本信息。
 * 
 * 💡 继承概念：
 * 虽然 C 语言没有继承，但我们可以在其他结构体的开头包含这个结构体，
 * 从而"继承"这些基本属性。
 * 
 * 使用示例：
 * ```cpp
 * // 定义玩家结构体
 * struct Player
 * {
 *     // 基本信息（从 GameObject "继承"）
 *     Vector2 position;
 *     double width;
 *     double height;
 *     Attribute attributes;
 *     
 *     // 玩家特有的信息
 *     int frameIndex;  // 动画帧索引
 * };
 * ```
 */
struct GameObject
{
    Vector2 position;     // 位置（左上角坐标）
    double width;         // 宽度
    double height;        // 高度
    Attribute attributes; // 游戏属性
};

/**
 * @brief 颜色结构体（RGB 格式）
 * 
 * 表示一个颜色，使用红(R)、绿(G)、蓝(B)三个分量。
 * 
 * 💡 RGB 颜色说明：
 * - 每个分量的范围是 0-255
 * - (255, 0, 0) = 纯红色
 * - (0, 255, 0) = 纯绿色
 * - (0, 0, 255) = 纯蓝色
 * - (255, 255, 255) = 白色
 * - (0, 0, 0) = 黑色
 * - (128, 128, 128) = 灰色
 * 
 * 使用示例：
 * ```cpp
 * Color red = {255, 0, 0};
 * Color white = {255, 255, 255};
 * ```
 */
struct Color
{
    unsigned char r;  // 红色分量 (0-255)
    unsigned char g;  // 绿色分量 (0-255)
    unsigned char b;  // 蓝色分量 (0-255)
};

/* ============================================================================
 * 方向枚举
 * ============================================================================
 */

/**
 * @brief 方向枚举
 * 
 * 用于表示四个基本方向。
 * 
 * 使用示例：
 * ```cpp
 * Direction dir = DIR_UP;
 * 
 * switch (dir)
 * {
 * case DIR_UP:
 *     // 向上移动
 *     player->y -= speed * deltaTime;
 *     break;
 * case DIR_DOWN:
 *     // 向下移动
 *     player->y += speed * deltaTime;
 *     break;
 * // ...
 * }
 * ```
 */
enum Direction
{
    DIR_UP = 0,     // 上
    DIR_DOWN = 1,   // 下
    DIR_LEFT = 2,   // 左
    DIR_RIGHT = 3   // 右
};

/* ============================================================================
 * 常用类型别名
 * ============================================================================
 */

// 时间类型（单位：秒）
typedef double GameTime;

// ID 类型（用于标识游戏对象）
typedef int ObjectId;

/* ============================================================================
 * 使用建议
 * ============================================================================
 * 
 * 1. 优先使用结构体来组织相关数据
 *    ✅ 好：struct Player { Vector2 pos; int health; };
 *    ❌ 差：double playerX, playerY; int playerHealth;
 * 
 * 2. 使用有意义的变量名
 *    ✅ 好：Vector2 playerPosition;
 *    ❌ 差：Vector2 v1;
 * 
 * 3. 初始化结构体的方法：
 *    Vector2 pos = {0, 0};  // 推荐：列表初始化
 *    或
 *    Vector2 pos;
 *    pos.x = 0;
 *    pos.y = 0;
 * 
 * 4. 传递结构体时使用指针（提高效率）：
 *    ✅ 好：void UpdatePlayer(Player* player);
 *    ❌ 差：void UpdatePlayer(Player player);  // 会复制整个结构体
 * 
 * ============================================================================
 */
