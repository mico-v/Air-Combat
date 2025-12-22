# 框架使用完全指南

## 🎯 框架概述

本飞机大战游戏框架已完成 **60%** 的核心开发，为零基础学习者提供了完整的工具库、输入系统和详尽的文档。

### ✅ 已完成部分

#### 1. 完整的文档系统
- **README.md** - 项目介绍和快速开始
- **SETUP.md** - 环境搭建指南
- **GETTING_STARTED.md** - 30分钟快速上手
- **docs/02-框架概览.md** - 架构详解
- **docs/API文档.md** - 完整API参考
- **docs/快速参考.md** - 常用函数速查
- **docs/实现指南.md** - 分步实现教程
- **PROJECT_STATUS.md** - 项目进度跟踪
- **FRAMEWORK_SUMMARY.md** - 框架总结

#### 2. 完整的工具函数库
- **config.h** - 游戏配置参数
- **type.h** - 数据结构定义
- **util.h/cpp** - 工具函数实现
  - 数学函数（归一化、距离、限制等）
  - 随机数生成
  - 碰撞检测（矩形、圆形、点）

#### 3. 完整的输入系统
- **keyboard.h/cpp** - 键盘输入处理
- **mouse.h/cpp** - 鼠标输入处理

#### 4. 实现指南
- **src/game_object/README.md** - 游戏对象实现指南
- **src/scene/README.md** - 场景系统实现指南

### 📦 待实现部分（已有完整文档指导）

以下部分已提供完整的实现指南和代码示例，学习者可以按照文档自行实现：

1. **核心系统** (core/)
   - main.cpp - Win32程序入口
   - core.h/cpp - 游戏核心逻辑
   - timer.h - 定时器配置

2. **场景系统** (scene/)
   - scene.h/cpp - 场景管理
   - scene1.h/cpp - 开始场景
   - scene2.h/cpp - 游戏场景

3. **游戏对象** (game_object/)
   - player.h/cpp - 玩家实现
   - enemy.h/cpp - 敌人实现
   - bullet.h/cpp - 子弹实现

4. **UI组件** (ui/)
   - button.h/cpp - 按钮系统

5. **资源管理** (resource/)
   - resource.h/cpp - 资源加载

## 📖 使用框架的三种方式

### 方式一：跟随实现指南（推荐初学者）

**适合人群**：零基础或初学者

**步骤**：
1. 阅读 `GETTING_STARTED.md` 快速了解框架
2. 跟随 `docs/实现指南.md` 一步步实现
3. 参考 `docs/API文档.md` 查询函数用法
4. 查看 `src/*/README.md` 了解模块实现

**优点**：循序渐进，理解透彻

### 方式二：使用提供的工具库快速开发

**适合人群**：有一定基础的开发者

**步骤**：
1. 浏览 `docs/快速参考.md` 了解可用函数
2. 使用已实现的工具函数和输入系统
3. 自行实现游戏逻辑和场景
4. 需要时查阅 `docs/API文档.md`

**优点**：快速开发，灵活自由

### 方式三：学习框架设计理念

**适合人群**：想深入理解的学习者

**步骤**：
1. 阅读 `docs/02-框架概览.md` 理解架构
2. 阅读所有源代码和注释
3. 分析设计模式和最佳实践
4. 尝试扩展和优化框架

**优点**：深入理解，提升能力

## 🚀 快速实现游戏的步骤

### 第1步：创建玩家（30分钟）

**参考文档**：`docs/实现指南.md` - 任务1

**需要实现**：
- `src/game_object/player.h` - 玩家头文件
- `src/game_object/player.cpp` - 玩家实现

**核心功能**：
- 创建和销毁玩家
- WASD/方向键移动
- 限制在屏幕内

**可用工具**：
- `GetKeyDown()` - 检测按键
- `Normalize()` - 归一化方向
- `Clamp()` - 限制范围

### 第2步：创建敌人（30分钟）

