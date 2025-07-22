#[cfg(target_os = "windows")]
pub use crate::platform::windows_embed::embed_webview;
#[cfg(target_os = "macos")]
pub use crate::platform::mac_embed::embed_webview;
#[cfg(target_os = "linux")]
pub use crate::platform::linux_embed::embed_webview;

#[cfg(target_os = "windows")]
mod windows_embed;
#[cfg(target_os = "macos")]
mod mac_embed;
#[cfg(target_os = "linux")]
mod linux_embed;
