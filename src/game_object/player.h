#pragma once

#include "../util/type.h"

#include <windows.h>

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
void RenderPlayer(HDC hdc_memBuffer, HDC hdc_loadBmp);
void DestroyPlayer();
