# 场景系统实现指南

本目录包含游戏的场景管理和各个场景的实现代码。

## 📁 文件结构

```
scene/
├── README.md          # 本文件
├── scene.h           # 场景管理头文件
├── scene.cpp         # 场景管理实现
├── scene1.h          # 开始场景头文件
├── scene1.cpp        # 开始场景实现
├── scene2.h          # 游戏场景头文件
└── scene2.cpp        # 游戏场景实现
```

## 🎬 场景系统概述

场景系统负责管理游戏的不同界面和状态。本游戏包含以下场景：

### 1. 开始场景 (StartScene)
- 显示游戏标题
- 显示开始按钮
- 等待玩家点击开始

### 2. 游戏场景 (GameScene)
- 实际游戏画面
- 玩家控制
- 敌人生成
- 碰撞检测

### 3. 游戏结束场景 (GameOverScene) - 可选
- 显示最终分数
- 显示重新开始按钮
- 返回主菜单选项

## 📝 场景生命周期

每个场景都必须实现 6 个核心函数：

### 1. LoadScene - 场景加载
**调用时机**: 切换到该场景时

**职责**:
- 创建游戏对象
- 初始化变量
- 创建 UI 元素
- 加载场景特定资源

```cpp
void LoadScene_GameScene()
{
    // 1. 创建游戏对象
    CreatePlayer();
    
    // 2. 初始化变量
    enemySpawnTimer = 0;
    score = 0;
    
    // 3. 创建 UI（如暂停按钮）
    // pauseButton = CreateButton(...);
}
```

### 2. UnloadScene - 场景卸载
**调用时机**: 离开该场景时

**职责**:
- 销毁游戏对象
- 清理 UI 元素
- 释放资源

```cpp
void UnloadScene_GameScene()
{
    // 1. 销毁游戏对象（重要！防止内存泄漏）
    DestroyPlayer();
    DestroyEnemies();
    DestroyBullets();
    
    // 2. 销毁 UI
    DestroyButtons();
}
```

### 3. ProcessUiInput - 处理 UI 输入
**调用时机**: 每帧开始

**职责**:
- 处理按钮点击
- 处理 UI 交互

```cpp
void ProcessUiInput_StartScene()
{
    // 检测鼠标点击按钮
    if (IsMouseLButtonDown())
    {
        PressButtons(GetMouseX(), GetMouseY());
    }
}
```

### 4. CheckCollision - 碰撞检测
**调用时机**: 每帧，在 UpdateScene 之前

**职责**:
- 检测所有游戏对象的碰撞
- 处理碰撞后的逻辑

```cpp
void CheckCollision_GameScene()
{
    // 1. 玩家与敌人
    CheckCollision_Player_Enemies();
    
    // 2. 子弹与敌人
    CheckCollision_Bullets_Enemies();
}
```

### 5. UpdateScene - 更新场景
**调用时机**: 每帧

**参数**: `double deltaTime` - 帧间隔时间

**职责**:
- 更新所有游戏对象
- 更新游戏逻辑
- 更新计时器

```cpp
void UpdateScene_GameScene(double deltaTime)
{
    // 更新所有游戏对象
    UpdatePlayer(deltaTime);
    UpdateEnemies(deltaTime);
    UpdateBullets(deltaTime);
    
    // 更新游戏逻辑
    // ...
}
```

### 6. RenderScene - 渲染场景
**调用时机**: 绘制窗口时

**参数**: 
- `HDC hdc_memBuffer` - 内存缓冲区（在这上面绘制）
- `HDC hdc_loadBmp` - 用于加载位图

**职责**:
- 绘制背景
- 绘制游戏对象
- 绘制 UI 文字
- 绘制按钮

```cpp
void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 1. 绘制背景（可选）
    
    // 2. 绘制游戏对象
    RenderPlayer(hdc_memBuffer, hdc_loadBmp);
    RenderEnemies(hdc_memBuffer, hdc_loadBmp);
    RenderBullets(hdc_memBuffer, hdc_loadBmp);
    
    // 3. 绘制 UI 文字
    TCHAR scoreText[64];
    swprintf_s(scoreText, TEXT("分数: %d"), score);
    TextOut(hdc_memBuffer, 10, 10, scoreText, lstrlen(scoreText));
    
    // 4. 绘制按钮（自动调用）
    RenderButtons(hdc_memBuffer, hdc_loadBmp);
}
```

## 🔄 场景切换流程

```
当前场景运行中
    ↓
调用 ChangeScene(NewScene)
    ↓
标记需要切换场景
    ↓
下一帧开始时：
    ↓
调用当前场景的 UnloadScene
    ↓
切换场景 ID
    ↓
调用新场景的 LoadScene
    ↓
新场景开始运行
```

