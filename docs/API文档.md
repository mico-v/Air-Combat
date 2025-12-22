# API 函数文档

本文档详细说明了框架中所有函数的用途、参数、返回值和使用示例。

## 目录

- [核心系统 (Core)](#核心系统-core)
- [场景系统 (Scene)](#场景系统-scene)
- [输入系统 (Input)](#输入系统-input)
- [游戏对象 (Game Objects)](#游戏对象-game-objects)
- [UI 组件 (UI Components)](#ui-组件-ui-components)
- [工具函数 (Utilities)](#工具函数-utilities)

---

## 核心系统 (Core)

### GameInit

**文件**: `src/core/core.cpp`

**作用**: 初始化游戏，在游戏启动时调用一次

**函数签名**:
```cpp
void GameInit(HWND hWnd, WPARAM wParam, LPARAM lParam)
```

**参数**:
- `hWnd`: 窗口句柄
- `wParam`: Windows 消息参数
- `lParam`: Windows 消息参数

**调用时机**: 在 `WM_CREATE` 事件中自动调用

**做什么**:
1. 初始化游戏时间系统
2. 加载游戏资源（图片等）
3. 切换到开始场景

**使用示例**:
```cpp
// 在 WndProc 函数中
case WM_CREATE:
    GameInit(hWnd, wParam, lParam);
    SetTimer(hWnd, 1, TIMER_INTERVAL, NULL);
    break;
```

---

### GameLoop

**文件**: `src/core/core.cpp`

**作用**: 游戏主循环，每帧调用一次

**函数签名**:
```cpp
void GameLoop(HWND hWnd)
```

**参数**:
- `hWnd`: 窗口句柄

**调用时机**: 在 `WM_TIMER` 事件中自动调用（每 16ms 一次）

**做什么**:
1. 计算帧间隔时间 (deltaTime)
2. 更新游戏时间
3. 调用场景更新函数 `SceneLoop()`
4. 请求重绘窗口

**使用示例**:
```cpp
// 在 WndProc 函数中
case WM_TIMER:
    GameLoop(hWnd);
    break;
```

---

### GameRender

**文件**: `src/core/core.cpp`

**作用**: 渲染游戏画面

**函数签名**:
```cpp
void GameRender(HWND hWnd, WPARAM wParam, LPARAM lParam)
```

**参数**:
- `hWnd`: 窗口句柄
- `wParam`: Windows 消息参数
- `lParam`: Windows 消息参数

**调用时机**: 在 `WM_PAINT` 事件中自动调用

**做什么**:
1. 创建内存缓冲区（双缓冲）
2. 清空背景
3. 调用场景渲染函数 `RenderScene()`
4. 将缓冲区内容显示到窗口

**使用示例**:
```cpp
// 在 WndProc 函数中
case WM_PAINT:
    GameRender(hWnd, wParam, lParam);
    break;
```

---

### GetGameTime

**文件**: `src/core/core.cpp`

**作用**: 获取游戏开始后经过的总时间

**函数签名**:
```cpp
double GetGameTime()
```

**返回值**: 游戏时间（单位：秒）

**使用示例**:
```cpp
// 检查是否到达指定时间
double currentTime = GetGameTime();
if (currentTime - lastSpawnTime > 1.0)
{
    // 超过 1 秒，生成新敌人
    CreateEnemy();
    lastSpawnTime = currentTime;
}
```

**💡 应用场景**:
- 定时生成敌人
- 实现游戏计时器
- 控制特定事件的触发时间

---

## 场景系统 (Scene)

### ChangeScene

**文件**: `src/scene/scene.cpp`

**作用**: 切换到指定场景

**函数签名**:
```cpp
void ChangeScene(SceneId newSceneId)
```

**参数**:
- `newSceneId`: 目标场景的 ID
  - `StartScene`: 开始场景
  - `GameScene`: 游戏场景
  - 可以添加更多场景

**使用示例**:
```cpp
// 点击开始按钮后切换到游戏场景
void OnStartButtonClick(Button* button)
{
    ChangeScene(GameScene);
}

// 游戏结束后返回开始场景
if (player->health <= 0)
{
    ChangeScene(StartScene);
}
```

**注意事项**:
- 切换不是立即发生的，会在下一帧开始时切换
- 切换时会自动调用旧场景的 `UnloadScene` 和新场景的 `LoadScene`

---

### GetCurrentScene

**文件**: `src/scene/scene.cpp`

**作用**: 获取当前场景的指针

**函数签名**:
```cpp
Scene* GetCurrentScene()
```

**返回值**: 当前场景的指针

**使用示例**:
```cpp
// 获取当前场景 ID
SceneId currentId = GetCurrentScene()->sceneId;

// 判断当前场景
if (currentId == GameScene)
{
    // 在游戏场景中...
}
```

---

### 场景函数（每个场景都需要实现）

每个场景都必须实现以下 6 个函数：

#### LoadScene_XXX

**作用**: 场景加载时调用，用于初始化

**调用时机**: 切换到该场景时

**典型实现**:
```cpp
void LoadScene_GameScene()
{
    // 1. 创建游戏对象
    CreatePlayer();
    
    // 2. 初始化变量
    enemySpawnTime = 0;
    
    // 3. 创建 UI 元素（如果有）
    // ButtonId pauseBtn = CreateButton(...);
}
```

---

#### UnloadScene_XXX

**作用**: 场景卸载时调用，用于清理资源

**调用时机**: 离开该场景时

**典型实现**:
```cpp
void UnloadScene_GameScene()
{
    // 1. 销毁游戏对象
    DestroyPlayer();
    DestroyEnemies();
    DestroyBullets();
    
    // 2. 销毁 UI 元素
    DestroyButtons();
    
    // 3. 清理其他资源
}
```

**💡 重要**: 必须销毁所有在 LoadScene 中创建的对象，防止内存泄漏！

---

#### ProcessUiInput_XXX

**作用**: 处理 UI 输入（按钮点击等）

**调用时机**: 每帧开始

**典型实现**:
```cpp
void ProcessUiInput_StartScene()
{
    // 检查鼠标点击
    if (IsMouseLButtonDown())
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        PressButtons(mouseX, mouseY);
    }
}
```

---

#### CheckCollision_XXX

**作用**: 检测游戏对象之间的碰撞

**调用时机**: 每帧，在 ProcessUiInput 之后，UpdateScene 之前

**典型实现**:
```cpp
void CheckCollision_GameScene()
{
    // 1. 玩家与敌人的碰撞
    CheckCollision_Player_Enemies();
    
    // 2. 子弹与敌人的碰撞
    CheckCollision_Bullets_Enemies();
}
```

---

#### UpdateScene_XXX

**作用**: 更新场景中的游戏逻辑

**参数**:
- `deltaTime`: 帧间隔时间（秒）

**调用时机**: 每帧，在 CheckCollision 之后

**典型实现**:
```cpp
void UpdateScene_GameScene(double deltaTime)
{
    // 1. 更新玩家
    UpdatePlayer(deltaTime);
    
    // 2. 更新敌人
    UpdateEnemies(deltaTime);
    
    // 3. 更新子弹
    UpdateBullets(deltaTime);
}
```

**💡 重要**: 所有移动、动画、计时器都在这里更新

---

#### RenderScene_XXX

**作用**: 绘制场景内容

**参数**:
- `hdc_memBuffer`: 内存缓冲区（在这上面绘制）
- `hdc_loadBmp`: 用于加载位图的 DC

**调用时机**: 绘制窗口时

**典型实现**:
```cpp
void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 1. 绘制背景（如果需要）
    
    // 2. 绘制游戏对象
    RenderPlayer(hdc_memBuffer, hdc_loadBmp);
    RenderEnemies(hdc_memBuffer, hdc_loadBmp);
    RenderBullets(hdc_memBuffer, hdc_loadBmp);
    
    // 3. 绘制 UI 文字
    DrawText(hdc_memBuffer, ...);
    
    // 4. 绘制按钮（会自动调用）
    RenderButtons(hdc_memBuffer, hdc_loadBmp);
}
```

---

## 输入系统 (Input)

### 键盘输入

#### GetKeyDown

**文件**: `src/util/keyboard.cpp`

**作用**: 检查某个键是否正在被按下

**函数签名**:
```cpp
bool GetKeyDown(int keycode)
```

**参数**:
- `keycode`: 键盘代码（虚拟键码）

**返回值**: 
- `true`: 该键正在被按下
- `false`: 该键未被按下

**常用键码**:
```cpp
VK_SPACE    // 空格键
VK_RETURN   // 回车键
VK_ESCAPE   // ESC 键
VK_UP       // 上方向键
VK_DOWN     // 下方向键
VK_LEFT     // 左方向键
VK_RIGHT    // 右方向键
'W'         // W 键
'A'         // A 键
'S'         // S 键
'D'         // D 键
```

**使用示例**:
```cpp
// 检测空格键发射子弹
if (GetKeyDown(VK_SPACE))
{
    FireBullet();
}

// WASD 移动
Vector2 direction = {0, 0};
if (GetKeyDown('W')) direction.y -= 1;
if (GetKeyDown('S')) direction.y += 1;
if (GetKeyDown('A')) direction.x -= 1;
if (GetKeyDown('D')) direction.x += 1;

// 移动玩家
player->x += direction.x * speed * deltaTime;
player->y += direction.y * speed * deltaTime;
```

---

### 鼠标输入

#### GetMouseX / GetMouseY

**文件**: `src/util/mouse.cpp`

**作用**: 获取鼠标当前位置

**函数签名**:
```cpp
int GetMouseX()  // 获取 X 坐标
int GetMouseY()  // 获取 Y 坐标
```

**返回值**: 鼠标坐标（相对于窗口左上角）

**使用示例**:
```cpp
int mouseX = GetMouseX();
int mouseY = GetMouseY();

// 检查鼠标是否在某个区域内
if (mouseX >= 100 && mouseX <= 200 && 
    mouseY >= 50 && mouseY <= 100)
{
    // 鼠标在矩形区域内
}
```

---

#### IsMouseLButtonDown

**文件**: `src/util/mouse.cpp`

**作用**: 检查鼠标左键是否被按下

**函数签名**:
```cpp
bool IsMouseLButtonDown()
```

**返回值**:
- `true`: 鼠标左键正在被按下
- `false`: 鼠标左键未被按下

**使用示例**:
```cpp
// 处理点击
if (IsMouseLButtonDown())
{
    int x = GetMouseX();
    int y = GetMouseY();
    
    // 检查是否点击了按钮
    PressButtons(x, y);
}
```

**💡 提示**: 这个函数会持续返回 `true` 直到松开鼠标，如果只想检测"点击"（按下并松开），需要额外的逻辑。

---

## 游戏对象 (Game Objects)

### 玩家 (Player)

#### CreatePlayer

**文件**: `src/game_object/player.cpp`

**作用**: 创建玩家对象

**函数签名**:
```cpp
void CreatePlayer()
```

**使用时机**: 在 `LoadScene_GameScene` 中调用

**使用示例**:
```cpp
void LoadScene_GameScene()
{
    CreatePlayer();  // 创建玩家
}
```

**做什么**:
- 分配内存创建 Player 对象
- 设置初始位置（通常在屏幕底部中央）
- 初始化属性（生命值、分数、速度等）

---

#### DestroyPlayer

**文件**: `src/game_object/player.cpp`

**作用**: 销毁玩家对象

**函数签名**:
```cpp
void DestroyPlayer()
```

**使用时机**: 在 `UnloadScene_GameScene` 中调用

**使用示例**:
```cpp
void UnloadScene_GameScene()
{
    DestroyPlayer();  // 销毁玩家
}
```

**💡 重要**: 必须调用此函数，否则会造成内存泄漏！

---

#### UpdatePlayer

**文件**: `src/game_object/player.cpp`

**作用**: 更新玩家状态

**函数签名**:
```cpp
void UpdatePlayer(double deltaTime)
```

**参数**:
- `deltaTime`: 帧间隔时间（秒）

**使用时机**: 在 `UpdateScene_GameScene` 中每帧调用

**做什么**:
1. 处理键盘输入（移动）
2. 限制玩家在屏幕内
3. 更新动画帧
4. 处理射击（空格键）
5. 更新子弹冷却时间

**使用示例**:
```cpp
void UpdateScene_GameScene(double deltaTime)
{
    UpdatePlayer(deltaTime);
}
```

---

#### RenderPlayer

**文件**: `src/game_object/player.cpp`

**作用**: 绘制玩家

**函数签名**:
```cpp
void RenderPlayer(HDC hdc_memBuffer, HDC hdc_loadBmp)
```

**参数**:
- `hdc_memBuffer`: 内存缓冲区
- `hdc_loadBmp`: 用于加载位图的 DC

**使用时机**: 在 `RenderScene_GameScene` 中调用

**使用示例**:
```cpp
void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    RenderPlayer(hdc_memBuffer, hdc_loadBmp);
}
```

---

#### GetPlayer

**文件**: `src/game_object/player.cpp`

**作用**: 获取玩家对象指针

**函数签名**:
```cpp
Player* GetPlayer()
```

**返回值**: 玩家对象指针（如果未创建则返回 `nullptr`）

**使用示例**:
```cpp
// 获取玩家信息
Player* player = GetPlayer();
if (player != nullptr)
{
    int health = player->attributes.health;
    int score = player->attributes.score;
    
    // 显示生命值和分数
    printf("生命值: %d, 分数: %d\n", health, score);
}
```

**💡 常见用途**:
- 在碰撞检测中获取玩家位置
- 显示玩家属性（生命值、分数）
- 修改玩家状态

---

### 敌人 (Enemy)

#### CreateEnemy

**文件**: `src/game_object/enemy.cpp`

**作用**: 在指定位置创建一个敌人

**函数签名**:
```cpp
void CreateEnemy(double x, double y)
```

**参数**:
- `x`: 敌人的 X 坐标
- `y`: 敌人的 Y 坐标

**使用示例**:
```cpp
// 在屏幕顶部中央创建敌人
CreateEnemy(GAME_WIDTH / 2, -100);

// 在随机位置创建
double randomX = GetRandomDouble(0, GAME_WIDTH - ENEMY_WIDTH);
CreateEnemy(randomX, -100);
```

---

#### CreateRandomEnemy

**文件**: `src/game_object/enemy.cpp`

**作用**: 在随机位置创建敌人

**函数签名**:
```cpp
void CreateRandomEnemy()
```

**使用示例**:
```cpp
// 定时生成敌人
if (GetGameTime() - lastSpawnTime > 1.0)
{
    CreateRandomEnemy();
    lastSpawnTime = GetGameTime();
}
```

---

#### DestroyEnemy

**文件**: `src/game_object/enemy.cpp`

**作用**: 销毁指定的敌人

**函数签名**:
```cpp
void DestroyEnemy(Enemy* enemy)
```

**参数**:
- `enemy`: 要销毁的敌人指针

**使用示例**:
```cpp
// 敌人生命值为 0 时销毁
for (Enemy* enemy : GetEnemies())
{
    if (enemy->attributes.health <= 0)
    {
        DestroyEnemy(enemy);
    }
}
```

**💡 注意**: 不要在遍历敌人列表的过程中直接删除，可能导致崩溃。正确的做法见下文的碰撞检测示例。

---

#### DestroyEnemies

**文件**: `src/game_object/enemy.cpp`

**作用**: 销毁所有敌人

**函数签名**:
```cpp
void DestroyEnemies()
```

**使用时机**: 在 `UnloadScene_GameScene` 中调用

**使用示例**:
```cpp
void UnloadScene_GameScene()
{
    DestroyEnemies();  // 清空所有敌人
}
```

---

#### UpdateEnemies

**文件**: `src/game_object/enemy.cpp`

**作用**: 更新所有敌人

**函数签名**:
```cpp
void UpdateEnemies(double deltaTime)
```

**参数**:
- `deltaTime`: 帧间隔时间

**使用时机**: 在 `UpdateScene_GameScene` 中调用

**做什么**:
1. 定时生成新敌人
2. 移动所有敌人
3. 删除超出屏幕的敌人

---

#### RenderEnemies

**文件**: `src/game_object/enemy.cpp`

**作用**: 绘制所有敌人

**函数签名**:
```cpp
void RenderEnemies(HDC hdc_memBuffer, HDC hdc_loadBmp)
```

**使用时机**: 在 `RenderScene_GameScene` 中调用

---

#### GetEnemies

**文件**: `src/game_object/enemy.cpp`

**作用**: 获取所有敌人的列表

**函数签名**:
```cpp
std::vector<Enemy*> GetEnemies()
```

**返回值**: 包含所有敌人指针的 vector

**使用示例**:
```cpp
// 遍历所有敌人
for (Enemy* enemy : GetEnemies())
{
    // 对每个敌人做某些操作
    printf("敌人位置: (%f, %f)\n", enemy->position.x, enemy->position.y);
}

// 获取敌人数量
int enemyCount = GetEnemies().size();
```

---

### 子弹 (Bullet)

子弹的函数与敌人类似，包括：

- `CreateBullet(double x, double y, int damage, double speed)`
- `DestroyBullet(Bullet* bullet)`
- `DestroyBullets()`
- `UpdateBullets(double deltaTime)`
- `RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp)`
- `GetBullets()` → `std::vector<Bullet*>`

**创建子弹示例**:
```cpp
// 从玩家位置发射子弹
Player* player = GetPlayer();
CreateBullet(
    player->position.x + player->width / 2,  // X: 飞机中心
    player->position.y,                        // Y: 飞机顶部
    1,                                         // 伤害
    800.0                                      // 速度
);
```

---

## UI 组件 (UI Components)

### 按钮 (Button)

#### CreateButton

**文件**: `src/ui/button.cpp`

**作用**: 创建一个按钮

**函数签名**:
```cpp
ButtonId CreateButton(
    double x, double y,
    int width, int height,
    RenderButtonFunc renderFunc,
    OnClickButtonFunc clickFunc
)
```

**参数**:
- `x, y`: 按钮位置
- `width, height`: 按钮大小
- `renderFunc`: 绘制函数（如何显示按钮）
- `clickFunc`: 点击回调函数（点击后做什么）

**返回值**: 按钮 ID（用于后续操作）

**使用示例**:
```cpp
// 1. 定义绘制函数
void RenderStartButton(Button* button, HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 绘制按钮图片
    SelectObject(hdc_loadBmp, bmp_StartButton);
    TransparentBlt(hdc_memBuffer, 
        button->position.x, button->position.y,
        button->width, button->height,
        hdc_loadBmp, 0, 0,
        button->width, button->height,
        COLOR_TRANSPARENT);
}

// 2. 定义点击回调
void OnStartButtonClick(Button* button)
{
    // 切换到游戏场景
    ChangeScene(GameScene);
}

// 3. 创建按钮
ButtonId startBtn = CreateButton(
    300, 400,              // 位置
    200, 100,              // 大小
    RenderStartButton,     // 绘制函数
    OnStartButtonClick     // 点击回调
);

// 4. 启用按钮
EnableButton(startBtn);
```

---

#### EnableButton / DisableButton

**作用**: 启用或禁用按钮

**函数签名**:
```cpp
void EnableButton(ButtonId id)
void DisableButton(ButtonId id)
```

**参数**:
- `id`: 按钮 ID

**使用示例**:
```cpp
// 创建按钮时默认是禁用的，需要手动启用
ButtonId btn = CreateButton(...);
EnableButton(btn);  // 启用按钮

// 暂时禁用按钮（不响应点击，也不显示）
DisableButton(btn);

// 重新启用
EnableButton(btn);
```

**💡 应用场景**:
- 暂停菜单中的按钮
- 根据游戏状态动态显示/隐藏按钮

---

#### PressButtons

**作用**: 检查鼠标点击是否命中任何按钮

**函数签名**:
```cpp
void PressButtons(int mouseX, int mouseY)
```

**参数**:
- `mouseX, mouseY`: 鼠标坐标

**使用时机**: 在 `ProcessUiInput` 中调用

**使用示例**:
```cpp
void ProcessUiInput_StartScene()
{
    if (IsMouseLButtonDown())
    {
        PressButtons(GetMouseX(), GetMouseY());
    }
}
```

**工作原理**:
1. 遍历所有已启用的按钮
2. 检查鼠标是否在按钮范围内
3. 如果命中，调用该按钮的点击回调函数

---

#### DestroyButtons

**作用**: 销毁所有按钮

**函数签名**:
```cpp
void DestroyButtons()
```

**使用时机**: 在 `UnloadScene` 中调用

**使用示例**:
```cpp
void UnloadScene_StartScene()
{
    DestroyButtons();  // 清空所有按钮
}
```

---

## 工具函数 (Utilities)

### 数学函数

#### Normalize

**文件**: `src/util/util.cpp`

**作用**: 归一化向量（变成长度为 1 的向量）

**函数签名**:
```cpp
Vector2 Normalize(Vector2 v)
```

**参数**:
- `v`: 要归一化的向量

**返回值**: 归一化后的向量

**使用示例**:
```cpp
// WASD 移动时保证所有方向速度一致
Vector2 direction = {0, 0};
if (GetKeyDown('W')) direction.y -= 1;
if (GetKeyDown('S')) direction.y += 1;
if (GetKeyDown('A')) direction.x -= 1;
if (GetKeyDown('D')) direction.x += 1;

// 归一化方向向量
direction = Normalize(direction);

// 现在无论往哪个方向移动，速度都是一致的
player->x += direction.x * speed * deltaTime;
player->y += direction.y * deltaTime;
```

**为什么需要归一化？**
```
向右移动: (1, 0)    长度 = 1
向右上移动: (1, -1)  长度 = √2 ≈ 1.414

如果不归一化，斜向移动会比直线移动快 1.414 倍！
归一化后，所有方向的向量长度都是 1，速度就一致了。
```

---

#### Length

**作用**: 计算向量长度

**函数签名**:
```cpp
double Length(Vector2 v)
```

**返回值**: 向量长度

**使用示例**:
```cpp
Vector2 v = {3, 4};
double len = Length(v);  // len = 5 (因为 3² + 4² = 25, √25 = 5)
```

---

### 随机数

#### GetRandomDouble

**作用**: 生成指定范围的随机小数

**函数签名**:
```cpp
double GetRandomDouble(double min, double max)
```

**参数**:
- `min`: 最小值
- `max`: 最大值

**返回值**: [min, max] 范围内的随机数

**使用示例**:
```cpp
// 在屏幕宽度范围内随机生成 X 坐标
double randomX = GetRandomDouble(0, GAME_WIDTH - ENEMY_WIDTH);

// 随机速度
double speed = GetRandomDouble(100, 300);
```

---

#### GetRandomInt

**作用**: 生成指定范围的随机整数

**函数签名**:
```cpp
int GetRandomInt(int min, int max)
```

**使用示例**:
```cpp
// 随机选择 1-3
int randomChoice = GetRandomInt(1, 3);

// 随机生命值
int health = GetRandomInt(1, 5);
```

---

### 碰撞检测

#### IsRectRectCollision

**作用**: 检测两个矩形是否碰撞

**函数签名**:
```cpp
bool IsRectRectCollision(Rect rect1, Rect rect2)
```

**返回值**: 
- `true`: 碰撞
- `false`: 未碰撞

**使用示例**:
```cpp
// 检测玩家与敌人的碰撞
Player* player = GetPlayer();
Rect playerRect;
playerRect.left = player->position.x;
playerRect.right = player->position.x + player->width;
playerRect.top = player->position.y;
playerRect.bottom = player->position.y + player->height;

for (Enemy* enemy : GetEnemies())
{
    Rect enemyRect;
    enemyRect.left = enemy->position.x;
    enemyRect.right = enemy->position.x + enemy->width;
    enemyRect.top = enemy->position.y;
    enemyRect.bottom = enemy->position.y + enemy->height;
    
    if (IsRectRectCollision(playerRect, enemyRect))
    {
        // 发生碰撞！
        player->attributes.health--;
        DestroyEnemy(enemy);
    }
}
```

---

#### IsRectCircleCollision

**作用**: 检测矩形与圆形是否碰撞

**函数签名**:
```cpp
bool IsRectCircleCollision(Rect rect, Circle circle)
```

**使用示例**:
```cpp
// 检测子弹（圆形）与敌人（矩形）的碰撞
for (Enemy* enemy : GetEnemies())
{
    Rect enemyRect = {...};
    
    for (Bullet* bullet : GetBullets())
    {
        Circle bulletCircle;
        bulletCircle.center = bullet->position;
        bulletCircle.radius = bullet->radius;
        
        if (IsRectCircleCollision(enemyRect, bulletCircle))
        {
            // 子弹击中敌人
            enemy->attributes.health -= bullet->damage;
            DestroyBullet(bullet);
        }
    }
}
```

---

## 完整使用流程示例

### 创建一个新场景

假设要创建一个"游戏结束"场景：

```cpp
// 1. 在 scene.h 中添加场景 ID
enum SceneId
{
    None = 0,
    StartScene = 1,
    GameScene = 2,
    GameOverScene = 3  // 新增
};

// 2. 创建 scene3.h，声明 6 个函数
void LoadScene_GameOverScene();
void UnloadScene_GameOverScene();
void ProcessUiInput_GameOverScene();
void CheckCollision_GameOverScene();
void UpdateScene_GameOverScene(double deltaTime);
void RenderScene_GameOverScene(HDC hdc_memBuffer, HDC hdc_loadBmp);

// 3. 创建 scene3.cpp，实现这些函数
void LoadScene_GameOverScene()
{
    // 创建"重新开始"按钮
    ButtonId restartBtn = CreateButton(
        300, 400, 200, 100,
        RenderRestartButton,
        OnRestartButtonClick
    );
    EnableButton(restartBtn);
}

void RenderScene_GameOverScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    // 显示"游戏结束"文字
    RECT rect = {0, 200, WINDOW_WIDTH, 300};
    DrawText(hdc_memBuffer, TEXT("游戏结束！"), -1, &rect, 
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
    // 显示最终分数
    TCHAR scoreText[64];
    swprintf_s(scoreText, TEXT("最终分数: %d"), finalScore);
    rect.top = 350;
    rect.bottom = 400;
    DrawText(hdc_memBuffer, scoreText, -1, &rect,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// 4. 在 scene.cpp 的路由宏中添加
#define ROUTE_SCENE_FUNCTION(FUNCTION_NAME) \
    switch (GetCurrentScene()->sceneId) \
    { \
    case StartScene: \
        FUNCTION_NAME##_StartScene(); \
        break; \
    case GameScene: \
        FUNCTION_NAME##_GameScene(); \
        break; \
    case GameOverScene: \
        FUNCTION_NAME##_GameOverScene(); \
        break; \
    }

// 5. 在游戏结束时切换
if (player->attributes.health <= 0)
{
    ChangeScene(GameOverScene);
}
```

---

## 调试技巧

### 使用 Log 函数

```cpp
// 显示调试信息
Log(1, TEXT("玩家位置: x=%f, y=%f"), player->x, player->y);
Log(1, TEXT("敌人数量: %d"), GetEnemies().size());
Log(1, TEXT("游戏时间: %.2f"), GetGameTime());
```

### 断点调试

1. 在想要暂停的代码行按 F9 设置断点
2. 按 F5 启动调试
3. 程序会在断点处暂停
4. 可以查看变量值、单步执行

### 常见问题排查

| 问题 | 检查项 |
|------|--------|
| 对象不显示 | 1. 是否调用了 Render 函数？<br>2. 位置是否在屏幕内？<br>3. 资源是否正确加载？ |
| 对象不移动 | 1. 是否调用了 Update 函数？<br>2. deltaTime 是否正确？<br>3. 速度是否为 0？ |
| 程序崩溃 | 1. 是否访问了空指针？<br>2. 数组是否越界？<br>3. 对象是否已被删除？ |
| 内存泄漏 | 1. new 和 delete 是否配对？<br>2. UnloadScene 是否清理了所有对象？ |

---

## 总结

本文档提供了框架中所有主要函数的详细说明。使用时的建议：

1. **不要急于记住所有函数**：需要时查阅即可
2. **理解函数的作用**：比记住函数名更重要
3. **多看示例代码**：实践是最好的老师
4. **遇到问题时**：
   - 先查看文档
   - 检查示例代码
   - 使用调试工具
   - 在 GitHub 提 Issue

祝你开发愉快！ 🎮✈️
