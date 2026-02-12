#include "input.h"

#include <array>

namespace
{
    // 存储所有键盘键的按下状态（true=按下，false=未按下）
    std::array<bool, SDL_NUM_SCANCODES> g_keys = {};
    
    // 存储鼠标按钮的按下状态（8个按钮）
    std::array<bool, 8> g_mouseButtons = {};
    
    // 当前鼠标坐标
    int g_mouseX = 0;
    int g_mouseY = 0;
}

// 输入系统初始化（目前预留用于未来的逻辑）
void InputBeginFrame()
{
    // 预留给未来的每帧逻辑
}

// 处理 SDL 事件并更新输入状态
void InputProcessEvent(const SDL_Event& e)
{
    switch (e.type)
    {
    case SDL_KEYDOWN:  // 键盘按下
        if (e.key.keysym.scancode >= 0 && e.key.keysym.scancode < SDL_NUM_SCANCODES)
            g_keys[e.key.keysym.scancode] = true;
        break;
        
    case SDL_KEYUP:  // 键盘释放
        if (e.key.keysym.scancode >= 0 && e.key.keysym.scancode < SDL_NUM_SCANCODES)
            g_keys[e.key.keysym.scancode] = false;
        break;
        
    case SDL_MOUSEBUTTONDOWN:  // 鼠标按钮按下
        if (e.button.button < g_mouseButtons.size())
            g_mouseButtons[e.button.button] = true;
        break;
        
    case SDL_MOUSEBUTTONUP:  // 鼠标按钮释放
        if (e.button.button < g_mouseButtons.size())
            g_mouseButtons[e.button.button] = false;
        break;
        
    case SDL_MOUSEMOTION:  // 鼠标移动
        g_mouseX = e.motion.x;
        g_mouseY = e.motion.y;
        break;
        
    default:
        break;
    }
}

// 查询某个键是否按下
bool IsKeyDown(SDL_Scancode key)
{
    if (key < 0 || key >= SDL_NUM_SCANCODES)
        return false;
    return g_keys[key];
}

// 查询某个鼠标按钮是否按下
bool IsMouseDown(Uint8 button)
{
    if (button >= g_mouseButtons.size())
        return false;
    return g_mouseButtons[button];
}

// 获取当前鼠标坐标（以引用参数方式返回）
void GetMousePos(int& x, int& y)
{
    x = g_mouseX;
    y = g_mouseY;
}
