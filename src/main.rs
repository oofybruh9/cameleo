mod layout;
mod tab;
mod theme;

use sdl3::event::Event;
use sdl3::keyboard::Keycode;
use tab::TabManager;
use theme::LIGHT_THEME;

fn main() -> Result<(), String> {
    let sdl = sdl3::init()?;
    let video = sdl.video()?;
    let window = video
        .window("Cameleo", 800, 600)
        .position_centered()
        .resizable()
        .build()?;
    let mut canvas = window.into_canvas().build()?;

    let ttf_ctx = Sdl3Ttf::init()?;
    let font = ttf_ctx.load_font("assets/Roboto-Regular.ttf", 16)?;

    let mut tab_manager = TabManager::new();
    let mut event_pump = sdl.event_pump()?;

    'running: loop {
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit { .. }
                | Event::KeyDown {
                    keycode: Some(Keycode::Escape),
                    ..
                } => break 'running,
                _ => {}
            }
        }

        canvas.set_draw_color(LIGHT_THEME.background);
        canvas.clear();

        layout::draw_ui(&mut canvas, &font, LIGHT_THEME, &tab_manager);
        canvas.present();
    }

    Ok(())
}
