// desktop/main.cpp - SDL3 + CEF Boilerplate for Cameleo Browser
/*
while (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT) running = false;
    HandleUIEvent(e);  // NEW!
}
*/

#include <SDL3/SDL.h>
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"

CefRefPtr<CefBrowser> browser;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;

class SimpleHandler : public CefClient, public CefLifeSpanHandler {
public:
    SimpleHandler() = default;

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    void OnAfterCreated(CefRefPtr<CefBrowser> b) override {
        browser = b;
    }

    IMPLEMENT_REFCOUNTING(SimpleHandler);
};

void InitSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Cameleo Browser",
        800, 600, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);
}

void InitCEF(int argc, char* argv[]) {
    CefEnableHighDPISupport();

    CefMainArgs main_args(argc, argv);
    CefSettings settings;
    settings.no_sandbox = true;

    CefInitialize(main_args, settings, new CefApp(), nullptr);
}

void CreateBrowser() {
    CefWindowInfo window_info;
#if defined(_WIN32)
    window_info.SetAsChild((HWND)SDL_GetProperty(SDL_GetWindowProperties(window), "SDL.window.win32.hwnd", nullptr), {0, 0, 800, 600});
#elif defined(__linux__)
    window_info.SetAsChild((Window)SDL_GetProperty(SDL_GetWindowProperties(window), "SDL.window.x11.window", nullptr), {0, 0, 800, 600});
#elif defined(__APPLE__)
    window_info.SetAsChild((NSView*)SDL_GetProperty(SDL_GetWindowProperties(window), "SDL.window.cocoa.view", nullptr), {0, 0, 800, 600});
#endif

    CefBrowserSettings browser_settings;
    CefBrowserHost::CreateBrowser(window_info, new SimpleHandler(), "https://example.com", browser_settings, nullptr, nullptr);
}

void MainLoop() {
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        CefDoMessageLoopWork();
        SDL_Delay(10);
        while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) running = false;
        HandleUIEvent(e);  // NEW!
        }
    }
}

int main(int argc, char* argv[]) {
    InitSDL();
    InitCEF(argc, argv);
    CreateBrowser();
    MainLoop();
    CefShutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
