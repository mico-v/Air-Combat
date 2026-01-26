#include "scene2.h"

#include "scene.h"
#include "../game_object/player.h"
#include "../game_object/enemy.h"
#include "../game_object/bullet.h"
#include "../util/keyboard.h"
#include "../util/util.h"
#include "../util/config.h"

#include <cstddef>
#include <vector>

void LoadScene_GameScene()
{
    CreatePlayer();
    DestroyEnemies();
    DestroyBullets();
}

void UnloadScene_GameScene()
{
    DestroyPlayer();
    DestroyEnemies();
    DestroyBullets();
}

void ProcessUiInput_GameScene()
{
    // ESC -> back to start scene.
    if (GetKeyDown(VK_ESCAPE))
    {
        ChangeScene(SceneId::StartScene);
    }
}

static void CheckCollision_Player_Enemies()
{
    Player* player = GetPlayer();
    if (!player)
        return;

    Rect playerRect = CreateRect(player->position, player->width, player->height);

    // Copy to avoid iterator invalidation when destroying.
    std::vector<Enemy*> enemies = GetEnemies();
    for (Enemy* enemy : enemies)
    {
        Rect enemyRect = CreateRect(enemy->position, enemy->width, enemy->height);
        if (IsRectRectCollision(playerRect, enemyRect))
        {
            player->attributes.health -= 1;
            player->attributes.score += enemy->attributes.score;
            DestroyEnemy(enemy);

            if (player->attributes.health <= 0)
            {
                ChangeScene(SceneId::StartScene);
            }
            break;
        }
    }
}

static void CheckCollision_Bullets_Enemies()
{
    Player* player = GetPlayer();
    if (!player)
        return;

    // NOTE:
    // GetEnemies()/GetBullets() return vectors of raw pointers.
    // If we destroy an enemy and keep iterating the old pointer list, we can
    // easily dereference freed memory. Keep local lists and update them when we
    // destroy things.
    std::vector<Bullet*> bullets = GetBullets();
    std::vector<Enemy*> enemies = GetEnemies();

    for (Bullet* bullet : bullets)
    {
        Circle bulletCircle = CreateCircle(bullet->position, bullet->radius);

        for (size_t i = 0; i < enemies.size(); ++i)
        {
            Enemy* enemy = enemies[i];
            Rect enemyRect = CreateRect(enemy->position, enemy->width, enemy->height);
            if (!IsRectCircleCollision(enemyRect, bulletCircle))
                continue;

            enemy->attributes.health -= bullet->damage;
            if (enemy->attributes.health <= 0)
            {
                player->attributes.score += enemy->attributes.score;
                DestroyEnemy(enemy);
                enemies.erase(enemies.begin() + (int)i);
            }

            DestroyBullet(bullet);
            break;
        }
    }
}

void CheckCollision_GameScene()
{
    CheckCollision_Player_Enemies();
    CheckCollision_Bullets_Enemies();
}

void UpdateScene_GameScene(double deltaTime)
{
    UpdatePlayer(deltaTime);
    UpdateEnemies(deltaTime);
    UpdateBullets(deltaTime);
}

void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    RenderPlayer(hdc_memBuffer, hdc_loadBmp);
    RenderEnemies(hdc_memBuffer, hdc_loadBmp);
    RenderBullets(hdc_memBuffer, hdc_loadBmp);

    Player* player = GetPlayer();
    if (player)
    {
        wchar_t buf[128] = {0};
        wsprintfW(buf, L"HP: %d  Score: %d", player->attributes.health, player->attributes.score);
        SetBkMode(hdc_memBuffer, TRANSPARENT);
        SetTextColor(hdc_memBuffer, COLOR_BLACK);
        TextOutW(hdc_memBuffer, 10, 10, buf, lstrlenW(buf));
    }
}
