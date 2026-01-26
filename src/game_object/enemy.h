#pragma once

#include "../util/type.h"

#include <windows.h>
#include <vector>

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
void RenderEnemies(HDC hdc_memBuffer, HDC hdc_loadBmp);
void DestroyEnemy(Enemy* enemy);
void DestroyEnemies();
std::vector<Enemy*> GetEnemies();
