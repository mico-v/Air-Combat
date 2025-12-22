# 游戏对象实现指南

本目录包含游戏中所有对象的实现代码。

## 📁 文件结构

```
game_object/
├── README.md          # 本文件
├── player.h          # 玩家头文件
├── player.cpp        # 玩家实现
├── enemy.h           # 敌人头文件
├── enemy.cpp         # 敌人实现
├── bullet.h          # 子弹头文件
└── bullet.cpp        # 子弹实现
```

## 🎮 游戏对象概述

### 玩家 (Player)
- **数量**: 1 个
- **管理方式**: 单例模式（全局指针）
- **功能**: 接受输入、移动、发射子弹

### 敌人 (Enemy)
- **数量**: 多个
- **管理方式**: vector 容器
- **功能**: 自动移动、定时生成

### 子弹 (Bullet)
- **数量**: 多个
- **管理方式**: vector 容器
- **功能**: 自动移动、碰撞检测

## 📝 实现规范

### 1. 头文件结构

每个对象的头文件应包含：
```cpp
#pragma once
#include "../util/type.h"
#include <windows.h>

// 对象结构体定义
struct ObjectName
{
    Vector2 position;
    double width;
    double height;
    Attribute attributes;
};

// 创建函数
void CreateObject();

// 获取函数
ObjectName* GetObject();  // 单例对象
std::vector<ObjectName*> GetObjects();  // 多个对象

// 更新函数
void UpdateObject(double deltaTime);

// 渲染函数
void RenderObject(HDC hdc_memBuffer, HDC hdc_loadBmp);

// 销毁函数
void DestroyObject();
```

### 2. CPP 文件结构

每个对象的实现文件应包含：
```cpp
#include "object.h"
#include "../util/config.h"
#include "../util/util.h"

// 内部状态存储
static ObjectName* object = nullptr;  // 单例
// 或
static std::vector<ObjectName*> objects;  // 多个

// 实现各个函数...
```

### 3. 生命周期管理

**单例对象（如玩家）：**
```cpp
// 创建
void CreatePlayer()
{
    player = new Player();
    // 初始化...
}

// 销毁
void DestroyPlayer()
{
    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }
}
```

**多实例对象（如敌人）：**
```cpp
// 创建
void CreateEnemy(double x, double y)
{
    Enemy* enemy = new Enemy();
    // 初始化...
    enemies.push_back(enemy);
}

// 销毁单个
void DestroyEnemy(Enemy* enemy)
{
    auto it = std::find(enemies.begin(), enemies.end(), enemy);
    if (it != enemies.end())
    {
        delete *it;
        enemies.erase(it);
    }
}

// 销毁所有
void DestroyEnemies()
{
    for (Enemy* enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}
```

## 🔄 更新循环模式

### 单个对象更新
```cpp
void UpdatePlayer(double deltaTime)
{
    if (player == nullptr) return;
    
    // 1. 处理输入
    // 2. 更新位置
    // 3. 限制边界
    // 4. 更新状态（冷却时间等）
}
```

### 多个对象更新
```cpp
void UpdateEnemies(double deltaTime)
{
    // 1. 定时生成新对象
    // 2. 更新所有对象
    // 3. 删除无效对象
    
    for (size_t i = 0; i < enemies.size(); )
    {
        Enemy* enemy = enemies[i];
        
        // 更新
        enemy->position.y += enemy->speed * deltaTime;
        
        // 检查是否需要删除
        if (enemy->position.y > GAME_HEIGHT + 100)
        {
            delete enemy;
            enemies.erase(enemies.begin() + i);
            // 不要 i++
        }
        else
        {
            i++;  // 只有不删除时才增加索引
        }
    }
}
```

## 🎨 渲染模式

### 简单矩形渲染
```cpp
void RenderObject(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    if (object == nullptr) return;
    
    RECT rect;
    rect.left = (LONG)object->position.x;
    rect.top = (LONG)object->position.y;
    rect.right = (LONG)(object->position.x + object->width);
    rect.bottom = (LONG)(object->position.y + object->height);
    
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
    FillRect(hdc_memBuffer, &rect, brush);
    DeleteObject(brush);
}
```

