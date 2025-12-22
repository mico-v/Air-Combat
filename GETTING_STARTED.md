# 快速上手指南

欢迎使用飞机大战游戏框架！本指南将帮助你在 30 分钟内了解并开始使用本框架。

## 🚀 5 分钟快速开始

### 第 1 步：了解项目
打开 `README.md`，快速浏览项目结构和特色。

### 第 2 步：搭建环境
按照 `SETUP.md` 的指引安装 Visual Studio 并配置环境。

### 第 3 步：查看示例
浏览 `docs/快速参考.md`，了解最常用的函数和代码模式。

### 第 4 步：开始实现
跟随 `docs/实现指南.md`，一步步实现你的游戏。

## 📚 文档导航

### 入门文档（必读）
1. **README.md** - 项目概述和学习路径
2. **SETUP.md** - 环境搭建（从安装到运行）
3. **docs/快速参考.md** - 常用函数速查表

### 深入学习
1. **docs/02-框架概览.md** - 理解框架架构
2. **docs/API文档.md** - 完整函数参考
3. **docs/实现指南.md** - 完整实现教程
4. **GuideBook.md** - 原始实验指导书

### 模块指南
1. **src/game_object/README.md** - 游戏对象实现
2. **src/scene/README.md** - 场景系统实现

### 开发参考
1. **PROJECT_STATUS.md** - 项目状态和计划
2. **FRAMEWORK_SUMMARY.md** - 框架总结

## 🎯 学习路径

### 零基础学习者（推荐路径）

#### Week 1: 环境和基础
- [ ] Day 1-2: 阅读 README 和 SETUP，搭建环境
- [ ] Day 3-4: 学习 `docs/02-框架概览.md`，理解架构
- [ ] Day 5-7: 阅读 `src/util/` 中的代码，理解工具函数

#### Week 2: 实践基础功能
- [ ] Day 1-2: 实现玩家对象（参考 `src/game_object/README.md`）
- [ ] Day 3-4: 实现敌人对象
- [ ] Day 5: 实现碰撞检测
- [ ] Day 6-7: 调试和完善

#### Week 3: 完善游戏
- [ ] Day 1-2: 实现子弹系统
- [ ] Day 3-4: 实现场景切换
- [ ] Day 5-6: 添加 UI 元素
- [ ] Day 7: 测试和优化

#### Week 4: 扩展和优化
- [ ] 添加音效
- [ ] 优化性能
- [ ] 增加游戏内容
- [ ] 打磨细节

### 有基础学习者（快速路径）

#### Day 1: 快速上手
- 阅读 `docs/快速参考.md`
- 查看 `src/util/` 源代码
- 理解输入系统 (keyboard/mouse)

#### Day 2-3: 实现核心功能
- 实现玩家、敌人、子弹
- 实现碰撞检测
- 实现基本游戏循环

#### Day 4-5: 完善游戏
- 实现场景系统
- 添加 UI 和音效
- 测试和调试

#### Day 6-7: 优化和扩展
- 性能优化
- 添加新功能
- 代码重构

## 💡 使用技巧

### 1. 如何查找函数？
**场景**: 想知道如何检测按键

**方法**:
1. 打开 `docs/快速参考.md` → 输入系统 → 键盘
2. 或打开 `docs/API文档.md` 搜索 "键盘"
3. 或直接查看 `src/util/keyboard.h`

### 2. 如何理解某个概念？
**场景**: 不理解场景系统是什么

**方法**:
1. 打开 `docs/02-框架概览.md` → 场景系统
2. 或打开 `src/scene/README.md`
3. 或查看 `docs/实现指南.md` 中的场景部分

### 3. 如何实现某个功能？
**场景**: 想实现玩家移动

**方法**:
1. 打开 `docs/实现指南.md` → 任务 1：创建玩家对象
2. 查看完整的代码示例
3. 参考 `src/game_object/README.md` 了解最佳实践

### 4. 遇到错误怎么办？
**步骤**:
1. 查看错误信息
2. 在文档中搜索相关内容
3. 查看"常见问题"部分
4. 使用调试器定位问题
5. 在 GitHub 提 Issue

## 🔧 常用代码片段

### 移动游戏对象
```cpp
// 使用 WASD 移动
Vector2 direction = {0, 0};
if (GetKeyDown('W')) direction.y -= 1;
if (GetKeyDown('S')) direction.y += 1;
if (GetKeyDown('A')) direction.x -= 1;
if (GetKeyDown('D')) direction.x += 1;

direction = Normalize(direction);
object->x += direction.x * speed * deltaTime;
object->y += direction.y * speed * deltaTime;
```

