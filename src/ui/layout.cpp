// Updated layout.cpp - Adds tab bar rendering and CEF switching
#include <SDL3/SDL.h>
#include <string>
#include "theme_assets.hpp"
#include "tab.cpp"
#include "controls.cpp"
#include <functional>
#include <vector>
struct UIButton
{
    SDL_Rect rect;
    std::string label;
    std::function<void()> onClick;
};

// Declare the buttons vector to store UI buttons
std::vector<UIButton> buttons;

extern SDL_Renderer *renderer;
extern void SetCEFURL(const std::string &url); // function from cef_wrapper.cpp

void DrawRect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
    SDL_RenderFillRect(renderer, &rect);
}

void RenderTopBar()
{
    int height = 50;
    DrawRect(0, 0, 800, height, CurrentTheme.accent);
    // RenderTopBarText(); // Function not defined, comment out or implement as needed
}

void RenderBottomNav()
{
    int height = 60;
    DrawRect(0, 540, 800, height, CurrentTheme.background);
    RenderBottomNavText();
}

void RenderTabs()
{
    const int tabHeight = 30;
    const int tabWidth = 150;
    const int closeSize = 24; // Width for the [X] button
    const int y = 50;
    int x = 0;

    const auto &tabs = GetTabs();
    int active = GetActiveTabIndex();

    for (size_t i = 0; i < tabs.size(); ++i)
    {
        bool isActive = (i == active);
        SDL_Color tabColor = isActive ? CurrentTheme.accent : CurrentTheme.foreground;
        SDL_Color textColor = isActive ? CurrentTheme.background : CurrentTheme.background;

        // Draw tab background
        DrawRect(x, y, tabWidth, tabHeight, tabColor);

        // Draw tab label
        std::string label = "Tab " + std::to_string(i + 1);
        DrawText(label, x + 8, y + 6, textColor);

        // Tab click area (excluding [X])
        UIButton tabButton;
        tabButton.rect.x = x;
        tabButton.rect.y = y;
        tabButton.rect.w = tabWidth - closeSize;
        tabButton.rect.h = tabHeight;
        tabButton.label = "Tab" + std::to_string(i);
        tabButton.onClick = [i]()
        {
            SwitchToTab(i);
            const Tab *tab = GetActiveTab();
            if (tab)
                SetCEFURL(tab->url);
        };
        buttons.push_back(tabButton);

        // Draw close button
        // Close button event
        UIButton closeButton;
        closeButton.rect.x = x + tabWidth - closeSize;
        closeButton.rect.y = y;
        closeButton.rect.w = closeSize;
        closeButton.rect.h = tabHeight;
        closeButton.label = "Close" + std::to_string(i);
        closeButton.onClick = [i]()
        {
            CloseTab(i);
            const Tab *tab = GetActiveTab();
            if (tab)
                SetCEFURL(tab->url);
        };
        buttons.push_back(UIButton(closeButton));
    }

    x += tabWidth;
}
