/**
 * @file mouse.h
 * @brief 鼠标输入系统头文件
 * 
 * 这个文件提供鼠标输入处理功能，包括：
 * - 记录鼠标位置
 * - 记录鼠标按键状态（左键/右键/中键）
 * - 查询鼠标状态
 * 
 * 💡 工作原理：
 * 1. Win32 系统检测到鼠标事件 → 发送 WM_MOUSEMOVE/WM_LBUTTONDOWN 等消息
 * 2. 在 WndProc 中调用对应函数记录状态
 * 3. 游戏逻辑中调用查询函数获取鼠标状态
 */

#pragma once

#include <windows.h>

/* ============================================================================
 * 鼠标状态设置函数（在 WndProc 中调用）
 * ============================================================================
 */

/**
 * @brief 处理鼠标移动事件
 * 
 * 当鼠标在窗口内移动时，Windows 会发送 WM_MOUSEMOVE 消息。
 * 在 WndProc 的 WM_MOUSEMOVE 处理中调用此函数来记录鼠标位置。
 * 
 * @param hWnd 窗口句柄
 * @param wParam 鼠标按键状态标志（MK_LBUTTON, MK_RBUTTON 等）
 * @param lParam 鼠标位置（低16位是X坐标，高16位是Y坐标）
 * 
 * 使用示例（在 WndProc 中）：
 * ```cpp
 * case WM_MOUSEMOVE:
 *     MouseMove(hWnd, wParam, lParam);
 *     break;
 * ```
 * 
 * 💡 坐标说明：
 * - X 坐标：从窗口左边界开始，向右递增
 * - Y 坐标：从窗口上边界开始，向下递增
 * - 坐标原点(0,0)在窗口的左上角
 */
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

/**
 * @brief 处理鼠标左键按下事件
 * 
 * 当用户按下鼠标左键时，Windows 会发送 WM_LBUTTONDOWN 消息。
 * 
 * @param hWnd 窗口句柄
 * @param wParam 键盘修饰键状态（MK_SHIFT, MK_CONTROL 等）
 * @param lParam 鼠标位置
 * 
 * 使用示例（在 WndProc 中）：
 * ```cpp
 * case WM_LBUTTONDOWN:
 *     LButtonDown(hWnd, wParam, lParam);
 *     break;
 * ```
 */
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

/**
 * @brief 处理鼠标左键释放事件
 * 
 * 当用户释放鼠标左键时，Windows 会发送 WM_LBUTTONUP 消息。
 * 
 * @param hWnd 窗口句柄
 * @param wParam 键盘修饰键状态
 * @param lParam 鼠标位置
 * 
 * 使用示例（在 WndProc 中）：
 * ```cpp
 * case WM_LBUTTONUP:
 *     LButtonUp(hWnd, wParam, lParam);
 *     break;
 * ```
 */
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

/**
 * @brief 处理鼠标右键按下事件（可选）
 * 
 * @param hWnd 窗口句柄
 * @param wParam 键盘修饰键状态
 * @param lParam 鼠标位置
 * 
 * 使用示例（在 WndProc 中）：
 * ```cpp
 * case WM_RBUTTONDOWN:
 *     RButtonDown(hWnd, wParam, lParam);
 *     break;
 * ```
 */
void RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

/**
 * @brief 处理鼠标右键释放事件（可选）
 * 
 * @param hWnd 窗口句柄
 * @param wParam 键盘修饰键状态
 * @param lParam 鼠标位置
 * 
 * 使用示例（在 WndProc 中）：
 * ```cpp
 * case WM_RBUTTONUP:
 *     RButtonUp(hWnd, wParam, lParam);
 *     break;
 * ```
 */
void RButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

/* ============================================================================
 * 鼠标状态查询函数（在游戏逻辑中调用）
 * ============================================================================
 */

/**
 * @brief 获取鼠标当前的 X 坐标
 * 
 * @return 鼠标 X 坐标（相对于窗口左边界，单位：像素）
 * 
 * 使用示例：
 * ```cpp
 * int mouseX = GetMouseX();
 * int mouseY = GetMouseY();
 * 
 * // 检查鼠标是否在某个矩形区域内
 * if (mouseX >= rect.left && mouseX <= rect.right &&
 *     mouseY >= rect.top && mouseY <= rect.bottom)
 * {
 *     // 鼠标在矩形内
 * }
 * ```
 */
int GetMouseX();

