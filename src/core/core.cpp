#include "core.h"

#include "../game_object/player.h"
#include "../game_object/enemy.h"
#include "../game_object/bullet.h"
#include "../util/config.h"
#include "../util/util.h"

#include <SDL.h>

namespace
{
    void ResetGame()
    {
        CreatePlayer();
        ClearEnemies();
        ClearBullets();
    }

    void CheckCollision_Player_Enemies()
    {
        Player* player = GetPlayer();
        if (!player)
            return;

        Rect playerRect = CreateRect(player->position, player->width, player->height);
        auto& enemies = GetEnemies();

        for (size_t i = 0; i < enemies.size();)
        {
            Rect enemyRect = CreateRect(enemies[i].position, enemies[i].width, enemies[i].height);
            if (IsRectRectCollision(playerRect, enemyRect))
            {
                player->attributes.health -= 1;
                player->attributes.score += enemies[i].attributes.score;
                enemies.erase(enemies.begin() + static_cast<int>(i));

                if (player->attributes.health <= 0)
                {
                    ResetGame();
                    return;
                }
                continue;
            }
            i++;
        }
    }

    void CheckCollision_Bullets_Enemies()
    {
        Player* player = GetPlayer();
        if (!player)
            return;

        auto& bullets = GetBullets();
        auto& enemies = GetEnemies();

        for (size_t bi = 0; bi < bullets.size();)
        {
            Circle bulletCircle = CreateCircle(bullets[bi].position, bullets[bi].radius);
            bool bulletDestroyed = false;

            for (size_t ei = 0; ei < enemies.size(); ++ei)
            {
                Rect enemyRect = CreateRect(enemies[ei].position, enemies[ei].width, enemies[ei].height);
                if (!IsRectCircleCollision(enemyRect, bulletCircle))
                    continue;

                enemies[ei].attributes.health -= bullets[bi].damage;
                if (enemies[ei].attributes.health <= 0)
                {
                    player->attributes.score += enemies[ei].attributes.score;
                    enemies.erase(enemies.begin() + static_cast<int>(ei));
                }

                bullets.erase(bullets.begin() + static_cast<int>(bi));
                bulletDestroyed = true;
                break;
            }

            if (!bulletDestroyed)
                bi++;
        }
    }
}

void GameInit()
{
    ResetGame();
}

void GameUpdate(double deltaTime)
{
    UpdatePlayer(deltaTime);
    UpdateEnemies(deltaTime);
    UpdateBullets(deltaTime);

    CheckCollision_Player_Enemies();
    CheckCollision_Bullets_Enemies();
}

void GameRender(SDL_Renderer* renderer)
{
    if (!renderer)
        return;

    SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, 255);
    SDL_RenderClear(renderer);

    RenderPlayer(renderer);
    RenderEnemies(renderer);
    RenderBullets(renderer);
}

void GameShutdown()
{
    DestroyPlayer();
    ClearEnemies();
    ClearBullets();
}
