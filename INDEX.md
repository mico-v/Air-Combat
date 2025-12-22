# 文档索引 - Documentation Index

本文档帮助你快速找到需要的资料。

## 🚀 新手入门路线

如果你是完全的零基础，按以下顺序阅读：

1. **README.md** (5分钟)
   - 了解项目是什么
   - 查看项目特色

2. **SETUP.md** (30分钟)
   - 安装 Visual Studio
   - 配置开发环境

3. **GETTING_STARTED.md** (30分钟)
   - 快速上手指南
   - 了解文档体系

4. **COMPLETE_GUIDE.md** (20分钟)
   - 框架使用完全指南
   - 三种使用方式

5. **docs/实现指南.md** (开始编码)
   - 跟随教程实现功能
   - 一步步完成游戏

## 📚 文档分类

### 入门文档

| 文档 | 用途 | 适合人群 | 阅读时间 |
|------|------|----------|----------|
| [README.md](README.md) | 项目概述 | 所有人 | 5分钟 |
| [SETUP.md](SETUP.md) | 环境搭建 | 初学者 | 30分钟 |
| [GETTING_STARTED.md](GETTING_STARTED.md) | 快速开始 | 所有人 | 30分钟 |
| [COMPLETE_GUIDE.md](COMPLETE_GUIDE.md) | 完全指南 | 所有人 | 20分钟 |

### 技术文档

| 文档 | 用途 | 适合人群 | 阅读时间 |
|------|------|----------|----------|
| [docs/02-框架概览.md](docs/02-框架概览.md) | 理解架构 | 所有人 | 40分钟 |
| [docs/API文档.md](docs/API文档.md) | 函数参考 | 开发时查询 | 按需 |
| [docs/快速参考.md](docs/快速参考.md) | 速查手册 | 开发时查询 | 按需 |
| [docs/实现指南.md](docs/实现指南.md) | 实现教程 | 实现功能时 | 2小时 |

### 模块文档

| 文档 | 用途 | 适合人群 | 阅读时间 |
|------|------|----------|----------|
| [src/game_object/README.md](src/game_object/README.md) | 游戏对象实现 | 实现对象时 | 30分钟 |
| [src/scene/README.md](src/scene/README.md) | 场景系统实现 | 实现场景时 | 30分钟 |

### 项目管理文档

| 文档 | 用途 | 适合人群 | 阅读时间 |
|------|------|----------|----------|
| [PROJECT_STATUS.md](PROJECT_STATUS.md) | 项目进度 | 了解状态 | 5分钟 |
| [FRAMEWORK_SUMMARY.md](FRAMEWORK_SUMMARY.md) | 框架总结 | 全面了解 | 10分钟 |

### 原始教材

| 文档 | 用途 | 适合人群 | 阅读时间 |
|------|------|----------|----------|
| [GuideBook.md](GuideBook.md) | 实验指导书 | 参考资料 | 按需 |

## 🎯 按需求查找文档

### 我想快速开始

1. [GETTING_STARTED.md](GETTING_STARTED.md) - 30分钟快速上手
2. [docs/快速参考.md](docs/快速参考.md) - 常用函数速查

### 我想理解框架

1. [docs/02-框架概览.md](docs/02-框架概览.md) - 架构详解
2. [FRAMEWORK_SUMMARY.md](FRAMEWORK_SUMMARY.md) - 框架总结

### 我想实现功能

1. [docs/实现指南.md](docs/实现指南.md) - 完整教程
2. [src/game_object/README.md](src/game_object/README.md) - 对象实现
3. [src/scene/README.md](src/scene/README.md) - 场景实现

### 我想查询函数

1. [docs/快速参考.md](docs/快速参考.md) - 快速查找
2. [docs/API文档.md](docs/API文档.md) - 详细说明

### 我遇到了问题

1. [docs/实现指南.md](docs/实现指南.md) - 常见问题
2. [src/game_object/README.md](src/game_object/README.md) - 常见错误
3. [src/scene/README.md](src/scene/README.md) - 常见错误

## 📖 源代码文档

### 工具函数库

| 文件 | 说明 | 字符数 |
|------|------|--------|
| [src/util/config.h](src/util/config.h) | 游戏配置参数 | 5,151 |
| [src/util/type.h](src/util/type.h) | 数据结构定义 | 7,039 |
| [src/util/util.h](src/util/util.h) | 工具函数声明 | 8,398 |
| [src/util/util.cpp](src/util/util.cpp) | 工具函数实现 | 9,790 |

