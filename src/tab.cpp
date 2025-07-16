// src/tab.cpp - Basic tab management system
#include <vector>
#include <string>
#include <memory>
#include <iostream>

struct Tab {
    std::string url;
    std::string title;
    int id;
};

static std::vector<Tab> tabs;
static int activeTabIndex = 0;
static int nextTabId = 1;

void CreateTab(const std::string& url = "https://example.com") {
    Tab newTab;
    newTab.url = url;
    newTab.title = "New Tab";
    newTab.id = nextTabId++;
    tabs.push_back(newTab);
    activeTabIndex = tabs.size() - 1;
    std::cout << "Created tab with ID: " << newTab.id << "\n";
    // TODO: Hook into CEF/WebView to actually open the page
}

void CloseTab(int index) {
    if (tabs.empty() || index < 0 || index >= static_cast<int>(tabs.size())) return;
    std::cout << "Closing tab ID: " << tabs[index].id << "\n";
    tabs.erase(tabs.begin() + index);
    if (activeTabIndex >= static_cast<int>(tabs.size())) activeTabIndex = tabs.size() - 1;
}

void SwitchToTab(int index) {
    if (index >= 0 && index < static_cast<int>(tabs.size())) {
        activeTabIndex = index;
        std::cout << "Switched to tab ID: " << tabs[index].id << "\n";
        // TODO: Update CEF/WebView to show that tab
    }
}

const Tab* GetActiveTab() {
    if (tabs.empty()) return nullptr;
    return &tabs[activeTabIndex];
}

const std::vector<Tab>& GetTabs() {
    return tabs;
}

int GetActiveTabIndex() {
    return activeTabIndex;
}
