#pragma once

#include "../util/type.h"

struct SDL_Renderer;

struct Player
{
    Vector2 position;
    double width;
    double height;
    Attribute attributes;
};

void CreatePlayer();
Player* GetPlayer();
void UpdatePlayer(double deltaTime);
void RenderPlayer(SDL_Renderer* renderer);
void DestroyPlayer();
