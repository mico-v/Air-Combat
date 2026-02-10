#include "enemy.h"

#include "../util/config.h"
#include "../util/util.h"

#include <SDL.h>

namespace
{
    std::vector<Enemy> g_enemies;
    double g_spawnTimer = 0.0;
}

void CreateEnemy(double x, double y)
{
    Enemy e = {};
    e.position = {x, y};
    e.width = ENEMY_WIDTH;
    e.height = ENEMY_HEIGHT;
    e.attributes.health = ENEMY_HEALTH;
    e.attributes.score = ENEMY_SCORE;
    e.attributes.speed = ENEMY_SPEED;
    e.attributes.maxBulletCd = 0.0;
    e.attributes.bulletCd = 0.0;

    g_enemies.push_back(e);
}

void CreateRandomEnemy()
{
    CreateEnemy(
        GetRandomDouble(30.0, GAME_WIDTH - ENEMY_WIDTH - 30.0),
        -100.0);
}

std::vector<Enemy>& GetEnemies()
{
    return g_enemies;
}

void ClearEnemies()
{
    g_enemies.clear();
    g_spawnTimer = 0.0;
}

void UpdateEnemies(double deltaTime)
{
    g_spawnTimer += deltaTime;
    while (g_spawnTimer >= ENEMY_SPAWN_INTERVAL)
    {
        CreateRandomEnemy();
        g_spawnTimer -= ENEMY_SPAWN_INTERVAL;
    }

    for (size_t i = 0; i < g_enemies.size();)
    {
        Enemy& e = g_enemies[i];
        e.position.y += e.attributes.speed * deltaTime;

        if (e.position.y > GAME_HEIGHT + 50.0)
        {
            g_enemies.erase(g_enemies.begin() + static_cast<int>(i));
            continue;
        }
        i++;
    }
}

void RenderEnemies(SDL_Renderer* renderer)
{
    if (!renderer)
        return;

    SDL_SetRenderDrawColor(renderer, 220, 60, 60, 255);
    for (const Enemy& e : g_enemies)
    {
        SDL_Rect r;
        r.x = static_cast<int>(e.position.x);
        r.y = static_cast<int>(e.position.y);
        r.w = static_cast<int>(e.width);
        r.h = static_cast<int>(e.height);
        SDL_RenderFillRect(renderer, &r);
    }
}
