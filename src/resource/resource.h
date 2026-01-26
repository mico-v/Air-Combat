#pragma once

#include <windows.h>

// Resource system.
// This project currently uses simple primitives for rendering.
// The bitmap handles are reserved for the next step (loading real BMP assets).

extern HBITMAP g_bmpStartButton;
extern HBITMAP g_bmpPlayer;
extern HBITMAP g_bmpEnemy;

void InitResourceSystem(HWND hWnd, WPARAM wParam, LPARAM lParam);
void ShutdownResourceSystem();