**代码示例**:
```cpp
// 在按钮回调中切换场景
void OnStartButtonClick(Button* button)
{
    ChangeScene(GameScene);  // 不会立即切换
}

// 在 SceneLoop 中实际切换
void SceneLoop(double deltaTime)
{
    // 检查是否需要切换场景
    if (needSceneChange)
    {
        UnloadScene();        // 卸载当前场景
        currentScene = nextScene;
        LoadScene();          // 加载新场景
        needSceneChange = false;
    }
    
    // 继续当前场景的逻辑
    ProcessUiInput();
    CheckCollision();
    UpdateScene(deltaTime);
}
```

## 📋 实现步骤

### 步骤 1：实现场景管理器 (scene.h/cpp)

```cpp
// scene.h
#pragma once

enum SceneId
{
    None = 0,
    StartScene = 1,
    GameScene = 2
};

struct Scene
{
    SceneId sceneId;
};

// 场景管理函数
void ChangeScene(SceneId newSceneId);
Scene* GetCurrentScene();
void SceneLoop(double deltaTime);
void RenderScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
```

### 步骤 2：实现开始场景 (scene1.h/cpp)

```cpp
// scene1.h
#pragma once
#include <windows.h>

void LoadScene_StartScene();
void UnloadScene_StartScene();
void ProcessUiInput_StartScene();
void CheckCollision_StartScene();
void UpdateScene_StartScene(double deltaTime);
void RenderScene_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
```

### 步骤 3：实现游戏场景 (scene2.h/cpp)

```cpp
// scene2.h
#pragma once
#include <windows.h>

void LoadScene_GameScene();
void UnloadScene_GameScene();
void ProcessUiInput_GameScene();
void CheckCollision_GameScene();
void UpdateScene_GameScene(double deltaTime);
void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
```

### 步骤 4：在 scene.cpp 中路由函数调用

```cpp
// 使用宏简化路由代码
#define ROUTE_SCENE_FUNCTION(FUNCTION_NAME) \
    switch (GetCurrentScene()->sceneId) \
    { \
    case StartScene: \
        FUNCTION_NAME##_StartScene(); \
        break; \
    case GameScene: \
        FUNCTION_NAME##_GameScene(); \
        break; \
    }

// 使用示例
void LoadScene()
{
    ROUTE_SCENE_FUNCTION(LoadScene);
}
```

## ⚠️ 常见错误

### 1. 忘记清理资源
```cpp
// ❌ 错误：切换场景时忘记清理
void ChangeScene(SceneId newId)
{
    currentSceneId = newId;
    LoadScene();  // 没有先卸载旧场景！
}

// ✅ 正确：先卸载再加载
void ChangeScene(SceneId newId)
{
    UnloadScene();         // 先卸载
    currentSceneId = newId;
    LoadScene();           // 再加载
}
```

### 2. 在错误的时机切换场景
```cpp
// ❌ 错误：在更新循环中立即切换
void UpdateScene()
{
    if (gameOver)
    {
        UnloadScene();     // 立即卸载
        ChangeScene(GameOverScene);
        // 但后续代码还会访问已销毁的对象！
    }
    
    UpdatePlayer();  // 崩溃！player 已被销毁
}

// ✅ 正确：标记切换，下一帧再执行
void UpdateScene()
{
    if (gameOver)
    {
        ChangeScene(GameOverScene);  // 仅标记
        return;  // 提前返回，不执行后续代码
    }
    
    UpdatePlayer();
}
```

### 3. 场景切换死循环
```cpp
// ❌ 错误：在 LoadScene 中切换场景
void LoadScene_StartScene()
{
    CreateButton(..., OnButtonClick);
}

void OnButtonClick()
{
    ChangeScene(GameScene);  // 在加载场景时切换
    // 可能导致问题
}

// ✅ 正确：在输入处理或更新中切换
void ProcessUiInput_StartScene()
{
    if (IsMouseLButtonDown())
    {
        if (ClickedStartButton())
        {
            ChangeScene(GameScene);
        }
    }
}
```

## 🎯 实现检查清单

完成场景实现后，请确认：

- [ ] 所有场景都实现了 6 个核心函数
- [ ] LoadScene 创建的对象在 UnloadScene 中销毁
- [ ] 场景切换不会导致内存泄漏
- [ ] 切换场景时程序不会崩溃
- [ ] UI 按钮在正确的场景中显示
- [ ] 场景之间的数据传递正确（如分数）

## 📚 参考资料

- `docs/API文档.md` - 场景系统函数详解
- `docs/02-框架概览.md` - 场景系统架构
- `docs/实现指南.md` - 完整实现教程

---

开始创建你的游戏场景吧！ 🎬
