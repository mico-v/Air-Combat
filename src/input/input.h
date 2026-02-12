#pragma once

#include <SDL.h>

// 输入系统初始化（在每帧开始调用）
void InputBeginFrame();

// 处理单个 SDL 事件（键盘、鼠标、窗口事件等）
void InputProcessEvent(const SDL_Event& e);

// 查询某个键是否按下（利用扫描码指定，如 SDL_SCANCODE_W）
bool IsKeyDown(SDL_Scancode key);

// 查询某个鼠标按钮是否按下
bool IsMouseDown(Uint8 button);

// 获取当前鼠标坐标（以引用参数方式返回）
void GetMousePos(int& x, int& y);
