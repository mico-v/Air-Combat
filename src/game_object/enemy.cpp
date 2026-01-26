#include "enemy.h"

#include "../core/core.h"
#include "../util/config.h"
#include "../util/util.h"

#include <algorithm>

namespace
{
    std::vector<Enemy*> g_enemies;
    double g_lastSpawnTime = 0.0;
}

void CreateEnemy(double x, double y)
{
    Enemy* e = new Enemy();
    e->position = {x, y};
    e->width = ENEMY_WIDTH;
    e->height = ENEMY_HEIGHT;
    e->attributes.health = ENEMY_HEALTH;
    e->attributes.score = ENEMY_SCORE;
    e->attributes.speed = ENEMY_SPEED;
    e->attributes.maxBulletCd = 0.0;
    e->attributes.bulletCd = 0.0;

    g_enemies.push_back(e);
}

void CreateRandomEnemy()
{
    CreateEnemy(
        GetRandomDouble(30, GAME_WIDTH - ENEMY_WIDTH - 30),
        -100);
}

std::vector<Enemy*> GetEnemies()
{
    return g_enemies;
}

void DestroyEnemy(Enemy* enemy)
{
    auto it = std::find(g_enemies.begin(), g_enemies.end(), enemy);
    if (it == g_enemies.end())
        return;
    delete *it;
    g_enemies.erase(it);
}

void DestroyEnemies()
{
    for (Enemy* e : g_enemies)
        delete e;
    g_enemies.clear();
}

void UpdateEnemies(double deltaTime)
{
    const double now = GetGameTime();
    if (now - g_lastSpawnTime > ENEMY_SPAWN_INTERVAL)
    {
        CreateRandomEnemy();
        g_lastSpawnTime = now;
    }

    for (size_t i = 0; i < g_enemies.size();)
    {
        Enemy* e = g_enemies[i];
        e->position.y += e->attributes.speed * deltaTime;

        if (e->position.y > GAME_HEIGHT + 50)
        {
            delete e;
            g_enemies.erase(g_enemies.begin() + (int)i);
            continue;
        }
        i++;
    }
}

void RenderEnemies(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    (void)hdc_loadBmp;
    for (Enemy* e : g_enemies)
    {
        RECT r;
        r.left = (LONG)e->position.x;
        r.top = (LONG)e->position.y;
        r.right = (LONG)(e->position.x + e->width);
        r.bottom = (LONG)(e->position.y + e->height);

        HBRUSH brush = CreateSolidBrush(RGB(220, 60, 60));
        FillRect(hdc_memBuffer, &r, brush);
        DeleteObject(brush);
    }
}
