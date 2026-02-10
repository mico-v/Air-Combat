#include "bullet.h"

#include "player.h"

#include "../input/input.h"
#include "../util/config.h"

#include <SDL.h>
#include <cmath>

namespace
{
    std::vector<Bullet> g_bullets;
}

void CreateBullet(double x, double y, int damage, double speed)
{
    Bullet b = {};
    b.position = {x, y};
    b.radius = BULLET_RADIUS;
    b.damage = damage;
    b.speed = speed;
    g_bullets.push_back(b);
}

std::vector<Bullet>& GetBullets()
{
    return g_bullets;
}

void ClearBullets()
{
    g_bullets.clear();
}

void UpdateBullets(double deltaTime)
{
    Player* player = GetPlayer();
    if (player)
    {
        if (IsKeyDown(SDL_SCANCODE_SPACE) && player->attributes.bulletCd <= 0.0)
        {
            CreateBullet(
                player->position.x + player->width / 2.0,
                player->position.y,
                BULLET_DAMAGE,
                BULLET_SPEED);
            player->attributes.bulletCd = player->attributes.maxBulletCd;
        }
    }

    for (size_t i = 0; i < g_bullets.size();)
    {
        Bullet& b = g_bullets[i];
        b.position.y -= b.speed * deltaTime;
        if (b.position.y + b.radius < 0)
        {
            g_bullets.erase(g_bullets.begin() + static_cast<int>(i));
            continue;
        }
        i++;
    }
}

static void DrawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    for (int dy = -radius; dy <= radius; ++dy)
    {
        int dx = static_cast<int>(std::sqrt(radius * radius - dy * dy));
        SDL_RenderDrawLine(renderer, cx - dx, cy + dy, cx + dx, cy + dy);
    }
}

void RenderBullets(SDL_Renderer* renderer)
{
    if (!renderer)
        return;

    SDL_SetRenderDrawColor(renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255);
    for (const Bullet& b : g_bullets)
    {
        DrawFilledCircle(
            renderer,
            static_cast<int>(b.position.x),
            static_cast<int>(b.position.y),
            static_cast<int>(b.radius));
    }
}
