#include "bullet.h"

#include "player.h"

#include "../util/config.h"
#include "../util/keyboard.h"

#include <algorithm>

namespace
{
    std::vector<Bullet*> g_bullets;
}

void CreateBullet(double x, double y, int damage, double speed)
{
    Bullet* b = new Bullet();
    b->position = {x, y};
    b->radius = BULLET_RADIUS;
    b->damage = damage;
    b->speed = speed;
    g_bullets.push_back(b);
}

std::vector<Bullet*> GetBullets()
{
    return g_bullets;
}

void DestroyBullet(Bullet* bullet)
{
    auto it = std::find(g_bullets.begin(), g_bullets.end(), bullet);
    if (it == g_bullets.end())
        return;
    delete *it;
    g_bullets.erase(it);
}

void DestroyBullets()
{
    for (Bullet* b : g_bullets)
        delete b;
    g_bullets.clear();
}

void UpdateBullets(double deltaTime)
{
    Player* player = GetPlayer();
    if (player)
    {
        if (GetKeyDown(VK_SPACE) && player->attributes.bulletCd <= 0.0)
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
        Bullet* b = g_bullets[i];
        b->position.y -= b->speed * deltaTime;
        if (b->position.y + b->radius < 0)
        {
            delete b;
            g_bullets.erase(g_bullets.begin() + (int)i);
            continue;
        }
        i++;
    }
}

void RenderBullets(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    (void)hdc_loadBmp;
    HBRUSH brush = CreateSolidBrush(COLOR_RED);
    HGDIOBJ oldBrush = SelectObject(hdc_memBuffer, brush);
    HGDIOBJ oldPen = SelectObject(hdc_memBuffer, GetStockObject(NULL_PEN));

    for (Bullet* b : g_bullets)
    {
        Ellipse(
            hdc_memBuffer,
            (int)(b->position.x - b->radius),
            (int)(b->position.y - b->radius),
            (int)(b->position.x + b->radius),
            (int)(b->position.y + b->radius));
    }

    SelectObject(hdc_memBuffer, oldPen);
    SelectObject(hdc_memBuffer, oldBrush);
    DeleteObject(brush);
}
