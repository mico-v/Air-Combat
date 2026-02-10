#pragma once

struct SDL_Renderer;

void GameInit();
void GameUpdate(double deltaTime);
void GameRender(SDL_Renderer* renderer);
void GameShutdown();
