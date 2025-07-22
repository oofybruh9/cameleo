// src/layout.rs
use crate::tab::TabManager;
use crate::text::render_text_to_texture;
use crate::theme::Theme;
use sdl3::rect::{Point, Rect};
use sdl3::{render::Canvas, video::Window};

/// Draw text using rusttype + SDL3
pub fn draw_text(
    canvas: &mut Canvas<Window>,
    text: &str,
    font_path: &str,
    x: i32,
    y: i32,
    font_size: f32,
) {
    let texture = render_text_to_texture(canvas, text, font_path, font_size);
    let query = texture.query();
    let dst = Rect::new(x, y, query.width, query.height);
    canvas.copy(&texture, None, Some(dst)).unwrap();
}

pub fn draw_ui(canvas: &mut Canvas<Window>, font: &Font, theme: Theme, tabs: &TabManager) {
    let w = canvas.window().size().0 as i32;

    // Top bar
    canvas.set_draw_color(theme.accent);
    canvas.fill_rect(Rect::new(0, 0, w as u32, 50)).unwrap();

    // Tab bar
    let tab_width = 150;
    let tab_height = 30;
    let tab_y = 50;

    for (i, tab) in tabs.tabs.iter().enumerate() {
        let x = (i * tab_width) as i32;
        let color = if i == tabs.active_index {
            theme.accent
        } else {
            theme.foreground
        };

        canvas.set_draw_color(color);
        canvas
            .fill_rect(Rect::new(x, tab_y, tab_width as u32, tab_height))
            .unwrap();

        // Optional: draw tab title text
    }

    // Bottom nav bar
    canvas.set_draw_color(theme.background);
    canvas.fill_rect(Rect::new(0, 540, w as u32, 60)).unwrap();
}
