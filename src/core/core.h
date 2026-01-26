#pragma once

#include <windows.h>

// Game lifecycle entry points called from Win32 WndProc.
void GameInit(HWND hWnd, WPARAM wParam, LPARAM lParam);
void GameLoop(HWND hWnd);
void GameRender(HWND hWnd, WPARAM wParam, LPARAM lParam);

// Time helpers.
double GetGameTime();
double GetDeltaTime();
