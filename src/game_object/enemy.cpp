#include "enemy.h"

#include "../util/config.h"
#include "../util/util.h"

#include <SDL.h>

namespace
{
    // 所有当前存在的敌人列表
    std::vector<Enemy> g_enemies;
    // 敌人生成计时器（累加器模式）
    double g_spawnTimer = 0.0;
}

// 在指定位置创建一个敌人
void CreateEnemy(double x, double y)
{
    Enemy e = {};
    e.position = {x, y};
    e.width = ENEMY_WIDTH;
    e.height = ENEMY_HEIGHT;
    // 初始化属性
    e.attributes.health = ENEMY_HEALTH;
    e.attributes.score = ENEMY_SCORE;
    e.attributes.speed = ENEMY_SPEED;
    e.attributes.maxBulletCd = 0.0;  // 敌人不射击
    e.attributes.bulletCd = 0.0;

    g_enemies.push_back(e);  // 添加到列表
}

// 创建一个随机位置的敌人
// 敌人生成在屏幕上方（y = -100）
void CreateRandomEnemy()
{
    CreateEnemy(
        GetRandomDouble(30.0, GAME_WIDTH - ENEMY_WIDTH - 30.0),  // 随机 x
        -100.0);  // 屏幕上方
}

// 获取敌人列表
std::vector<Enemy>& GetEnemies()
{
    return g_enemies;
}

// 清空所有敌人
void ClearEnemies()
{
    g_enemies.clear();
    g_spawnTimer = 0.0;  // 重置计时器
}

// 更新敌人
void UpdateEnemies(double deltaTime)
{
    // ===== 定时生成敌人（累加器模式）=====
    g_spawnTimer += deltaTime;
    // 当计时器达到生成间隔时，生成新敌人
    while (g_spawnTimer >= ENEMY_SPAWN_INTERVAL)
    {
        CreateRandomEnemy();
        g_spawnTimer -= ENEMY_SPAWN_INTERVAL;  // 扣掉一个周期
    }

    // ===== 更新所有敌人位置，删除超出屏幕的 =====
    for (size_t i = 0; i < g_enemies.size();)
    {
        Enemy& e = g_enemies[i];
        // 向下移动
        e.position.y += e.attributes.speed * deltaTime;

        // 如果敌人超出下边界，删除它
        if (e.position.y > GAME_HEIGHT + 50.0)
        {
            g_enemies.erase(g_enemies.begin() + static_cast<int>(i));
            continue;  // 直接推进i的下一个
        }
        i++;
    }
}

// 绘制所有敌人
void RenderEnemies(SDL_Renderer* renderer)
{
    if (!renderer)
        return;

    // 设置渲染颜色为深红色
    SDL_SetRenderDrawColor(renderer, 220, 60, 60, 255);
    // 遍历所有敌人并绘制
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
