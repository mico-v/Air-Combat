#include "bullet.h"

#include "player.h"

#include "../input/input.h"
#include "../util/config.h"

#include <SDL.h>
#include <cmath>

namespace
{
    // 所有当前存在的子弹列表
    std::vector<Bullet> g_bullets;
}

// 在指定位置创建一颗子弹
void CreateBullet(double x, double y, int damage, double speed)
{
    Bullet b = {};
    b.position = {x, y};
    b.radius = BULLET_RADIUS;
    b.damage = damage;
    b.speed = speed;
    g_bullets.push_back(b);  // 添加到列表
}

// 获取子弹列表
std::vector<Bullet>& GetBullets()
{
    return g_bullets;
}

// 清空所有子弹
void ClearBullets()
{
    g_bullets.clear();
}

// 更新子弹
void UpdateBullets(double deltaTime)
{
    // ===== 处理射击输入 =====
    Player* player = GetPlayer();
    if (player)
    {
        // 当按下空格且射击冷却完成时，发射一颗子弹
        if (IsKeyDown(SDL_SCANCODE_SPACE) && player->attributes.bulletCd <= 0.0)
        {
            // 从玩家中心顶部发射
            CreateBullet(
                player->position.x + player->width / 2.0,  // 水平中心
                player->position.y,                         // 顶部
                BULLET_DAMAGE,
                BULLET_SPEED);
            // 设置冷却时间
            player->attributes.bulletCd = player->attributes.maxBulletCd;
        }
    }

    // ===== 更新子弹位置，删除超出屏幕的 =====
    for (size_t i = 0; i < g_bullets.size();)
    {
        Bullet& b = g_bullets[i];
        // 向上移动
        b.position.y -= b.speed * deltaTime;
        
        // 如果子弹超出上边界，删除它
        if (b.position.y + b.radius < 0)
        {
            g_bullets.erase(g_bullets.begin() + static_cast<int>(i));
            continue;  // 直接推进i的下一个（因为 erase 后后续元素前移）
        }
        i++;
    }
}

// 绘制一个填充圆形的辅助函数
// 使用水平线扫描算法 + 勾股定理
static void DrawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    // 对每一条水平扫描线
    for (int dy = -radius; dy <= radius; ++dy)
    {
        // 根据勾股定理计算该行的水平跨度
        // dx^2 + dy^2 = radius^2  =>  dx = sqrt(radius^2 - dy^2)
        int dx = static_cast<int>(std::sqrt(radius * radius - dy * dy));
        // 绘制该行的线段
        SDL_RenderDrawLine(renderer, cx - dx, cy + dy, cx + dx, cy + dy);
    }
}

// 渲染所有子弹
void RenderBullets(SDL_Renderer* renderer)
{
    if (!renderer)
        return;

    // 设置渲染颜色为红色
    SDL_SetRenderDrawColor(renderer, COLOR_RED.r, COLOR_RED.g, COLOR_RED.b, 255);
    // 遍历所有子弹并绘制
    for (const Bullet& b : g_bullets)
    {
        DrawFilledCircle(
            renderer,
            static_cast<int>(b.position.x),
            static_cast<int>(b.position.y),
            static_cast<int>(b.radius));
    }
}
