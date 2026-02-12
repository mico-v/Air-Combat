#include "player.h"

#include "../input/input.h"
#include "../util/config.h"
#include "../util/util.h"

#include <SDL.h>

namespace
{
    // 玩家飞机对象（全局单例）
    Player g_player = {};
    // 标记玩家是否存在
    bool g_hasPlayer = false;
}

// 初始化玩家
void CreatePlayer()
{
    g_hasPlayer = true;
    // 玩家出现在屏幕中下方，水平居中
    g_player.position.x = (GAME_WIDTH - PLAYER_WIDTH) / 2.0;
    g_player.position.y = GAME_HEIGHT - PLAYER_HEIGHT - 20.0;
    g_player.width = PLAYER_WIDTH;
    g_player.height = PLAYER_HEIGHT;
    // 初始化属性
    g_player.attributes.health = PLAYER_INITIAL_HEALTH;
    g_player.attributes.score = 0;
    g_player.attributes.speed = PLAYER_SPEED;
    g_player.attributes.maxBulletCd = PLAYER_BULLET_COOLDOWN;
    g_player.attributes.bulletCd = 0.0;
}

// 获取玩家对象指针
Player* GetPlayer()
{
    return g_hasPlayer ? &g_player : nullptr;
}

// 更新玩家状态（每帧调用）
void UpdatePlayer(double deltaTime)
{
    if (!g_hasPlayer)
        return;

    // ===== 处理移动输入 =====
    // 初始化移动方向向量
    Vector2 direction = {0.0, 0.0};
    
    // 检查上箭头或 W 键
    if (IsKeyDown(SDL_SCANCODE_W) || IsKeyDown(SDL_SCANCODE_UP))
        direction.y -= 1.0;
    // 检查下箭头或 S 键
    if (IsKeyDown(SDL_SCANCODE_S) || IsKeyDown(SDL_SCANCODE_DOWN))
        direction.y += 1.0;
    // 检查左箭头或 A 键
    if (IsKeyDown(SDL_SCANCODE_A) || IsKeyDown(SDL_SCANCODE_LEFT))
        direction.x -= 1.0;
    // 检查右箭头或 D 键
    if (IsKeyDown(SDL_SCANCODE_D) || IsKeyDown(SDL_SCANCODE_RIGHT))
        direction.x += 1.0;

    // 正规化方向向量（这样即使斜向移动也是恒定速度）
    direction = Normalize(direction);

    // 根据方向、速度和 deltaTime 更新位置
    g_player.position.x += direction.x * g_player.attributes.speed * deltaTime;
    g_player.position.y += direction.y * g_player.attributes.speed * deltaTime;

    // ===== 限制玩家在游戏区域内 =====
    g_player.position.x = Clamp(g_player.position.x, 0.0, GAME_WIDTH - g_player.width);
    g_player.position.y = Clamp(g_player.position.y, 0.0, GAME_HEIGHT - g_player.height);

    // ===== 更新射击冷却时间 =====
    if (g_player.attributes.bulletCd > 0.0)
        g_player.attributes.bulletCd -= deltaTime;  // 冷却递减
}

// 渲染玩家
void RenderPlayer(SDL_Renderer* renderer)
{
    if (!g_hasPlayer || !renderer)
        return;

    // 转换为 SDL 矩形结构
    SDL_Rect r;
    r.x = static_cast<int>(g_player.position.x);
    r.y = static_cast<int>(g_player.position.y);
    r.w = static_cast<int>(g_player.width);
    r.h = static_cast<int>(g_player.height);

    // 设置渲染颜色为蓝色
    SDL_SetRenderDrawColor(renderer, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b, 255);
    // 绘制填充矩形
    SDL_RenderFillRect(renderer, &r);
}

// 销毁玩家
void DestroyPlayer()
{
    g_hasPlayer = false;
}