### 位图渲染
```cpp
void RenderObject(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    if (object == nullptr) return;
    
    // 选择位图到 hdc_loadBmp
    SelectObject(hdc_loadBmp, bmp_Object);
    
    // 透明位图传输
    TransparentBlt(
        hdc_memBuffer,                     // 目标 DC
        (int)object->position.x,           // 目标 X
        (int)object->position.y,           // 目标 Y
        (int)object->width,                // 目标宽度
        (int)object->height,               // 目标高度
        hdc_loadBmp,                       // 源 DC
        0, 0,                              // 源起始位置
        (int)object->width,                // 源宽度
        (int)object->height,               // 源高度
        COLOR_TRANSPARENT                  // 透明色
    );
}
```

## ⚠️ 常见错误

### 1. 内存泄漏
```cpp
// ❌ 错误：创建后忘记删除
void CreateEnemy()
{
    Enemy* enemy = new Enemy();
    enemies.push_back(enemy);
}
// 游戏结束时忘记调用 DestroyEnemies()

// ✅ 正确：在 UnloadScene 中销毁
void UnloadScene()
{
    DestroyPlayer();
    DestroyEnemies();
    DestroyBullets();
}
```

### 2. 遍历时删除
```cpp
// ❌ 错误：删除后继续使用迭代器
for (Enemy* enemy : enemies)
{
    if (enemy->health <= 0)
    {
        DestroyEnemy(enemy);  // 修改了 vector
        // 迭代器失效！
    }
}

// ✅ 正确：使用索引，删除时不递增
for (size_t i = 0; i < enemies.size(); )
{
    if (enemies[i]->health <= 0)
    {
        delete enemies[i];
        enemies.erase(enemies.begin() + i);
        // 不递增 i
    }
    else
    {
        i++;
    }
}
```

### 3. 空指针访问
```cpp
// ❌ 错误：不检查空指针
void UpdatePlayer(double deltaTime)
{
    player->position.x += 10;  // 如果 player 为 nullptr，崩溃！
}

// ✅ 正确：先检查
void UpdatePlayer(double deltaTime)
{
    if (player == nullptr) return;
    player->position.x += 10;
}
```

## 📊 性能优化建议

### 1. 对象池
对于频繁创建销毁的对象（如子弹），可以使用对象池：
```cpp
// 预分配对象，重复使用
static std::vector<Bullet*> bulletPool;
static std::vector<bool> bulletActive;

void InitBulletPool(int size)
{
    for (int i = 0; i < size; i++)
    {
        bulletPool.push_back(new Bullet());
        bulletActive.push_back(false);
    }
}

Bullet* GetInactiveBullet()
{
    for (size_t i = 0; i < bulletActive.size(); i++)
    {
        if (!bulletActive[i])
        {
            bulletActive[i] = true;
            return bulletPool[i];
        }
    }
    return nullptr;  // 池已满
}
```

### 2. 空间分区
对于大量对象的碰撞检测，使用空间分区：
```cpp
// 简单的网格分区
const int GRID_SIZE = 100;
std::vector<Enemy*> grid[GRID_WIDTH][GRID_HEIGHT];

void UpdateGrid()
{
    // 清空网格
    for (int i = 0; i < GRID_WIDTH; i++)
        for (int j = 0; j < GRID_HEIGHT; j++)
            grid[i][j].clear();
    
    // 将敌人分配到网格
    for (Enemy* enemy : enemies)
    {
        int gridX = (int)(enemy->x / GRID_SIZE);
        int gridY = (int)(enemy->y / GRID_SIZE);
        if (gridX >= 0 && gridX < GRID_WIDTH && 
            gridY >= 0 && gridY < GRID_HEIGHT)
        {
            grid[gridX][gridY].push_back(enemy);
        }
    }
}
```

## 🎯 实现检查清单

在完成游戏对象实现后，请确认：

- [ ] 所有对象都有创建和销毁函数
- [ ] 内存管理正确（new 和 delete 配对）
- [ ] 更新函数处理了移动和状态
- [ ] 渲染函数正确绘制对象
- [ ] 边界检查防止对象移出屏幕
- [ ] 使用 deltaTime 保证帧率独立
- [ ] 有适当的注释说明
- [ ] 在场景中正确调用这些函数

## 📚 参考资料

- `docs/API文档.md` - 查看可用的工具函数
- `docs/快速参考.md` - 常用代码模式
- `docs/实现指南.md` - 完整实现教程
- `src/util/type.h` - 数据结构定义
- `src/util/config.h` - 配置参数

---

开始实现你的游戏对象吧！ 🚀
