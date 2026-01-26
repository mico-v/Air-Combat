#pragma once

#include <windows.h>

void LoadScene_StartScene();
void UnloadScene_StartScene();
void ProcessUiInput_StartScene();
void CheckCollision_StartScene();
void UpdateScene_StartScene(double deltaTime);
void RenderScene_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp);
