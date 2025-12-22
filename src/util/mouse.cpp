/**
 * @file mouse.cpp
 * @brief 鼠标输入系统实现文件
 * 
 * 这个文件实现了鼠标输入的状态管理。
 */

#include "mouse.h"

/* ============================================================================
 * 内部状态存储
 * ============================================================================
 */

/**
 * @brief 鼠标当前位置
 * 
 * 存储鼠标在窗口客户区内的坐标（像素单位）
 */
static int mouseX = 0;
static int mouseY = 0;

/**
 * @brief 鼠标按键状态
 * 
 * 存储各个鼠标按键的按下/释放状态
 */
static bool isLButtonDown = false;  // 左键状态
static bool isRButtonDown = false;  // 右键状态
static bool isMButtonDown = false;  // 中键状态（可选）

/* ============================================================================
 * 辅助函数：从 lParam 提取鼠标坐标
 * ============================================================================
 */

/**
 * @brief 从 lParam 提取鼠标 X 坐标
 * 
 * 在 Win32 中，WM_MOUSEMOVE 等消息的 lParam 包含鼠标坐标：
 * - 低 16 位：X 坐标
 * - 高 16 位：Y 坐标
 * 
 * LOWORD 宏提取低 16 位
 */
static int ExtractMouseX(LPARAM lParam)
{
    return LOWORD(lParam);
}

/**
 * @brief 从 lParam 提取鼠标 Y 坐标
 * 
 * HIWORD 宏提取高 16 位
 */
static int ExtractMouseY(LPARAM lParam)
{
    return HIWORD(lParam);
}

/* ============================================================================
 * 鼠标状态设置函数实现
 * ============================================================================
 */

/**
 * @brief 处理鼠标移动事件
 * 
 * 实现说明：
 * 1. 从 lParam 提取鼠标坐标
 * 2. 更新全局鼠标位置变量
 */
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 提取鼠标坐标
    mouseX = ExtractMouseX(lParam);
    mouseY = ExtractMouseY(lParam);
    
    // 💡 调试技巧：
    // 如果想查看鼠标位置，可以添加日志输出：
    // Log(1, TEXT("Mouse: (%d, %d)"), mouseX, mouseY);
}

/**
 * @brief 处理鼠标左键按下事件
 * 
 * 实现说明：
 * 1. 设置左键状态为 true
 * 2. 更新鼠标位置（因为按下时可能鼠标也在移动）
 */
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 设置左键状态
    isLButtonDown = true;
    
    // 更新鼠标位置
    mouseX = ExtractMouseX(lParam);
    mouseY = ExtractMouseY(lParam);
    
    // 💡 调试技巧：
    // Log(1, TEXT("Left Button Down at (%d, %d)"), mouseX, mouseY);
}

/**
 * @brief 处理鼠标左键释放事件
 * 
 * 实现说明：
 * 设置左键状态为 false
 */
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 设置左键状态
    isLButtonDown = false;
    
    // 更新鼠标位置
    mouseX = ExtractMouseX(lParam);
    mouseY = ExtractMouseY(lParam);
    
    // 💡 调试技巧：
    // Log(1, TEXT("Left Button Up at (%d, %d)"), mouseX, mouseY);
}

/**
 * @brief 处理鼠标右键按下事件
 */
void RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 设置右键状态
    isRButtonDown = true;
    
    // 更新鼠标位置
    mouseX = ExtractMouseX(lParam);
    mouseY = ExtractMouseY(lParam);
}

/**
 * @brief 处理鼠标右键释放事件
 */
void RButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 设置右键状态
    isRButtonDown = false;
    
    // 更新鼠标位置
    mouseX = ExtractMouseX(lParam);
    mouseY = ExtractMouseY(lParam);
}

/* ============================================================================
 * 鼠标状态查询函数实现
 * ============================================================================
 */

/**
 * @brief 获取鼠标 X 坐标
 * 
 * 实现说明：
 * 直接返回存储的鼠标 X 坐标
 */
int GetMouseX()
{
    return mouseX;
}

