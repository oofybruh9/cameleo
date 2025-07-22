use sdl3::video::Window;

pub fn embed_webview(_window: &Window, url: &str) {
    println!("Linux: embedding WebView with URL: {}", url);
    // TODO: Add GTK/X11 integration or fallback handling
}
