#include "input.h"

#include <array>

namespace
{
    std::array<bool, SDL_NUM_SCANCODES> g_keys = {};
    std::array<bool, 8> g_mouseButtons = {};
    int g_mouseX = 0;
    int g_mouseY = 0;
}

void InputBeginFrame()
{
    // Reserved for future per-frame logic.
}

void InputProcessEvent(const SDL_Event& e)
{
    switch (e.type)
    {
    case SDL_KEYDOWN:
        if (e.key.keysym.scancode >= 0 && e.key.keysym.scancode < SDL_NUM_SCANCODES)
            g_keys[e.key.keysym.scancode] = true;
        break;
    case SDL_KEYUP:
        if (e.key.keysym.scancode >= 0 && e.key.keysym.scancode < SDL_NUM_SCANCODES)
            g_keys[e.key.keysym.scancode] = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (e.button.button < g_mouseButtons.size())
            g_mouseButtons[e.button.button] = true;
        break;
    case SDL_MOUSEBUTTONUP:
        if (e.button.button < g_mouseButtons.size())
            g_mouseButtons[e.button.button] = false;
        break;
    case SDL_MOUSEMOTION:
        g_mouseX = e.motion.x;
        g_mouseY = e.motion.y;
        break;
    default:
        break;
    }
}

bool IsKeyDown(SDL_Scancode key)
{
    if (key < 0 || key >= SDL_NUM_SCANCODES)
        return false;
    return g_keys[key];
}

bool IsMouseDown(Uint8 button)
{
    if (button >= g_mouseButtons.size())
        return false;
    return g_mouseButtons[button];
}

void GetMousePos(int& x, int& y)
{
    x = g_mouseX;
    y = g_mouseY;
}