/**
 * @brief 获取鼠标 Y 坐标
 * 
 * 实现说明：
 * 直接返回存储的鼠标 Y 坐标
 */
int GetMouseY()
{
    return mouseY;
}

/**
 * @brief 检查鼠标左键是否被按下
 * 
 * 实现说明：
 * 返回存储的左键状态
 */
bool IsMouseLButtonDown()
{
    return isLButtonDown;
}

/**
 * @brief 检查鼠标右键是否被按下
 */
bool IsMouseRButtonDown()
{
    return isRButtonDown;
}

/* ============================================================================
 * 辅助函数实现
 * ============================================================================
 */

/**
 * @brief 清空鼠标状态
 * 
 * 用途：
 * - 窗口失去焦点时调用
 * - 场景切换时调用
 * 
 * 实现说明：
 * 将所有按键状态设置为 false，鼠标位置保持不变
 */
void ClearMouseStates()
{
    // 清空所有按键状态
    isLButtonDown = false;
    isRButtonDown = false;
    isMButtonDown = false;
    
    // 鼠标位置不清空（保持最后记录的位置）
    // 如果需要也可以重置为 (0, 0)
}

/* ============================================================================
 * 进阶功能实现示例（可选）
 * ============================================================================
 * 
 * 以下是一些进阶功能的实现，初学者可以跳过。
 * 
 * 1. 检测鼠标"点击"（按下并松开）：
 * 
 * ```cpp
 * // 需要保存上一帧的按键状态
 * static bool prevLButtonDown = false;
 * 
 * // 每帧结束时调用
 * void UpdateMouseStates()
 * {
 *     prevLButtonDown = isLButtonDown;
 * }
 * 
 * // 检测是否刚刚点击（这一帧按下，上一帧未按下）
 * bool IsMouseLButtonPressed()
 * {
 *     return isLButtonDown && !prevLButtonDown;
 * }
 * 
 * // 检测是否刚刚松开
 * bool IsMouseLButtonReleased()
 * {
 *     return !isLButtonDown && prevLButtonDown;
 * }
 * ```
 * 
 * 2. 鼠标拖拽系统：
 * 
 * ```cpp
 * static bool isDragging = false;
 * static int dragStartX = 0;
 * static int dragStartY = 0;
 * 
 * // 开始拖拽
 * void StartDrag()
 * {
 *     if (IsMouseLButtonDown() && !isDragging)
 *     {
 *         isDragging = true;
 *         dragStartX = GetMouseX();
 *         dragStartY = GetMouseY();
 *     }
 * }
 * 
 * // 结束拖拽
 * void EndDrag()
 * {
 *     if (!IsMouseLButtonDown())
 *     {
 *         isDragging = false;
 *     }
 * }
 * 
 * // 获取拖拽距离
 * void GetDragDelta(int* dx, int* dy)
 * {
 *     if (isDragging)
 *     {
 *         *dx = GetMouseX() - dragStartX;
 *         *dy = GetMouseY() - dragStartY;
 *     }
 *     else
 *     {
 *         *dx = 0;
 *         *dy = 0;
 *     }
 * }
 * ```
 * 
 * 3. 鼠标滚轮支持：
 * 
 * ```cpp
 * static int mouseWheelDelta = 0;
 * 
 * // 在 WndProc 中处理 WM_MOUSEWHEEL
 * void MouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
 * {
 *     // GET_WHEEL_DELTA_WPARAM 提取滚轮滚动量
 *     mouseWheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
 *     
 *     // 正数表示向上滚，负数表示向下滚
 *     // 通常是 120 的倍数
 * }
 * 
 * int GetMouseWheelDelta()
 * {
 *     int delta = mouseWheelDelta;
 *     mouseWheelDelta = 0;  // 读取后清零
 *     return delta;
 * }
 * ```
 * 
 * 4. 检测双击：
 * 
 * ```cpp
 * static bool isDoubleClick = false;
 * 
 * // 在 WndProc 中处理 WM_LBUTTONDBLCLK
 * void LButtonDoubleClick(HWND hWnd, WPARAM wParam, LPARAM lParam)
 * {
 *     isDoubleClick = true;
 *     mouseX = ExtractMouseX(lParam);
 *     mouseY = ExtractMouseY(lParam);
 * }
 * 
 * bool IsMouseLButtonDoubleClick()
 * {
 *     bool result = isDoubleClick;
 *     isDoubleClick = false;  // 读取后清零
 *     return result;
 * }
 * ```
 * 
 * 5. 鼠标在游戏区域内：
 * 
 * ```cpp
 * bool IsMouseInGameArea()
 * {
 *     return (mouseX >= GAME_OFFSET_X && 
 *             mouseX < GAME_OFFSET_X + GAME_WIDTH &&
 *             mouseY >= GAME_OFFSET_Y && 
 *             mouseY < GAME_OFFSET_Y + GAME_HEIGHT);
 * }
 * ```
 * 
 * ============================================================================
 */

