# 代码阅读指南

> 适合 C++ 新手的 src/ 目录阅读顺序

## 推荐阅读路径

### 第一步：理解数据结构（5分钟）

**[src/util/type.h](src/util/type.h)** - 从这里开始
- `Vector2` - 二维坐标/向量（x, y）
- `Rect` - 矩形（位置 + 宽高）
- `Circle` - 圆形（圆心 + 半径）
- `Attribute` - 游戏对象属性（位置、速度、大小）
- `Color` - RGBA 颜色定义

**为什么先看这个？** 这些是整个游戏的"积木"，后面所有代码都会用到。

### 第二步：游戏配置参数（3分钟）

**[src/util/config.h](src/util/config.h)**
- 窗口大小、帧率
- 玩家/敌人/子弹的速度、大小
- 敌人生成间隔

**学习要点：** 用 `#define` 定义常量是 C/C++ 的传统做法，修改这些值可以调整游戏难度。

### 第三步：理解游戏循环（10分钟）

**[src/main.cpp](src/main.cpp)** - 程序入口
```
初始化 SDL → 游戏循环 → 清理资源
      ↓
  每帧执行：处理输入 → 更新逻辑 → 渲染画面
```

**关键概念：**
- `deltaTime` - 上一帧耗时，用于让游戏速度不受帧率影响
- 典型的游戏主循环结构

### 第四步：输入系统（8分钟）

**[src/input/input.h](src/input/input.h) + [input.cpp](src/input/input.cpp)**
- `UpdateInput()` - 每帧更新键盘/鼠标状态
- `IsKeyDown()` - 查询某个键是否按下
- `GetMousePos()` - 获取鼠标坐标

**设计优点：** 游戏逻辑不直接处理 SDL 事件，只需要问"空格键按下了吗？"

### 第五步：游戏对象（各15分钟）

**按这个顺序看：**

1. **[src/game_object/player.h](src/game_object/player.h) + [player.cpp](src/game_object/player.cpp)**
   - `CreatePlayer()` - 初始化玩家
   - `UpdatePlayer()` - 处理移动输入、发射子弹
   - `RenderPlayer()` - 绘制玩家飞机（蓝色矩形）
   - `GetPlayer()` - 获取玩家数据

2. **[src/game_object/bullet.h](src/game_object/bullet.h) + [bullet.cpp](src/game_object/bullet.cpp)**
   - 用 `std::vector` 存储多颗子弹
   - `CreateBullet()` - 在指定位置创建子弹
   - 子弹超出屏幕自动删除（注意 `erase` 用法）

3. **[src/game_object/enemy.h](src/game_object/enemy.h) + [enemy.cpp](src/game_object/enemy.cpp)**
   - 定时生成敌人（累加器模式）
   - 随机生成位置（`RandomDouble` 函数）
   - 敌机自动下落

**学习要点：**
- **单例模式变体** - 用匿名命名空间 `namespace { }` 内的全局变量存储状态
- **生命周期函数** - Create/Update/Render/Destroy 的统一模式
- **向量操作** - 添加元素、遍历、条件删除

### 第六步：核心游戏逻辑（15分钟）

**[src/core/core.h](src/core/core.h) + [core.cpp](src/core/core.cpp)**
- `UpdateCore()` - 协调所有游戏对象的更新
- `CheckCollision()` - 碰撞检测（玩家撞敌人、子弹打敌人）
- `ResetGame()` - 重置游戏状态

**重点关注：**
- 如何调用各个模块的 Update 函数
- 碰撞检测的逻辑（使用 util.h 的辅助函数）
- `deltaTime` 的限制（防止单帧跳跃过大）

### 第七步：工具函数（10分钟）

**[src/util/util.h](src/util/util.h) + [util.cpp](src/util/util.cpp)**
- `RandomDouble()` - 生成随机浮点数
- `RectCircleCollision()` - 矩形与圆形碰撞检测
- `RenderFilledCircle()` - 自定义圆形绘制（SDL2 没有内置）

**算法亮点：** 圆形绘制使用逐行扫描 + 勾股定理，值得仔细研究。

## 关键 C++ 知识点

| 用到的特性 | 在哪里看 | 说明 |
|-----------|---------|------|
| `struct` POD 类型 | type.h | 纯数据结构，没有成员函数 |
| `constexpr` | type.h, util.cpp | 编译时常量 |
| `#define` 宏 | config.h | 预处理器常量 |
| `namespace` | 各 .cpp 文件 | 匿名命名空间实现私有全局变量 |
| `std::vector` | bullet.cpp, enemy.cpp | 动态数组 |
| `std::array` | input.cpp | 固定大小数组 |
| 引用参数 `&` | 各 Update 函数 | 传递 deltaTime，避免拷贝 |
| Lambda 表达式 | bullet.cpp, enemy.cpp | `erase-remove_if` 惯用法 |

## 调试技巧

1. **修改 config.h** - 改变游戏参数，观察效果
2. **在 Update 函数加 printf** - 打印位置/速度，理解运动逻辑
3. **临时修改颜色** - 在 Render 函数里改颜色，定位渲染问题
4. **单步调试** - 在 main.cpp 的游戏循环打断点

## 进阶练习

- [ ] 添加玩家生命值系统
- [ ] 实现得分显示（需要 SDL_ttf）
- [ ] 增加敌人种类（不同速度/大小）
- [ ] 添加背景滚动效果
- [ ] 玩家子弹冷却时间限制

## 架构设计思考

**为什么用过程式而非面向对象？**
- 代码简单直接（适合学习）
- 避免过度设计
- 性能友好（数据局部性好）

**什么时候该用类？**
- 需要多态行为（不同类型敌人有不同AI）
- 需要封装复杂状态
- 需要资源管理（RAII）

这个项目展示了"简单问题用简单方案"的工程智慧。
