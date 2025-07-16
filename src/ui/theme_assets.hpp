// src/ui/theme_assets.hpp
#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>

struct Theme {
    std::string name;
    SDL_Color background;
    SDL_Color foreground;
    SDL_Color accent;
    std::string fontPath;
};

static const std::vector<Theme> ThemePresets = {
    {
        "Light",
        {255, 255, 255, 255},  // background
        {33, 33, 33, 255},     // foreground
        {100, 181, 246, 255},  // accent (light blue)
        "assets/fonts/OpenSans-Regular.ttf"
    },
    {
        "Dark",
        {33, 33, 33, 255},     // background
        {255, 255, 255, 255},  // foreground
        {3, 169, 244, 255},    // accent (cyan)
        "assets/fonts/OpenSans-Regular.ttf"
    },
    {
        "Amber",
        {255, 248, 225, 255},  // background
        {50, 50, 50, 255},     // foreground
        {255, 193, 7, 255},    // accent
        "assets/fonts/OpenSans-Regular.ttf"
    },
    {
        "Olive",
        {242, 243, 231, 255},  // background
        {51, 51, 34, 255},     // foreground
        {139, 195, 74, 255},   // accent
        "assets/fonts/OpenSans-Regular.ttf"
    }
};

// Active theme pointer
static Theme CurrentTheme = ThemePresets[0];  // Default to Light
