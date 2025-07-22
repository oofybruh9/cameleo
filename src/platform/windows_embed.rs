use sdl3::video::Window;

pub fn embed_webview(window: &Window, url: &str) {
    println!("Windows: embedding WebView with URL: {}", url);
    // TODO: Add HWND extraction and webview::Builder::with_parent(hwnd)
}