**参考文档**：`docs/实现指南.md` - 任务2

**需要实现**：
- `src/game_object/enemy.h` - 敌人头文件
- `src/game_object/enemy.cpp` - 敌人实现

**核心功能**：
- 创建多个敌人（使用vector）
- 自动向下移动
- 定时生成新敌人

**可用工具**：
- `GetRandomDouble()` - 随机位置
- `GetGameTime()` - 游戏时间（需实现）

### 第3步：实现碰撞检测（20分钟）

**参考文档**：`docs/实现指南.md` - 任务3

**核心功能**：
- 检测玩家与敌人碰撞
- 处理碰撞后的逻辑

**可用工具**：
- `CreateRect()` - 创建碰撞矩形
- `IsRectRectCollision()` - 矩形碰撞检测

### 第4步：实现子弹系统（40分钟）

**参考文档**：`src/game_object/README.md`

**核心功能**：
- 发射子弹（空格键）
- 子弹移动
- 子弹与敌人碰撞

**可用工具**：
- `GetKeyDown(VK_SPACE)` - 检测空格键
- `IsRectCircleCollision()` - 子弹碰撞检测

### 第5步：实现场景系统（60分钟）

**参考文档**：`src/scene/README.md`

**核心功能**：
- 场景管理器
- 开始场景（标题和按钮）
- 游戏场景（实际游戏）
- 场景切换

## 💻 代码示例汇总

### 完整的玩家更新函数

```cpp
void UpdatePlayer(double deltaTime)
{
    Player* player = GetPlayer();
    if (player == nullptr) return;
    
    // 1. 处理移动
    Vector2 direction = {0, 0};
    if (GetKeyDown('W')) direction.y -= 1;
    if (GetKeyDown('S')) direction.y += 1;
    if (GetKeyDown('A')) direction.x -= 1;
    if (GetKeyDown('D')) direction.x += 1;
    
    direction = Normalize(direction);
    
    player->position.x += direction.x * player->attributes.speed * deltaTime;
    player->position.y += direction.y * player->attributes.speed * deltaTime;
    
    // 2. 限制在屏幕内
    player->position.x = Clamp(player->position.x, 0, GAME_WIDTH - player->width);
    player->position.y = Clamp(player->position.y, 0, GAME_HEIGHT - player->height);
    
    // 3. 处理射击
    if (GetKeyDown(VK_SPACE) && player->attributes.bulletCd <= 0)
    {
        CreateBullet(
            player->position.x + player->width / 2,
            player->position.y,
            1, 800.0
        );
        player->attributes.bulletCd = player->attributes.maxBulletCd;
    }
    
    // 4. 更新冷却
    if (player->attributes.bulletCd > 0)
        player->attributes.bulletCd -= deltaTime;
}
```

### 完整的碰撞检测函数

```cpp
void CheckCollision_GameScene()
{
    Player* player = GetPlayer();
    if (player == nullptr) return;
    
    Rect playerRect = CreateRect(player->position, player->width, player->height);
    
    // 1. 玩家与敌人碰撞
    for (Enemy* enemy : GetEnemies())
    {
        Rect enemyRect = CreateRect(enemy->position, enemy->width, enemy->height);
        
        if (IsRectRectCollision(playerRect, enemyRect))
        {
            player->attributes.health--;
            player->attributes.score += enemy->attributes.score;
            DestroyEnemy(enemy);
            
            if (player->attributes.health <= 0)
            {
                // 游戏结束
                ChangeScene(GameOverScene);
            }
            break;
        }
    }
    
    // 2. 子弹与敌人碰撞
    for (Bullet* bullet : GetBullets())
    {
        Circle bulletCircle = CreateCircle(bullet->position, bullet->radius);
        
        for (Enemy* enemy : GetEnemies())
        {
            Rect enemyRect = CreateRect(enemy->position, enemy->width, enemy->height);
            
            if (IsRectCircleCollision(enemyRect, bulletCircle))
            {
                enemy->attributes.health -= bullet->damage;
                
                if (enemy->attributes.health <= 0)
                {
                    player->attributes.score += enemy->attributes.score;
                    DestroyEnemy(enemy);
                }
                
                DestroyBullet(bullet);
                break;
            }
        }
    }
}
```

