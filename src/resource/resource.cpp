#include "resource.h"

HBITMAP g_bmpStartButton = nullptr;
HBITMAP g_bmpPlayer = nullptr;
HBITMAP g_bmpEnemy = nullptr;

void InitResourceSystem(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    (void)hWnd;
    (void)wParam;
    (void)lParam;

    // TODO: load bitmaps from .rc or from files (LoadImage/LoadBitmap).
}

void ShutdownResourceSystem()
{
    if (g_bmpStartButton)
    {
        DeleteObject(g_bmpStartButton);
        g_bmpStartButton = nullptr;
    }
    if (g_bmpPlayer)
    {
        DeleteObject(g_bmpPlayer);
        g_bmpPlayer = nullptr;
    }
    if (g_bmpEnemy)
    {
        DeleteObject(g_bmpEnemy);
        g_bmpEnemy = nullptr;
    }
}
