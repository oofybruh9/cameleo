// src/theme.rs
use sdl3::pixels::Color;

#[derive(Clone, Copy)]
pub struct Theme {
    pub background: Color,
    pub foreground: Color,
    pub accent: Color,
    pub text: Color,
}

pub const LIGHT_THEME: Theme = Theme {
    background: Color::RGB(255, 255, 255),
    foreground: Color::RGB(230, 230, 230),
    accent: Color::RGB(100, 149, 237),
    text: Color::RGB(0, 0, 0),
};
