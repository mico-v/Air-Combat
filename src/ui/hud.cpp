#include "hud.h"

#include "../util/config.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

namespace
{
    TTF_Font* g_hudFont = nullptr;
}

void HudInit()
{
    if (TTF_Init() != 0) {
        SDL_Log("HudInit: TTF_Init() failed");
        return;
    }

    // 使用项目 resource 目录里的字体
    const char* fontPath = "resource/simhei.ttf";
    g_hudFont = TTF_OpenFont(fontPath, 24);
    if (!g_hudFont) {
        SDL_Log("HudInit: Failed to load font from %s - %s", fontPath, TTF_GetError());
        return;
    }
}

void HudShutdown()
{
    if (g_hudFont)
    {
        TTF_CloseFont(g_hudFont);
        g_hudFont = nullptr;
    }
    TTF_Quit();
}

void HudRender(SDL_Renderer* renderer, int score)
{
    if (!renderer || !g_hudFont)
        return;

    std::string text = "Score: " + std::to_string(score);
    SDL_Color color{COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, 255};

    SDL_Surface* surface = TTF_RenderText_Blended(g_hudFont, text.c_str(), color);
    if (!surface)
        return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst{10, 10, surface->w, surface->h};
    SDL_FreeSurface(surface);

    if (!texture)
        return;

    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}
