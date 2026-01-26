#include "scene1.h"

#include "scene.h"
#include "../ui/button.h"
#include "../util/config.h"
#include "../util/mouse.h"
#include "../util/keyboard.h"

namespace
{
    ButtonId g_startButtonId = 0;

    void RenderStartButton(Button* button, HDC hdc_memBuffer, HDC hdc_loadBmp)
    {
        (void)hdc_loadBmp;

        RECT r;
        r.left = (LONG)button->position.x;
        r.top = (LONG)button->position.y;
        r.right = (LONG)(button->position.x + button->width);
        r.bottom = (LONG)(button->position.y + button->height);

        HBRUSH bg = CreateSolidBrush(RGB(40, 120, 200));
        FillRect(hdc_memBuffer, &r, bg);
        DeleteObject(bg);

        SetBkMode(hdc_memBuffer, TRANSPARENT);
        SetTextColor(hdc_memBuffer, COLOR_WHITE);
        const wchar_t* text = L"START";
        TextOutW(hdc_memBuffer, r.left + 20, r.top + 20, text, lstrlenW(text));
    }

    void OnStartButtonClick(Button* button)
    {
        (void)button;
        ChangeScene(SceneId::GameScene);
    }
}

void LoadScene_StartScene()
{
    const int width = 240;
    const int height = 120;
    const int x = (WINDOW_WIDTH - width) / 2;
    const int y = (WINDOW_HEIGHT - height) / 2;

    g_startButtonId = CreateButton((double)x, (double)y, width, height, RenderStartButton, OnStartButtonClick);
    EnableButton(g_startButtonId);
}

void UnloadScene_StartScene()
{
    DestroyButtons();
    g_startButtonId = 0;
}

void ProcessUiInput_StartScene()
{
    if (IsMouseLButtonDown())
    {
        PressButtons(GetMouseX(), GetMouseY());
    }

    // Keyboard fallback.
    if (GetKeyDown(VK_RETURN))
    {
        ChangeScene(SceneId::GameScene);
    }
}

void CheckCollision_StartScene()
{
}

void UpdateScene_StartScene(double deltaTime)
{
    (void)deltaTime;
}

void RenderScene_StartScene(HDC hdc_memBuffer, HDC hdc_loadBmp)
{
    (void)hdc_loadBmp;

    SetBkMode(hdc_memBuffer, TRANSPARENT);
    SetTextColor(hdc_memBuffer, COLOR_BLACK);
    const wchar_t* title = L"Air Combat";
    TextOutW(hdc_memBuffer, 30, 30, title, lstrlenW(title));

    RenderButtons(hdc_memBuffer, hdc_loadBmp);
}