/**
 * @brief 获取鼠标当前的 Y 坐标
 * 
 * @return 鼠标 Y 坐标（相对于窗口上边界，单位：像素）
 */
int GetMouseY();

/**
 * @brief 检查鼠标左键是否正在被按下
 * 
 * @return true 表示左键正在被按下，false 表示未被按下
 * 
 * 使用示例 1：检测按钮点击
 * ```cpp
 * void ProcessUiInput()
 * {
 *     if (IsMouseLButtonDown())
 *     {
 *         int x = GetMouseX();
 *         int y = GetMouseY();
 *         
 *         // 检查是否点击了按钮
 *         PressButtons(x, y);
 *     }
 * }
 * ```
 * 
 * 使用示例 2：拖拽功能
 * ```cpp
 * static bool isDragging = false;
 * static Vector2 dragStart;
 * 
 * void Update()
 * {
 *     if (IsMouseLButtonDown())
 *     {
 *         if (!isDragging)
 *         {
 *             // 开始拖拽
 *             isDragging = true;
 *             dragStart.x = GetMouseX();
 *             dragStart.y = GetMouseY();
 *         }
 *         else
 *         {
 *             // 正在拖拽
 *             int currentX = GetMouseX();
 *             int currentY = GetMouseY();
 *             // 计算拖拽距离...
 *         }
 *     }
 *     else
 *     {
 *         // 结束拖拽
 *         isDragging = false;
 *     }
 * }
 * ```
 * 
 * 💡 注意：
 * - 这个函数返回的是"持续状态"，按住不放会一直返回 true
 * - 如果只想检测"点击"（按下并松开），需要额外的逻辑
 */
bool IsMouseLButtonDown();

/**
 * @brief 检查鼠标右键是否正在被按下（可选）
 * 
 * @return true 表示右键正在被按下，false 表示未被按下
 * 
 * 使用场景：
 * - 右键菜单
 * - 取消操作
 * - 次要功能
 */
bool IsMouseRButtonDown();

/* ============================================================================
 * 辅助函数
 * ============================================================================
 */

/**
 * @brief 清空鼠标状态
 * 
 * 用途：
 * - 窗口失去焦点时清空状态
 * - 场景切换时重置状态
 * 
 * 调用时机（在 WndProc 中）：
 * ```cpp
 * case WM_KILLFOCUS:
 *     ClearMouseStates();
 *     break;
 * ```
 */
void ClearMouseStates();

/* ============================================================================
 * 常见使用模式
 * ============================================================================
 * 
 * 1. 检测按钮点击：
 * 
 * ```cpp
 * void ProcessUiInput()
 * {
 *     if (IsMouseLButtonDown())
 *     {
 *         PressButtons(GetMouseX(), GetMouseY());
 *     }
 * }
 * 
 * void PressButtons(int mouseX, int mouseY)
 * {
 *     for (Button* btn : buttons)
 *     {
 *         if (mouseX >= btn->x && mouseX <= btn->x + btn->width &&
 *             mouseY >= btn->y && mouseY <= btn->y + btn->height)
 *         {
 *             btn->onClick();  // 触发按钮回调
 *         }
 *     }
 * }
 * ```
 * 
 * 2. 鼠标瞄准：
 * 
 * ```cpp
 * void UpdatePlayer()
 * {
 *     Player* player = GetPlayer();
 *     
 *     // 计算玩家到鼠标的方向
 *     Vector2 playerCenter = {
 *         player->x + player->width / 2,
 *         player->y + player->height / 2
 *     };
 *     
 *     Vector2 mousePos = {
 *         (double)GetMouseX(),
 *         (double)GetMouseY()
 *     };
 *     
 *     Vector2 direction = {
 *         mousePos.x - playerCenter.x,
 *         mousePos.y - playerCenter.y
 *     };
 *     
 *     // 归一化方向
 *     direction = Normalize(direction);
 *     
 *     // 让玩家面向鼠标
 *     player->rotation = atan2(direction.y, direction.x);
 * }
 * ```
 * 
 * 3. 鼠标点击发射：
 * 
 * ```cpp
 * void UpdatePlayer()
 * {
 *     if (IsMouseLButtonDown())
 *     {
 *         Player* player = GetPlayer();
 *         
 *         // 向鼠标位置发射子弹
 *         Vector2 target = {
 *             (double)GetMouseX(),
 *             (double)GetMouseY()
 *         };
 *         
 *         FireBulletTowards(player->position, target);
 *     }
 * }
 * ```
 * 
 * 4. 检测鼠标悬停：
 * 
 * ```cpp
 * bool IsMouseOverButton(Button* btn)
 * {
 *     int x = GetMouseX();
 *     int y = GetMouseY();
 *     
 *     return (x >= btn->x && x <= btn->x + btn->width &&
 *             y >= btn->y && y <= btn->y + btn->height);
 * }
 * 
 * void RenderButton(Button* btn)
 * {
 *     if (IsMouseOverButton(btn))
 *     {
 *         // 鼠标悬停时高亮显示
 *         DrawButtonHighlight(btn);
 *     }
 *     
 *     DrawButtonNormal(btn);
 * }
 * ```
 * 
 * ============================================================================
 */

