#pragma once

#include <windows.h>
#include <tchar.h>

// Minimal logging system.
// For now it writes to OutputDebugString and is safe to call from anywhere.

void InitLogSystem(HWND hWnd);
void Log(int statusBarIndex, const TCHAR* format, ...);