### 检测碰撞
```cpp
Rect rect1 = CreateRect(obj1->position, obj1->width, obj1->height);
Rect rect2 = CreateRect(obj2->position, obj2->width, obj2->height);

if (IsRectRectCollision(rect1, rect2))
{
    // 发生碰撞
}
```

### 定时生成对象
```cpp
static double lastSpawnTime = 0;
double currentTime = GetGameTime();

if (currentTime - lastSpawnTime > 1.0)  // 每秒
{
    CreateEnemy();
    lastSpawnTime = currentTime;
}
```

### 处理鼠标点击
```cpp
if (IsMouseLButtonDown())
{
    int x = GetMouseX();
    int y = GetMouseY();
    // 检测是否点击了按钮...
}
```

## 📋 开发检查清单

### 开始开发前
- [ ] 已阅读 README.md
- [ ] 已完成环境搭建（SETUP.md）
- [ ] 已浏览快速参考（docs/快速参考.md）
- [ ] 了解项目结构

### 实现功能时
- [ ] 理解要实现的功能
- [ ] 查看相关文档和示例
- [ ] 编写代码并添加注释
- [ ] 测试功能是否正常

### 完成功能后
- [ ] 代码可以正常运行
- [ ] 没有编译警告
- [ ] 没有内存泄漏
- [ ] 添加了适当的注释

### 提交代码前
- [ ] 所有功能都已测试
- [ ] 代码格式规范
- [ ] 清理了临时文件
- [ ] 更新了文档（如果需要）

## 🆘 获取帮助

### 自助资源
1. **文档系统**
   - 快速参考 → 日常查询
   - API 文档 → 函数详情
   - 实现指南 → 完整示例

2. **代码示例**
   - 查看 `src/util/` 中的实现
   - 参考各目录的 README.md
   - 查看实现指南中的代码

3. **调试工具**
   - Visual Studio 调试器
   - Log 函数输出
   - 断点和单步执行

### 寻求帮助
1. 在 GitHub 提 Issue
2. 描述清楚问题
3. 附上错误信息和代码
4. 说明尝试过的解决方法

## 🎓 推荐学习顺序

### 第一次学习（完整理解）
1. README.md（项目概述）
2. SETUP.md（环境搭建）
3. docs/02-框架概览.md（架构理解）
4. docs/快速参考.md（常用功能）
5. src/util/*.h（工具函数）
6. docs/实现指南.md（实践开发）
7. src/*/README.md（模块详解）

### 日常开发（按需查询）
1. docs/快速参考.md（速查）
2. docs/API文档.md（详情）
3. src/*/README.md（模块指南）

### 深入学习（提高水平）
1. 阅读所有源代码
2. 理解设计模式
3. 优化性能
4. 扩展功能

## 💪 成功要素

### 1. 循序渐进
不要一次学太多，每天进步一点点。

### 2. 动手实践
看懂不等于会写，必须亲自动手。

### 3. 善用文档
遇到问题先查文档，培养自学能力。

### 4. 调试技能
学会使用调试器，快速定位问题。

### 5. 持续改进
写完不是结束，不断优化代码。

## 🎯 目标设定

### 短期目标（1-2周）
- [ ] 完成环境搭建
- [ ] 理解框架架构
- [ ] 实现基本的玩家移动

### 中期目标（3-4周）
- [ ] 实现完整的游戏循环
- [ ] 实现碰撞检测
- [ ] 完成基本游戏玩法

### 长期目标（1-2个月）
- [ ] 完善所有功能
- [ ] 优化游戏性能
- [ ] 添加特色功能

## 📊 学习进度追踪

### 文档阅读进度
- [ ] README.md
- [ ] SETUP.md
- [ ] docs/快速参考.md
- [ ] docs/02-框架概览.md
- [ ] docs/API文档.md
- [ ] docs/实现指南.md

### 实践进度
- [ ] 环境搭建完成
- [ ] 第一个对象实现
- [ ] 输入处理实现
- [ ] 碰撞检测实现
- [ ] 场景系统实现
- [ ] 完整游戏完成

## 🎉 开始你的游戏开发之旅！

现在你已经了解了如何使用本框架，是时候开始动手了！

**建议的第一步**：
1. 确保环境已搭建好（SETUP.md）
2. 打开 `docs/实现指南.md`
3. 跟着教程实现第一个功能
4. 遇到问题查看对应文档

记住：
- 💻 多动手，少空想
- 📖 善用文档，随时查阅
- 🐛 学会调试，快速定位
- 🚀 持续改进，不断优化

祝你开发愉快，创造出精彩的游戏！ 🎮✈️

---

**快速链接**：
- [环境搭建](SETUP.md)
- [快速参考](docs/快速参考.md)
- [实现指南](docs/实现指南.md)
- [API 文档](docs/API文档.md)
