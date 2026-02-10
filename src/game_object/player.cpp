#include "player.h"

#include "../input/input.h"
#include "../util/config.h"
#include "../util/util.h"

#include <SDL.h>

namespace
{
    Player g_player = {};
    bool g_hasPlayer = false;
}

void CreatePlayer()
{
    g_hasPlayer = true;
    g_player.position.x = (GAME_WIDTH - PLAYER_WIDTH) / 2.0;
    g_player.position.y = GAME_HEIGHT - PLAYER_HEIGHT - 20.0;
    g_player.width = PLAYER_WIDTH;
    g_player.height = PLAYER_HEIGHT;
    g_player.attributes.health = PLAYER_INITIAL_HEALTH;
    g_player.attributes.score = 0;
    g_player.attributes.speed = PLAYER_SPEED;
    g_player.attributes.maxBulletCd = PLAYER_BULLET_COOLDOWN;
    g_player.attributes.bulletCd = 0.0;
}

Player* GetPlayer()
{
    return g_hasPlayer ? &g_player : nullptr;
}

void UpdatePlayer(double deltaTime)
{
    if (!g_hasPlayer)
        return;

    Vector2 direction = {0.0, 0.0};
    if (IsKeyDown(SDL_SCANCODE_W) || IsKeyDown(SDL_SCANCODE_UP))
        direction.y -= 1.0;
    if (IsKeyDown(SDL_SCANCODE_S) || IsKeyDown(SDL_SCANCODE_DOWN))
        direction.y += 1.0;
    if (IsKeyDown(SDL_SCANCODE_A) || IsKeyDown(SDL_SCANCODE_LEFT))
        direction.x -= 1.0;
    if (IsKeyDown(SDL_SCANCODE_D) || IsKeyDown(SDL_SCANCODE_RIGHT))
        direction.x += 1.0;

    direction = Normalize(direction);

    g_player.position.x += direction.x * g_player.attributes.speed * deltaTime;
    g_player.position.y += direction.y * g_player.attributes.speed * deltaTime;

    g_player.position.x = Clamp(g_player.position.x, 0.0, GAME_WIDTH - g_player.width);
    g_player.position.y = Clamp(g_player.position.y, 0.0, GAME_HEIGHT - g_player.height);

    if (g_player.attributes.bulletCd > 0.0)
        g_player.attributes.bulletCd -= deltaTime;
}

void RenderPlayer(SDL_Renderer* renderer)
{
    if (!g_hasPlayer || !renderer)
        return;

    SDL_Rect r;
    r.x = static_cast<int>(g_player.position.x);
    r.y = static_cast<int>(g_player.position.y);
    r.w = static_cast<int>(g_player.width);
    r.h = static_cast<int>(g_player.height);

    SDL_SetRenderDrawColor(renderer, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b, 255);
    SDL_RenderFillRect(renderer, &r);
}

void DestroyPlayer()
{
    g_hasPlayer = false;
}
