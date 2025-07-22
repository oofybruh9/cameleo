// src/ui/button.rs
use sdl3::rect::Rect;

pub struct UIButton {
    pub rect: Rect,
    pub label: String,
    pub on_click: Box<dyn FnMut()>,
}
