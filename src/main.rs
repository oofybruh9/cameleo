mod platform;

use sdl3::{event::Event, keyboard::Keycode, video::Window, EventPump};
use std::time::Duration;
use platform::embed_webview;

struct Tab {
    url: String,
}

fn main() {
    let sdl = sdl3::init().unwrap();
    let video = sdl.video().unwrap();
    let window = video
        .window("Cameleo Browser", 800, 600)
        .position_centered()
        .resizable()
        .build()
        .unwrap();

    let mut tabs = vec![Tab { url: "https://example.com".to_string() }];
    let mut active_tab = 0;

    let mut event_pump = sdl.event_pump().unwrap();
    embed_webview(&window, &tabs[active_tab].url);

    'running: loop {
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit { .. }
                | Event::KeyDown {
                    keycode: Some(Keycode::Escape),
                    .. 
                } => break 'running,
                Event::KeyDown {
                    keycode: Some(Keycode::Tab),
                    ..
                } => {
                    active_tab = (active_tab + 1) % tabs.len();
                    embed_webview(&window, &tabs[active_tab].url);
                }
                _ => {}
            }
        }
        std::thread::sleep(Duration::from_millis(16));
    }
}
