#pragma once

#include <windows.h>

void LoadScene_GameScene();
void UnloadScene_GameScene();
void ProcessUiInput_GameScene();
void CheckCollision_GameScene();
void UpdateScene_GameScene(double deltaTime);
void RenderScene_GameScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
