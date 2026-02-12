#pragma once

struct SDL_Renderer;

// ===== 游戏核心模块 API =====

// 初始化游戏（创建玩家，清空敌人和子弹）
void GameInit();

// 更新游戏状态（所有实体的逻辑更新和碰撞检测）
void GameUpdate(double deltaTime);

// 渲染游戏画面
void GameRender(SDL_Renderer* renderer);

// 清理游戏资源（目前预留）
void GameShutdown();
