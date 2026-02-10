#pragma once

#include "../util/type.h"

#include <vector>

struct SDL_Renderer;

struct Enemy
{
    Vector2 position;
    double width;
    double height;
    Attribute attributes;
};

void CreateEnemy(double x, double y);
void CreateRandomEnemy();
void UpdateEnemies(double deltaTime);
void RenderEnemies(SDL_Renderer* renderer);
void ClearEnemies();
std::vector<Enemy>& GetEnemies();
