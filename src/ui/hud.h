#pragma once

struct SDL_Renderer;

void HudInit();
void HudShutdown();
void HudRender(SDL_Renderer* renderer, int score);
