#pragma once

#include <windows.h>

enum class SceneId
{
    None = 0,
    StartScene = 1,
    GameScene = 2,
};

struct Scene
{
    SceneId sceneId;
};

Scene* GetCurrentScene();
void ChangeScene(SceneId newSceneId);

void SceneLoop(double deltaTime);
void RenderScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
