#include "player.h"

#include "../util/config.h"
#include "../util/keyboard.h"
#include "../util/util.h"

namespace
{
    Player* g_player = nullptr;
}

void CreatePlayer()
{
    DestroyPlayer();

    g_player = new Player();
    g_player->position.x = (GAME_WIDTH - PLAYER_WIDTH) / 2.0;
    g_player->position.y = GAME_HEIGHT - PLAYER_HEIGHT - 20.0;
    g_player->width = PLAYER_WIDTH;
    g_player->height = PLAYER_HEIGHT;
    g_player->attributes.health = PLAYER_INITIAL_HEALTH;
    g_player->attributes.score = 0;
    g_player->attributes.speed = PLAYER_SPEED;
    g_player->attributes.maxBulletCd = PLAYER_BULLET_COOLDOWN;
    g_player->attributes.bulletCd = 0.0;
}

Player* GetPlayer()
{
    return g_player;
}

void UpdatePlayer(double deltaTime)
{
    if (!g_player)
        return;

    Vector2 direction = {0, 0};
    if (GetKeyDown('W') || GetKeyDown(VK_UP))
        direction.y -= 1;
    if (GetKeyDown('S') || GetKeyDown(VK_DOWN))
        direction.y += 1;
    if (GetKeyDown('A') || GetKeyDown(VK_LEFT))
        direction.x -= 1;
    if (GetKeyDown('D') || GetKeyDown(VK_RIGHT))
        direction.x += 1;

    direction = Normalize(direction);

    g_player->position.x += direction.x * g_player->attributes.speed * deltaTime;
    g_player->position.y += direction.y * g_player->attributes.speed * deltaTime;

    g_player->position.x = Clamp(g_player->position.x, 0, GAME_WIDTH - g_player->width);
    g_player->position.y = Clamp(g_player->position.y, 0, GAME_HEIGHT - g_player->height);

    if (g_player->attributes.bulletCd > 0.0)
        g_player->attributes.bulletCd -= deltaTime;
}

void RenderPlayer(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    (void)hdc_loadBmp;
    if (!g_player)
        return;

    RECT r;
    r.left = (LONG)g_player->position.x;
    r.top = (LONG)g_player->position.y;
    r.right = (LONG)(g_player->position.x + g_player->width);
    r.bottom = (LONG)(g_player->position.y + g_player->height);

    HBRUSH brush = CreateSolidBrush(COLOR_BLUE);
    FillRect(hdc_memBuffer, &r, brush);
    DeleteObject(brush);
}

void DestroyPlayer()
{
    if (g_player)
    {
        delete g_player;
        g_player = nullptr;
    }
}
