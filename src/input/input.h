#pragma once

#include <SDL.h>

void InputBeginFrame();
void InputProcessEvent(const SDL_Event& e);
bool IsKeyDown(SDL_Scancode key);
bool IsMouseDown(Uint8 button);
void GetMousePos(int& x, int& y);
