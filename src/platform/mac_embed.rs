use sdl3::video::Window;

pub fn embed_webview(window: &Window, url: &str) {
    println!("macOS: embedding WebView with URL: {}", url);
    // TODO: Add NSView extraction and webview::Builder::with_parent(nsview)
}
