#include "button.h"

#include <vector>

namespace
{
    std::vector<Button*> g_buttons;
}

static bool PointInButton(int x, int y, const Button* b)
{
    const int left = (int)b->position.x;
    const int top = (int)b->position.y;
    const int right = left + b->width;
    const int bottom = top + b->height;
    return x >= left && x <= right && y >= top && y <= bottom;
}

ButtonId CreateButton(double x, double y, int width, int height, RenderButtonFunc renderFunc, OnClickButtonFunc clickFunc)
{
    Button* b = new Button();
    b->position = {x, y};
    b->width = width;
    b->height = height;
    b->enabled = false;
    b->render = renderFunc;
    b->onClick = clickFunc;

    g_buttons.push_back(b);
    return (ButtonId)g_buttons.size();
}

static Button* GetButton(ButtonId id)
{
    const int index = id - 1;
    if (index < 0 || index >= (int)g_buttons.size())
        return nullptr;
    return g_buttons[index];
}

void EnableButton(ButtonId id)
{
    Button* b = GetButton(id);
    if (b)
        b->enabled = true;
}

void DisableButton(ButtonId id)
{
    Button* b = GetButton(id);
    if (b)
        b->enabled = false;
}

void DestroyButtons()
{
    for (Button* b : g_buttons)
        delete b;
    g_buttons.clear();
}

void PressButtons(int mouseX, int mouseY)
{
    for (Button* b : g_buttons)
    {
        if (!b || !b->enabled)
            continue;
        if (!PointInButton(mouseX, mouseY, b))
            continue;

        if (b->onClick)
            b->onClick(b);
        break;
    }
}

void RenderButtons(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    for (Button* b : g_buttons)
    {
        if (!b || !b->enabled)
            continue;
        if (b->render)
            b->render(b, hdc_memBuffer, hdc_loadBmp);
    }
}
