#include "core.h"

#include "../resource/resource.h"
#include "../scene/scene.h"
#include "../util/config.h"
#include "info.h"

#include <windows.h>

namespace
{
    double g_gameTimeSeconds = 0.0;
    double g_deltaTimeSeconds = 0.0;

    LARGE_INTEGER g_qpcFreq = {};
    LARGE_INTEGER g_lastCounter = {};
}

static void UpdateTime()
{
    LARGE_INTEGER now = {};
    QueryPerformanceCounter(&now);

    if (g_qpcFreq.QuadPart == 0)
    {
        QueryPerformanceFrequency(&g_qpcFreq);
        g_lastCounter = now;
        g_gameTimeSeconds = 0.0;
        g_deltaTimeSeconds = 0.0;
        return;
    }

    const LONGLONG deltaTicks = now.QuadPart - g_lastCounter.QuadPart;
    g_lastCounter = now;

    g_deltaTimeSeconds = static_cast<double>(deltaTicks) / static_cast<double>(g_qpcFreq.QuadPart);
    if (g_deltaTimeSeconds < 0.0)
        g_deltaTimeSeconds = 0.0;

    g_gameTimeSeconds += g_deltaTimeSeconds;
}

double GetGameTime()
{
    return g_gameTimeSeconds;
}

double GetDeltaTime()
{
    return g_deltaTimeSeconds;
}

void GameInit(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    InitLogSystem(hWnd);
    InitResourceSystem(hWnd, wParam, lParam);

    // Start from StartScene.
    ChangeScene(SceneId::StartScene);
}

void GameLoop(HWND hWnd)
{
    UpdateTime();

    SceneLoop(GetDeltaTime());

    // Trigger WM_PAINT.
    RECT rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    InvalidateRect(hWnd, &rect, FALSE);
}

void GameRender(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps = {};
    HDC hdcWindow = BeginPaint(hWnd, &ps);
    if (!hdcWindow)
        return;

    HDC hdcMem = CreateCompatibleDC(hdcWindow);
    HDC hdcLoad = CreateCompatibleDC(hdcWindow);
    HBITMAP backBuffer = CreateCompatibleBitmap(hdcWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

    HGDIOBJ oldMemBmp = SelectObject(hdcMem, backBuffer);

    // Clear background.
    RECT full = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    HBRUSH brush = CreateSolidBrush(COLOR_WHITE);
    FillRect(hdcMem, &full, brush);
    DeleteObject(brush);

    RenderScene(hdcMem, hdcLoad);

    BitBlt(hdcWindow, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdcMem, 0, 0, SRCCOPY);

    // Cleanup.
    SelectObject(hdcMem, oldMemBmp);
    DeleteObject(backBuffer);
    DeleteDC(hdcLoad);
    DeleteDC(hdcMem);
    EndPaint(hWnd, &ps);
}
