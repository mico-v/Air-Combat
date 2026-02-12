#include "core.h"

#include "../game_object/player.h"
#include "../game_object/enemy.h"
#include "../game_object/bullet.h"
#include "../util/config.h"
#include "../util/util.h"

#include <SDL.h>

namespace
{
    // 重置游戏状态（玩家死亡时调用）
    void ResetGame()
    {
        CreatePlayer();
        ClearEnemies();
        ClearBullets();
    }

    // 检测玩家与敌人的碰撞
    void CheckCollision_Player_Enemies()
    {
        Player* player = GetPlayer();
        if (!player)
            return;

        // 将玩家转换为矩形用于碰撞检测
        Rect playerRect = CreateRect(player->position, player->width, player->height);
        auto& enemies = GetEnemies();

        // 遍历所有敌人，检查是否与玩家碰撞
        for (size_t i = 0; i < enemies.size();)
        {
            Rect enemyRect = CreateRect(enemies[i].position, enemies[i].width, enemies[i].height);
            
            if (IsRectRectCollision(playerRect, enemyRect))
            {
                // 玩家受伤
                player->attributes.health -= 1;
                // 玩家获得分数（即使碰撞也得分？这里的逻辑是获得敌人分数）
                player->attributes.score += enemies[i].attributes.score;
                // 敌人被消灭
                enemies.erase(enemies.begin() + static_cast<int>(i));

                // 如果玩家生命值 <= 0，游戏重置
                if (player->attributes.health <= 0)
                {
                    ResetGame();
                    return;
                }
                continue;  // 继续检测下一个敌人
            }
            i++;
        }
    }

    // 检测子弹与敌人的碰撞
    void CheckCollision_Bullets_Enemies()
    {
        Player* player = GetPlayer();
        if (!player)
            return;

        auto& bullets = GetBullets();
        auto& enemies = GetEnemies();

        // 遍历每一颗子弹
        for (size_t bi = 0; bi < bullets.size();)
        {
            // 将子弹转换为圆形用于碰撞检测
            Circle bulletCircle = CreateCircle(bullets[bi].position, bullets[bi].radius);
            bool bulletDestroyed = false;

            // 检查该子弹是否与任何敌人碰撞
            for (size_t ei = 0; ei < enemies.size(); ++ei)
            {
                Rect enemyRect = CreateRect(enemies[ei].position, enemies[ei].width, enemies[ei].height);
                
                // 如果没有碰撞，继续检查下一个敌人
                if (!IsRectCircleCollision(enemyRect, bulletCircle))
                    continue;

                // 敌人受伤
                enemies[ei].attributes.health -= bullets[bi].damage;
                // 如果敌人生命值 <= 0，敌人消灭
                if (enemies[ei].attributes.health <= 0)
                {
                    // 玩家得到分数
                    player->attributes.score += enemies[ei].attributes.score;
                    enemies.erase(enemies.begin() + static_cast<int>(ei));
                }

                // 子弹消灭
                bullets.erase(bullets.begin() + static_cast<int>(bi));
                bulletDestroyed = true;
                break;  // 一颗子弹只能击中一个敌人
            }

            // 如果子弹还存在，推进到下一颗
            if (!bulletDestroyed)
                bi++;
        }
    }
}

// 游戏初始化
void GameInit()
{
    ResetGame();
}

// 游戏每帧更新
void GameUpdate(double deltaTime)
{
    // 更新所有实体
    UpdatePlayer(deltaTime);
    UpdateEnemies(deltaTime);
    UpdateBullets(deltaTime);

    // 检测碰撞
    CheckCollision_Player_Enemies();
    CheckCollision_Bullets_Enemies();
}

// 游戏每帧渲染
void GameRender(SDL_Renderer* renderer)
{
    if (!renderer)
        return;

    // 清空屏幕为白色背景
    SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, 255);
    SDL_RenderClear(renderer);

    // 渲染所有游戏对象
    RenderPlayer(renderer);
    RenderEnemies(renderer);
    RenderBullets(renderer);
}

// 游戏清理
void GameShutdown()
{
    DestroyPlayer();
    ClearEnemies();
    ClearBullets();
}
