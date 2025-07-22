use image::{ImageBuffer, Rgba, RgbaImage};
use rusttype::{point, Font, Scale};
use sdl3::pixels::PixelFormatEnum;
use sdl3::render::{Canvas, Texture};
use sdl3::video::Window;
use std::fs;

pub fn render_text_to_texture(
    canvas: &mut Canvas<Window>,
    text: &str,
    font_path: &str,
    font_size: f32,
) -> Texture {
    // Load font bytes
    let font_data = fs::read(font_path).expect("Failed to read font file");
    let font = Font::try_from_vec(font_data).expect("Failed to parse font");

    let scale = Scale::uniform(font_size);
    let v_metrics = font.v_metrics(scale);
    let glyphs: Vec<_> = font
        .layout(text, scale, point(0.0, v_metrics.ascent))
        .collect();

    let width = glyphs
        .iter()
        .filter_map(|g| g.pixel_bounding_box().map(|b| b.max.x))
        .max()
        .unwrap_or(0) as u32;
    let height = (v_metrics.ascent - v_metrics.descent).ceil() as u32;

    let mut image: RgbaImage = ImageBuffer::from_pixel(width, height, Rgba([0, 0, 0, 0]));

    for glyph in &glyphs {
        if let Some(bb) = glyph.pixel_bounding_box() {
            glyph.draw(|x, y, v| {
                let px = x + bb.min.x as u32;
                let py = y + bb.min.y as u32;
                if px < width && py < height {
                    image.put_pixel(px, py, Rgba([255, 255, 255, (v * 255.0) as u8]));
                }
            });
        }
    }

    // Convert image to SDL texture
    let (w, h) = image.dimensions();
    let mut texture = canvas
        .create_texture(
            PixelFormatEnum::RGBA32,
            sdl3::render::TextureAccess::Static,
            w,
            h,
        )
        .expect("Failed to create SDL texture");

    texture
        .update(None, &image, (4 * w) as usize)
        .expect("Failed to update texture with image data");

    texture
}
