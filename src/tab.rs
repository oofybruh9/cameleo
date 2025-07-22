// src/tab.rs
#[derive(Clone)]
pub struct Tab {
    pub title: String,
    pub url: String,
}

pub struct TabManager {
    pub tabs: Vec<Tab>,
    pub active_index: usize,
}

impl TabManager {
    pub fn new() -> Self {
        Self {
            tabs: vec![Tab {
                title: "Example".into(),
                url: "https://example.com".into(),
            }],
            active_index: 0,
        }
    }

    pub fn switch_to(&mut self, index: usize) {
        if index < self.tabs.len() {
            self.active_index = index;
        }
    }

    pub fn active(&self) -> &Tab {
        &self.tabs[self.active_index]
    }
}