/* ============================================================================
 * 使用示例
 * ============================================================================
 * 
 * 示例 1：在 WndProc 中处理鼠标消息
 * 
 * ```cpp
 * LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
 * {
 *     switch (message)
 *     {
 *     case WM_MOUSEMOVE:
 *         MouseMove(hWnd, wParam, lParam);
 *         break;
 *         
 *     case WM_LBUTTONDOWN:
 *         LButtonDown(hWnd, wParam, lParam);
 *         break;
 *         
 *     case WM_LBUTTONUP:
 *         LButtonUp(hWnd, wParam, lParam);
 *         break;
 *         
 *     case WM_RBUTTONDOWN:
 *         RButtonDown(hWnd, wParam, lParam);
 *         break;
 *         
 *     case WM_RBUTTONUP:
 *         RButtonUp(hWnd, wParam, lParam);
 *         break;
 *         
 *     case WM_KILLFOCUS:
 *         ClearMouseStates();
 *         break;
 *     
 *     // 其他消息处理...
 *     }
 *     return DefWindowProc(hWnd, message, wParam, lParam);
 * }
 * ```
 * 
 * 示例 2：检测按钮点击
 * 
 * ```cpp
 * void ProcessUiInput()
 * {
 *     // 检查鼠标左键是否按下
 *     if (IsMouseLButtonDown())
 *     {
 *         // 获取鼠标位置
 *         int x = GetMouseX();
 *         int y = GetMouseY();
 *         
 *         // 检测是否点击了按钮
 *         for (Button* btn : GetButtons())
 *         {
 *             if (x >= btn->x && x <= btn->x + btn->width &&
 *                 y >= btn->y && y <= btn->y + btn->height)
 *             {
 *                 // 点击了这个按钮
 *                 btn->onClick(btn);
 *                 break;
 *             }
 *         }
 *     }
 * }
 * ```
 * 
 * 示例 3：鼠标瞄准射击
 * 
 * ```cpp
 * void UpdatePlayer(double deltaTime)
 * {
 *     Player* player = GetPlayer();
 *     
 *     // 如果按下鼠标左键，向鼠标位置发射子弹
 *     if (IsMouseLButtonDown())
 *     {
 *         // 检查射击冷却
 *         if (player->bulletCd <= 0)
 *         {
 *             // 计算玩家中心点
 *             double centerX = player->x + player->width / 2;
 *             double centerY = player->y + player->height / 2;
 *             
 *             // 计算朝向鼠标的方向
 *             double dirX = GetMouseX() - centerX;
 *             double dirY = GetMouseY() - centerY;
 *             
 *             // 归一化方向
 *             Vector2 direction = Normalize({dirX, dirY});
 *             
 *             // 发射子弹
 *             CreateBulletWithDirection(centerX, centerY, direction);
 *             
 *             // 重置冷却
 *             player->bulletCd = player->maxBulletCd;
 *         }
 *     }
 *     
 *     // 更新冷却时间
 *     if (player->bulletCd > 0)
 *         player->bulletCd -= deltaTime;
 * }
 * ```
 * 
 * ============================================================================
 */
