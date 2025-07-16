// Updated layout.cpp - Adds tab bar rendering and CEF switching
#include <SDL3/SDL.h>
#include <string>
#include "theme_assets.hpp"
#include "tab.cpp"
#include "controls.cpp"

extern SDL_Renderer* renderer;
extern void SetCEFURL(const std::string& url); // function from cef_wrapper.cpp

void DrawRect(int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void RenderTopBar() {
    int height = 50;
    DrawRect(0, 0, 800, height, CurrentTheme.accent);
    RenderTopBarText();
}

void RenderBottomNav() {
    int height = 60;
    DrawRect(0, 540, 800, height, CurrentTheme.background);
    RenderBottomNavText();
}

void RenderTabs() {
    const int tabHeight = 30;
    const int tabWidth = 150;
    int y = 50;
    int x = 0;

    const auto& tabs = GetTabs();
    int active = GetActiveTabIndex();

    for (size_t i = 0; i < tabs.size(); ++i) {
        SDL_Color color = (i == active) ? CurrentTheme.accent : CurrentTheme.foreground;
        DrawRect(x, y, tabWidth, tabHeight, color);
        DrawText("Tab " + std::to_string(i+1), x + 8, y + 8, CurrentTheme.background);

        buttons.push_back({ {x, y, tabWidth, tabHeight}, "Tab " + std::to_string(i+1), [i]() {
            SwitchToTab(i);
            const Tab* tab = GetActiveTab();
            if (tab) SetCEFURL(tab->url);
        }});

        x += tabWidth;
    }
}

void RenderCenterContent() {
    DrawRect(0, 80, 800, 460, CurrentTheme.background);
    const Tab* tab = GetActiveTab();
    if (tab) DrawText(tab->url, 16, 100, CurrentTheme.foreground);
}

void RenderUILayout() {
    RenderTopBar();
    RenderTabs();
    RenderCenterContent();
    RenderBottomNav();
}