### 输入系统

| 文件 | 说明 | 字符数 |
|------|------|--------|
| [src/util/keyboard.h](src/util/keyboard.h) | 键盘输入声明 | 6,994 |
| [src/util/keyboard.cpp](src/util/keyboard.cpp) | 键盘输入实现 | 7,476 |
| [src/util/mouse.h](src/util/mouse.h) | 鼠标输入声明 | 9,171 |
| [src/util/mouse.cpp](src/util/mouse.cpp) | 鼠标输入实现 | 9,172 |

## 🔍 按功能查找

### 配置和设置

- **窗口大小** → [src/util/config.h](src/util/config.h) → `WINDOW_WIDTH`, `WINDOW_HEIGHT`
- **游戏速度** → [src/util/config.h](src/util/config.h) → `PLAYER_SPEED`, `ENEMY_SPEED`
- **帧率设置** → [src/util/config.h](src/util/config.h) → `TARGET_FPS`

### 数据类型

- **向量** → [src/util/type.h](src/util/type.h) → `Vector2`
- **矩形** → [src/util/type.h](src/util/type.h) → `Rect`
- **圆形** → [src/util/type.h](src/util/type.h) → `Circle`
- **属性** → [src/util/type.h](src/util/type.h) → `Attribute`

### 数学函数

- **归一化** → [src/util/util.h](src/util/util.h) → `Normalize()`
- **距离** → [src/util/util.h](src/util/util.h) → `Distance()`
- **限制范围** → [src/util/util.h](src/util/util.h) → `Clamp()`
- **随机数** → [src/util/util.h](src/util/util.h) → `GetRandomInt()`, `GetRandomDouble()`

### 碰撞检测

- **矩形碰撞** → [src/util/util.h](src/util/util.h) → `IsRectRectCollision()`
- **圆形碰撞** → [src/util/util.h](src/util/util.h) → `IsCircleCircleCollision()`
- **矩形圆形** → [src/util/util.h](src/util/util.h) → `IsRectCircleCollision()`

### 输入处理

- **键盘检测** → [src/util/keyboard.h](src/util/keyboard.h) → `GetKeyDown()`
- **鼠标位置** → [src/util/mouse.h](src/util/mouse.h) → `GetMouseX()`, `GetMouseY()`
- **鼠标按键** → [src/util/mouse.h](src/util/mouse.h) → `IsMouseLButtonDown()`

## 📊 文档统计

### 总体统计

- **总文档数**: 17个文件
- **文档总行数**: ~5,000行
- **代码总行数**: ~2,400行
- **总字符数**: ~80,000+汉字

### 文档分布

- **入门文档**: 4个
- **技术文档**: 4个
- **模块文档**: 2个
- **项目管理**: 3个
- **源代码文件**: 8个

## 💡 使用建议

### 第一次阅读

按照"新手入门路线"顺序阅读，约2小时。

### 日常开发

1. 需要查函数 → [docs/快速参考.md](docs/快速参考.md)
2. 需要详细说明 → [docs/API文档.md](docs/API文档.md)
3. 需要实现功能 → [docs/实现指南.md](docs/实现指南.md)

### 深入学习

1. 理解架构 → [docs/02-框架概览.md](docs/02-框架概览.md)
2. 阅读源码 → [src/util/*.h](src/util/)
3. 学习设计 → 所有README.md

## 🆘 获取帮助

### 自助资源

1. **搜索文档** - 使用 Ctrl+F 在文档中搜索
2. **查看示例** - 每个文档都有完整示例
3. **阅读注释** - 源代码有详细中文注释

### 寻求支持

1. 在 GitHub 提 Issue
2. 描述清楚问题
3. 附上错误信息

## 📌 快速链接

### 最常用的5个文档

1. [GETTING_STARTED.md](GETTING_STARTED.md) - 快速开始
2. [docs/快速参考.md](docs/快速参考.md) - 函数速查
3. [docs/实现指南.md](docs/实现指南.md) - 实现教程
4. [docs/API文档.md](docs/API文档.md) - API参考
5. [COMPLETE_GUIDE.md](COMPLETE_GUIDE.md) - 完全指南

### 源代码

- [src/util/](src/util/) - 工具函数和输入系统
- [src/game_object/](src/game_object/) - 游戏对象（待实现）
- [src/scene/](src/scene/) - 场景系统（待实现）

---

**提示**: 将此文档加入书签，方便快速访问！ 📖
