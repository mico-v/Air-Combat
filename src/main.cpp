#include "core/core.h"
#include "input/input.h"
#include "util/config.h"

#include <SDL.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        return 1;

    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        SDL_Quit();
        return 1;
    }

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

    GameInit();

    bool running = true;
    const double freq = static_cast<double>(SDL_GetPerformanceFrequency());
    Uint64 lastCounter = SDL_GetPerformanceCounter();

    while (running)
    {
        InputBeginFrame();

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;
            InputProcessEvent(e);
        }

        if (IsKeyDown(SDL_SCANCODE_ESCAPE))
            running = false;

        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = static_cast<double>(now - lastCounter) / freq;
        lastCounter = now;
        if (deltaTime > 0.1)
            deltaTime = 0.1;

        GameUpdate(deltaTime);
        GameRender(renderer);
        SDL_RenderPresent(renderer);
    }

    GameShutdown();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
