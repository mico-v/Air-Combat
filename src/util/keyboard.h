/**
 * @file keyboard.h
 * @brief 键盘输入系统头文件
 * 
 * 这个文件提供键盘输入处理功能，包括：
 * - 记录按键状态（按下/释放）
 * - 查询按键状态
 * 
 * 💡 工作原理：
 * 1. Win32 系统检测到键盘事件 → 发送 WM_KEYDOWN/WM_KEYUP 消息
 * 2. 在 WndProc 中调用 KeyDown/KeyUp 函数记录状态
 * 3. 游戏逻辑中调用 GetKeyDown 查询状态
 * 
 * 💡 为什么要这样设计？
 * - Win32 的按键消息是异步的，不能直接在游戏循环中查询
 * - 需要一个"缓存"来存储按键状态
 * - 游戏逻辑只需要知道"某个键是否被按下"，不关心消息处理细节
 */

#pragma once

#include <windows.h>

/* ============================================================================
 * 按键状态设置函数（在 WndProc 中调用）
 * ============================================================================
 */

/**
 * @brief 处理按键按下事件
 * 
 * 当用户按下键盘按键时，Windows 会发送 WM_KEYDOWN 消息到窗口过程函数。
 * 在 WndProc 的 WM_KEYDOWN 处理中调用此函数来记录按键状态。
 * 
 * @param hWnd 窗口句柄
 * @param wParam 虚拟键码（例如 VK_SPACE, 'W', VK_UP 等）
 * @param lParam 附加信息（重复次数、扫描码等）
 * 
 * 使用示例（在 WndProc 中）：
 * ```cpp
 * case WM_KEYDOWN:
 *     KeyDown(hWnd, wParam, lParam);
 *     break;
 * ```
 * 
 * 💡 注意：
 * - 按住按键不放会持续触发 WM_KEYDOWN 消息
 * - 可以通过 lParam 判断是否是重复消息（如果需要）
 */
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

/**
 * @brief 处理按键释放事件
 * 
 * 当用户释放键盘按键时，Windows 会发送 WM_KEYUP 消息。
 * 在 WndProc 的 WM_KEYUP 处理中调用此函数来更新按键状态。
 * 
 * @param hWnd 窗口句柄
 * @param wParam 虚拟键码
 * @param lParam 附加信息
 * 
 * 使用示例（在 WndProc 中）：
 * ```cpp
 * case WM_KEYUP:
 *     KeyUp(hWnd, wParam, lParam);
 *     break;
 * ```
 */
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

/* ============================================================================
 * 按键状态查询函数（在游戏逻辑中调用）
 * ============================================================================
 */

/**
 * @brief 检查指定按键是否正在被按下
 * 
 * 这是游戏逻辑中最常用的函数，用于检查玩家的输入。
 * 
 * @param keycode 虚拟键码
 * @return true 表示按键正在被按下，false 表示按键未被按下
 * 
 * 常用虚拟键码：
 * - VK_SPACE     空格键
 * - VK_RETURN    回车键
 * - VK_ESCAPE    ESC 键
 * - VK_UP        上方向键
 * - VK_DOWN      下方向键
 * - VK_LEFT      左方向键
 * - VK_RIGHT     右方向键
 * - 'W', 'A', 'S', 'D'  字母键（必须大写）
 * - '0' 到 '9'   数字键
 * - VK_F1 到 VK_F12  功能键
 * 
 * 使用示例 1：检测单个按键
 * ```cpp
 * // 按空格键发射子弹
 * if (GetKeyDown(VK_SPACE))
 * {
 *     FireBullet();
 * }
 * ```
 * 
 * 使用示例 2：WASD 移动
 * ```cpp
 * Vector2 direction = {0, 0};
 * 
 * if (GetKeyDown('W'))  // 向上
 *     direction.y -= 1;
 * if (GetKeyDown('S'))  // 向下
 *     direction.y += 1;
 * if (GetKeyDown('A'))  // 向左
 *     direction.x -= 1;
 * if (GetKeyDown('D'))  // 向右
 *     direction.x += 1;
 * 
 * // 归一化方向向量（保证所有方向速度一致）
 * direction = Normalize(direction);
 * 
 * // 移动玩家
 * player->x += direction.x * speed * deltaTime;
 * player->y += direction.y * speed * deltaTime;
 * ```
 * 
 * 使用示例 3：组合键
 * ```cpp
 * // Ctrl + S 保存
 * if (GetKeyDown(VK_CONTROL) && GetKeyDown('S'))
 * {
 *     SaveGame();
 * }
 * ```
 * 
 * 💡 注意事项：
 * 1. 字母键码必须用大写：'W' 而不是 'w'
 * 2. 这个函数返回的是"持续状态"，按住不放会一直返回 true
 * 3. 如果只想检测"按下瞬间"，需要额外的逻辑（可以用上一帧状态对比）
 * 4. 不要在 WndProc 中调用此函数，应该在游戏更新循环中调用
 */
bool GetKeyDown(int keycode);

// Clear all key states (recommended to call from WM_KILLFOCUS).
void ClearKeyStates();

