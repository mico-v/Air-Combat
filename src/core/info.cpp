#include "info.h"

#include <cstdarg>

namespace
{
    HWND g_mainHwnd = nullptr;
}

void InitLogSystem(HWND hWnd)
{
    g_mainHwnd = hWnd;
    (void)g_mainHwnd;
}

void Log(int statusBarIndex, const TCHAR* format, ...)
{
    (void)statusBarIndex;

    TCHAR buffer[512] = {0};

    va_list args;
    va_start(args, format);

    // _vsntprintf is widely available on MinGW and MSVC.
    _vsntprintf(buffer, static_cast<int>(sizeof(buffer) / sizeof(buffer[0])) - 1, format, args);
    buffer[(sizeof(buffer) / sizeof(buffer[0])) - 1] = 0;

    va_end(args);

    OutputDebugString(buffer);
    OutputDebugString(TEXT("\r\n"));
}
