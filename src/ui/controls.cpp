// Updated controls.cpp - Adds basic button event handling
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include "theme_assets.hpp"
#include <functional> // 👈 Important

extern SDL_Renderer *renderer;
static TTF_Font *currentFont = nullptr;

struct UIButton
{
    SDL_FRect rect;
    std::string label;
    std::function<void()> onClick; // ✅ Must be std::function
};

// Declare the buttons vector at file scope
static std::vector<UIButton> buttons;

bool LoadFont(const std::string &path, int size)
{
    if (currentFont)
        TTF_CloseFont(currentFont);
    currentFont = TTF_OpenFont(path.c_str(), size);
    return currentFont != nullptr;
}

void DrawText(const std::string &text, int x, int y, SDL_Color color)
{
    if (!currentFont)
        return;
    SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
    SDL_Surface *surface = TTF_RenderText_Solid(currentFont, text.c_str(), 1, sdlColor);
    if (!surface)
        return;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_FRect fdst = {static_cast<float>(dst.x), static_cast<float>(dst.y), static_cast<float>(dst.w), static_cast<float>(dst.h)};
    SDL_RenderTexture(renderer, texture, nullptr, &fdst);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void HandleButtonClick(int mx, int my)
{
    for (auto &btn : buttons)
    {
        SDL_Point pt = {mx, my};
        if (SDL_PointInRect(&pt, &btn.rect))
        {
            if (btn.onClick)
                btn.onClick();
        }
    }
}

// Dummy actions for navigation
void OnBack() { SDL_Log("Back clicked"); }
void OnForward() { SDL_Log("Forward clicked"); }
void OnHome() { SDL_Log("Home clicked"); }
void OnTabs() { SDL_Log("Tabs clicked"); }
void OnMenu() { SDL_Log("Menu clicked"); }

void RenderBottomNavText()
{
    buttons.clear();

    int y = 555;
    buttons.push_back({{30, y, 30, 30}, "\uE5C4", OnBack});
    buttons.push_back({{90, y, 30, 30}, "\uE5C8", OnForward});
    buttons.push_back({{160, y, 30, 30}, "\uE88A", OnHome});
    buttons.push_back({{230, y, 30, 30}, "\uE8F0", OnTabs});
    buttons.push_back({{300, y, 30, 30}, "\uE5D2", OnMenu});

    for (const auto &btn : buttons)
    {
        DrawText(btn.label, btn.rect.x, btn.rect.y, CurrentTheme.foreground);
    }
}

void HandleUIEvent(const SDL_Event &e)
{
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        HandleButtonClick(e.button.x, e.button.y);
    }
}