/* ============================================================================
 * 虚拟键码参考
 * ============================================================================
 * 
 * 完整的虚拟键码列表可以在这里查看：
 * https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 * 
 * 以下是一些常用的键码：
 * 
 * 【字母键】
 * 'A' 到 'Z'（必须大写）
 * 
 * 【数字键】
 * '0' 到 '9'（主键盘区的数字键）
 * VK_NUMPAD0 到 VK_NUMPAD9（小键盘数字）
 * 
 * 【方向键】
 * VK_LEFT   (0x25) - 左箭头
 * VK_UP     (0x26) - 上箭头
 * VK_RIGHT  (0x27) - 右箭头
 * VK_DOWN   (0x28) - 下箭头
 * 
 * 【功能键】
 * VK_SPACE  (0x20) - 空格键
 * VK_RETURN (0x0D) - 回车键
 * VK_ESCAPE (0x1B) - ESC 键
 * VK_BACK   (0x08) - 退格键
 * VK_TAB    (0x09) - Tab 键
 * VK_SHIFT  (0x10) - Shift 键
 * VK_CONTROL(0x11) - Ctrl 键
 * VK_MENU   (0x12) - Alt 键
 * 
 * 【F 功能键】
 * VK_F1 到 VK_F12
 * 
 * 【其他】
 * VK_LBUTTON (0x01) - 鼠标左键
 * VK_RBUTTON (0x02) - 鼠标右键
 * VK_DELETE  (0x2E) - Delete 键
 * VK_HOME    (0x24) - Home 键
 * VK_END     (0x23) - End 键
 * VK_PRIOR   (0x21) - Page Up
 * VK_NEXT    (0x22) - Page Down
 * 
 * ============================================================================
 */

/* ============================================================================
 * 实现说明
 * ============================================================================
 * 
 * 内部实现（在 keyboard.cpp 中）：
 * 
 * 1. 使用一个布尔数组存储所有按键的状态：
 *    ```cpp
 *    static bool keyStates[256] = {false};  // 256 个可能的键码
 *    ```
 * 
 * 2. KeyDown 函数设置对应键为 true：
 *    ```cpp
 *    void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
 *    {
 *        if (wParam < 256)
 *            keyStates[wParam] = true;
 *    }
 *    ```
 * 
 * 3. KeyUp 函数设置对应键为 false：
 *    ```cpp
 *    void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
 *    {
 *        if (wParam < 256)
 *            keyStates[wParam] = false;
 *    }
 *    ```
 * 
 * 4. GetKeyDown 函数查询状态：
 *    ```cpp
 *    bool GetKeyDown(int keycode)
 *    {
 *        if (keycode >= 0 && keycode < 256)
 *            return keyStates[keycode];
 *        return false;
 *    }
 *    ```
 * 
 * 💡 为什么数组大小是 256？
 * 虚拟键码的范围是 0-255（8 位），所以需要 256 个元素。
 * 
 * ============================================================================
 */

/* ============================================================================
 * 进阶功能（可选实现）
 * ============================================================================
 * 
 * 如果想要更高级的键盘输入功能，可以添加：
 * 
 * 1. **检测按键"按下瞬间"**（只在按下的那一帧返回 true）：
 *    ```cpp
 *    bool GetKeyPressed(int keycode);  // 按下瞬间
 *    bool GetKeyReleased(int keycode); // 释放瞬间
 *    ```
 *    实现方法：保存上一帧的按键状态，与当前帧对比
 * 
 * 2. **获取文字输入**（处理中文等）：
 *    需要处理 WM_CHAR 消息
 * 
 * 3. **按键映射**（自定义按键）：
 *    ```cpp
 *    void SetKeyMapping(GameAction action, int keycode);
 *    bool IsActionPressed(GameAction action);
 *    ```
 * 
 * 4. **组合键检测**：
 *    ```cpp
 *    bool IsComboPressed(int key1, int key2);
 *    ```
 * 
 * 这些功能对于初学者不是必需的，可以在掌握基础后再实现。
 * 
 * ============================================================================
 */

/* ============================================================================
 * 使用技巧
 * ============================================================================
 * 
 * 1. **防止按键"卡住"**：
 *    如果窗口失去焦点时按键还在按下状态，可能会导致按键"卡住"。
 *    解决方法：在 WM_KILLFOCUS 消息中清空所有按键状态。
 * 
 * 2. **提高代码可读性**：
 *    定义常量代替魔法数字：
 *    ```cpp
 *    #define KEY_SHOOT VK_SPACE
 *    #define KEY_PAUSE VK_ESCAPE
 *    
 *    if (GetKeyDown(KEY_SHOOT))  // 比 GetKeyDown(VK_SPACE) 更清晰
 *    ```
 * 
 * 3. **减少重复代码**：
 *    封装常用操作：
 *    ```cpp
 *    Vector2 GetInputDirection()
 *    {
 *        Vector2 dir = {0, 0};
 *        if (GetKeyDown('W') || GetKeyDown(VK_UP))    dir.y -= 1;
 *        if (GetKeyDown('S') || GetKeyDown(VK_DOWN))  dir.y += 1;
 *        if (GetKeyDown('A') || GetKeyDown(VK_LEFT))  dir.x -= 1;
 *        if (GetKeyDown('D') || GetKeyDown(VK_RIGHT)) dir.x += 1;
 *        return Normalize(dir);
 *    }
 *    ```
 * 
 * 4. **调试技巧**：
 *    添加调试输出查看按键状态：
 *    ```cpp
 *    if (GetKeyDown('W'))
 *        Log(1, TEXT("W key is down!"));
 *    ```
 * 
 * ============================================================================
 */