/* ============================================================================
 * 进阶功能（可选实现）
 * ============================================================================
 * 
 * 1. 鼠标滚轮支持：
 * 
 * ```cpp
 * // 在 mouse.h 中添加
 * int GetMouseWheelDelta();  // 获取滚轮滚动量
 * 
 * // 在 WndProc 中处理 WM_MOUSEWHEEL 消息
 * case WM_MOUSEWHEEL:
 *     MouseWheel(hWnd, wParam, lParam);
 *     break;
 * ```
 * 
 * 用途：
 * - 缩放视图
 * - 切换武器
 * - 菜单滚动
 * 
 * 2. 双击检测：
 * 
 * ```cpp
 * bool IsMouseLButtonDoubleClick();
 * 
 * // 在 WndProc 中处理 WM_LBUTTONDBLCLK 消息
 * case WM_LBUTTONDBLCLK:
 *     LButtonDoubleClick(hWnd, wParam, lParam);
 *     break;
 * ```
 * 
 * 3. 鼠标拖拽系统：
 * 
 * ```cpp
 * bool IsMouseDragging();
 * Vector2 GetDragStart();
 * Vector2 GetDragCurrent();
 * Vector2 GetDragDelta();
 * ```
 * 
 * 4. 光标显示/隐藏：
 * 
 * ```cpp
 * void ShowMouseCursor(bool show);
 * 
 * // 实现
 * void ShowMouseCursor(bool show)
 * {
 *     ShowCursor(show ? TRUE : FALSE);
 * }
 * ```
 * 
 * 用途：
 * - 全屏游戏中隐藏光标
 * - 使用自定义光标图标
 * 
 * 5. 鼠标限制区域：
 * 
 * ```cpp
 * void ClipMouseToWindow(HWND hWnd);
 * 
 * // 实现
 * void ClipMouseToWindow(HWND hWnd)
 * {
 *     RECT rect;
 *     GetClientRect(hWnd, &rect);
 *     ClientToScreen(hWnd, (POINT*)&rect.left);
 *     ClientToScreen(hWnd, (POINT*)&rect.right);
 *     ClipCursor(&rect);
 * }
 * ```
 * 
 * 用途：
 * - 防止鼠标移出游戏窗口
 * - 全屏游戏必需
 * 
 * ============================================================================
 */

/* ============================================================================
 * 使用技巧
 * ============================================================================
 * 
 * 1. 检测"点击"而非"按下"：
 * 
 * ```cpp
 * static bool wasPressed = false;
 * 
 * bool IsMouseClicked()
 * {
 *     bool isPressed = IsMouseLButtonDown();
 *     bool clicked = isPressed && !wasPressed;  // 当前按下，之前未按下
 *     wasPressed = isPressed;
 *     return clicked;
 * }
 * ```
 * 
 * 2. 防止穿透点击：
 * 
 * ```cpp
 * // 如果点击了 UI，不要处理游戏逻辑
 * bool clickedUI = false;
 * 
 * // 先处理 UI
 * if (IsMouseLButtonDown())
 * {
 *     if (ClickButton())  // 如果点击了按钮
 *         clickedUI = true;
 * }
 * 
 * // 再处理游戏逻辑
 * if (!clickedUI && IsMouseLButtonDown())
 * {
 *     // 处理游戏中的点击
 * }
 * ```
 * 
 * 3. 调试鼠标位置：
 * 
 * ```cpp
 * // 在屏幕上显示鼠标坐标
 * TCHAR buffer[64];
 * swprintf_s(buffer, TEXT("Mouse: (%d, %d)"), GetMouseX(), GetMouseY());
 * DrawText(hdc, buffer, -1, &rect, DT_LEFT | DT_TOP);
 * ```
 * 
 * ============================================================================
 */
