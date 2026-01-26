#include "scene.h"

#include "scene1.h"
#include "scene2.h"

namespace
{
    Scene g_currentScene = {SceneId::None};
    SceneId g_newSceneId = SceneId::None;
}

Scene* GetCurrentScene()
{
    return &g_currentScene;
}

void ChangeScene(SceneId newSceneId)
{
    g_newSceneId = newSceneId;
}

#define ROUTE_SCENE_FUNCTION(FUNCTION_NAME) \
    switch (GetCurrentScene()->sceneId)     \
    {                                       \
    case SceneId::None:                     \
        break;                              \
    case SceneId::StartScene:               \
        FUNCTION_NAME##_StartScene();       \
        break;                              \
    case SceneId::GameScene:                \
        FUNCTION_NAME##_GameScene();        \
        break;                              \
    }

#define ROUTE_SCENE_FUNCTION_OneParam(FUNCTION_NAME, P1) \
    switch (GetCurrentScene()->sceneId)                  \
    {                                                    \
    case SceneId::None:                                  \
        break;                                           \
    case SceneId::StartScene:                            \
        FUNCTION_NAME##_StartScene(P1);                  \
        break;                                           \
    case SceneId::GameScene:                             \
        FUNCTION_NAME##_GameScene(P1);                   \
        break;                                           \
    }

#define ROUTE_SCENE_FUNCTION_TwoParam(FUNCTION_NAME, P1, P2) \
    switch (GetCurrentScene()->sceneId)                      \
    {                                                        \
    case SceneId::None:                                      \
        break;                                               \
    case SceneId::StartScene:                                \
        FUNCTION_NAME##_StartScene(P1, P2);                  \
        break;                                               \
    case SceneId::GameScene:                                 \
        FUNCTION_NAME##_GameScene(P1, P2);                   \
        break;                                               \
    }

void SceneLoop(double deltaTime)
{
    // Apply pending scene change at the beginning of a frame.
    if (g_newSceneId != SceneId::None)
    {
        ROUTE_SCENE_FUNCTION(UnloadScene);
        g_currentScene.sceneId = g_newSceneId;
        g_newSceneId = SceneId::None;
        ROUTE_SCENE_FUNCTION(LoadScene);
    }

    ROUTE_SCENE_FUNCTION(ProcessUiInput);
    ROUTE_SCENE_FUNCTION(CheckCollision);
    ROUTE_SCENE_FUNCTION_OneParam(UpdateScene, deltaTime);
}

void RenderScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    ROUTE_SCENE_FUNCTION_TwoParam(RenderScene, hdc_memBuffer, hdc_loadBmp);
}
