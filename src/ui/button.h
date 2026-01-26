#pragma once

#include "../util/type.h"

#include <windows.h>

struct Button;
using ButtonId = int;
using RenderButtonFunc = void (*)(Button* button, HDC hdc_memBuffer, HDC hdc_loadBmp);
using OnClickButtonFunc = void (*)(Button* button);

struct Button
{
    Vector2 position;
    int width;
    int height;
    bool enabled;
    RenderButtonFunc render;
    OnClickButtonFunc onClick;
};

ButtonId CreateButton(double x, double y, int width, int height, RenderButtonFunc renderFunc, OnClickButtonFunc clickFunc);
void EnableButton(ButtonId id);
void DisableButton(ButtonId id);

void DestroyButtons();
void PressButtons(int mouseX, int mouseY);
void RenderButtons(HDC hdc_memBuffer, HDC hdc_loadBmp);
