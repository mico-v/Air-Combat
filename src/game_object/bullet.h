#pragma once

#include "../util/type.h"

#include <vector>

struct SDL_Renderer;

struct Bullet
{
    Vector2 position;
    double radius;
    int damage;
    double speed;
};

void CreateBullet(double x, double y, int damage, double speed);
void UpdateBullets(double deltaTime);
void RenderBullets(SDL_Renderer* renderer);
void ClearBullets();
std::vector<Bullet>& GetBullets();
