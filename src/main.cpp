#include "core/core.h"
#include "input/input.h"
#include "util/config.h"

#include <SDL.h>

// 游戏主程序入口
int main(int argc, char** argv)
{
    (void)argc;  // 消除未使用参数警告
    (void)argv;

    // ===== SDL 初始化 =====
    // 初始化 SDL2 库，启用视频和定时器功能
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        return 1;  // 初始化失败

    // 创建游戏窗口
    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE,                       // 窗口标题
        SDL_WINDOWPOS_CENTERED,             // 屏幕中央位置
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,                       // 窗口宽度
        WINDOW_HEIGHT,                      // 窗口高度
        SDL_WINDOW_SHOWN);                  // 窗口可见

    if (!window)
    {
        SDL_Quit();
        return 1;
    }

    // 创建渲染器（用于绘制图形）
    // SDL_RENDERER_ACCELERATED: 使用硬件加速
    // SDL_RENDERER_PRESENTVSYNC: 启用垂直同步（防止撕裂）
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // ===== 游戏初始化 =====
    GameInit();

    // ===== 主游戏循环 =====
    bool running = true;
    
    // 获取 CPU 性能计数器频率（用于计算 deltaTime）
    const double freq = static_cast<double>(SDL_GetPerformanceFrequency());
    Uint64 lastCounter = SDL_GetPerformanceCounter();

    while (running)
    {
        // --- 输入处理 ---
        InputBeginFrame();

        // 处理所有待处理的 SDL 事件
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)  // 窗口关闭按钮
                running = false;
            InputProcessEvent(e);    // 更新输入状态
        }

        // ESC 键退出游戏
        if (IsKeyDown(SDL_SCANCODE_ESCAPE))
            running = false;

        // --- 计算 deltaTime ---
        // 用性能计数器计算精确的帧间隔时间
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = static_cast<double>(now - lastCounter) / freq;
        lastCounter = now;
        
        // 限制单帧最大时间 0.1 秒（防止卡顿时物理跳跃过大）
        if (deltaTime > 0.1)
            deltaTime = 0.1;

        // --- 游戏逻辑更新和渲染 ---
        GameUpdate(deltaTime);
        GameRender(renderer);
        SDL_RenderPresent(renderer);  // 提交渲染到屏幕
    }

    // ===== 清理资源 =====
    GameShutdown();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