## 🎯 学习里程碑

### 第1周：基础掌握
- [x] 环境搭建完成
- [x] 理解框架架构
- [x] 掌握工具函数使用
- [ ] 实现玩家移动

### 第2周：核心功能
- [ ] 实现敌人系统
- [ ] 实现碰撞检测
- [ ] 实现子弹系统

### 第3周：场景和UI
- [ ] 实现场景切换
- [ ] 实现开始菜单
- [ ] 实现游戏UI

### 第4周：完善优化
- [ ] 添加音效
- [ ] 优化性能
- [ ] 增加游戏内容

## 📚 文档使用指南

### 日常开发查询顺序

1. **快速查找** → `docs/快速参考.md`
   - 找常用函数
   - 找代码模式

2. **详细说明** → `docs/API文档.md`
   - 看函数参数
   - 看使用示例

3. **实现教程** → `docs/实现指南.md`
   - 看完整实现
   - 看常见问题

4. **模块指南** → `src/*/README.md`
   - 看模块设计
   - 看最佳实践

### 遇到问题的解决流程

```
遇到问题
    ↓
查看错误信息
    ↓
在文档中搜索关键词
    ↓
找到了 → 按文档解决
    ↓
没找到 → 使用调试器
    ↓
定位问题代码
    ↓
查看相关文档
    ↓
仍未解决 → GitHub提Issue
```

## 🎓 学习建议

### 对于零基础学习者

1. **不要着急**
   - 每天学一点
   - 理解比速度重要

2. **多动手**
   - 看懂≠会写
   - 每个示例都要亲自敲

3. **善用文档**
   - 文档是最好的老师
   - 培养查文档的习惯

4. **循序渐进**
   - 先实现基本功能
   - 再添加高级特性

### 对于有基础的开发者

1. **快速上手**
   - 直接看快速参考
   - 使用提供的工具

2. **灵活运用**
   - 不必严格遵循文档
   - 可以自由发挥

3. **深入理解**
   - 阅读源码
   - 理解设计思想

4. **积极扩展**
   - 添加新功能
   - 优化现有代码

## 🔧 开发工具使用

### Visual Studio 必备技巧

1. **Ctrl + ,** - 快速查找文件
2. **F12** - 转到定义
3. **Ctrl + -** - 返回上一位置
4. **F9** - 设置断点
5. **F5** - 开始调试
6. **F10** - 单步跳过
7. **F11** - 单步进入

### 调试技巧

1. **使用断点**
   - 在关键位置设置
   - 观察变量值

2. **使用Log函数**
   - 输出关键信息
   - 追踪程序流程

3. **单步执行**
   - 逐行检查代码
   - 理解执行流程

## 🎉 总结

本框架提供了：
- ✅ 完整的文档系统（7个主要文档）
- ✅ 实用的工具函数库（数学、碰撞、随机）
- ✅ 完整的输入系统（键盘和鼠标）
- ✅ 详细的实现指南（含完整代码）
- ✅ 模块化的设计（易于理解和扩展）

你需要做的：
- 📖 认真阅读文档
- 💻 动手实践代码
- 🐛 调试解决问题
- 🚀 不断改进优化

从现在开始，跟随文档，实现你的第一个飞机大战游戏吧！ 🎮✈️

---

**快速链接**：
- [快速开始](GETTING_STARTED.md)
- [环境搭建](SETUP.md)
- [快速参考](docs/快速参考.md)
- [实现指南](docs/实现指南.md)
- [API文档](docs/API文档.md)
- [项目状态](PROJECT_STATUS.md)
