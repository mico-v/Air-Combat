#pragma once

#include "../util/type.h"

#include <windows.h>
#include <vector>

struct Bullet
{
    Vector2 position;
    double radius;
    int damage;
    double speed;
};

void CreateBullet(double x, double y, int damage, double speed);
void UpdateBullets(double deltaTime);
void RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp);
void DestroyBullet(Bullet* bullet);
void DestroyBullets();
std::vector<Bullet*> GetBullets();
