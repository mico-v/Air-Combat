#include "core.h"

#include "../util/config.h"
#include "../util/keyboard.h"
#include "../util/mouse.h"

#include <windows.h>

static const wchar_t* kWindowClassName = L"AirCombatWindowClass";

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        GameInit(hWnd, wParam, lParam);
        SetTimer(hWnd, 1, TIMER_INTERVAL, nullptr);
        return 0;

    case WM_TIMER:
        GameLoop(hWnd);
        return 0;

    case WM_PAINT:
        GameRender(hWnd, wParam, lParam);
        return 0;

    case WM_KEYDOWN:
        KeyDown(hWnd, wParam, lParam);
        return 0;
    case WM_KEYUP:
        KeyUp(hWnd, wParam, lParam);
        return 0;

    case WM_MOUSEMOVE:
        MouseMove(hWnd, wParam, lParam);
        return 0;
    case WM_LBUTTONDOWN:
        LButtonDown(hWnd, wParam, lParam);
        return 0;
    case WM_LBUTTONUP:
        LButtonUp(hWnd, wParam, lParam);
        return 0;
    case WM_RBUTTONDOWN:
        RButtonDown(hWnd, wParam, lParam);
        return 0;
    case WM_RBUTTONUP:
        RButtonUp(hWnd, wParam, lParam);
        return 0;

    case WM_KILLFOCUS:
        ClearKeyStates();
        ClearMouseStates();
        return 0;

    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;

    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = kWindowClassName;

    RegisterClassExW(&wcex);

    RECT rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindowW(
        kWindowClassName,
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hWnd)
        return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
