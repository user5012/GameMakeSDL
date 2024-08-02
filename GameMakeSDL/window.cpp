#include "window.h"
#include <Windows.h>
#include <algorithm>


window::window()
{
    
    bool success = true;
    //initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "Failed to init SDL\n" << SDL_GetError() << std::endl;
        success = false;
    }
    int width = 800;
    int height = 600;
    Uint32 flags = SDL_WINDOW_RESIZABLE;
    sdlwindow = SDL_CreateWindow(
        "SDL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        flags
    );

    if (sdlwindow == NULL) {
        std::cout << "Couldnt create Window\n";
        success = false;
    }

    renderer = SDL_CreateRenderer(sdlwindow, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Couldnt create renderer; " << SDL_GetError() << std::endl;
        success = false;
    }
    

    screenSurface = SDL_GetWindowSurface(sdlwindow);

    winMode = WindowMode::Windowed;
    if (!success) {
        std::cout << "Failed to initialize: " << SDL_GetError();
    }
    else {
        std::cout << "created renderer\n";
    }

}
void window::ChangeWinMode(){

    bool work = true;
    Uint32 Resize = SDL_WINDOW_RESIZABLE;
    Uint32 Fullscreen = SDL_WINDOW_FULLSCREEN;
    int width = 1920;
    int height = 1080;
    std::cout << static_cast<int>(winMode) << std::endl;
    
    
    if (winMode == WindowMode::Windowed) {
        SDL_SetWindowSize(sdlwindow, width, height);
        SDL_SetWindowFullscreen(sdlwindow, Fullscreen);
        winMode = WindowMode::FullScreen;
    }
    else {
        SDL_SetWindowFullscreen(sdlwindow, 0);
        SDL_SetWindowSize(sdlwindow, 800, 600);
        SDL_SetWindowResizable(sdlwindow, SDL_TRUE);
        winMode = WindowMode::Windowed;
    }
    std::cout << "Window mode: " << static_cast<int>(winMode) << std::endl;
    
    
    
}


void window::update()
{
    int x = 150;
    int y = 200;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            
            case SDL_QUIT:
                quit = true;
                break;

            default:
                Resize(e);
                KeyListener(e);
                popup(e);
                updaterect(&x, &y);
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        drawRect(90, 213, 250, 200, 200, x, y);
        

    }
    
}

void window::updaterect(int* x, int* y) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_w:
            *y -= 10;
            break;
        case SDLK_s:
            *y += 10;
            break;
        case SDLK_a:
            *x -= 10;
            break;
        case SDLK_d:
            *x += 10;
        }
    }
    
}


void window::popup(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_HOME) {
            MessageBoxW(
                nullptr,
                L"Hello",
                L"Hi",
                NULL
            );
        }
    }
}

void window::drawRect(int red, int green, int blue, int width, int height, int x, int y)
{
    SDL_Rect rect;
    rect.w = width;
    rect.h = height;

    rect.x = x;
    rect.y = y;

    SDL_SetRenderDrawColor(renderer, red, green , blue, 0xff);

    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

bool window::loadMedia()
{
    bool success = true;
    WindowMode winmode{};
    if (screenSurface == nullptr) {
        std::cout << "Couldnt create surface :(\n";
        success = false;
    }
    else {
        SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 255, 255));
        SDL_UpdateWindowSurface(sdlwindow);
    }

    return success;
}

void window::Resize(SDL_Event& e) {
    // Handle window events
    WindowMode winmode{};
    if (e.type == SDL_WINDOWEVENT) {
        switch (e.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_EXPOSED:
            screenSurface = SDL_GetWindowSurface(sdlwindow);
            if (!screenSurface) {
                std::cout << "Failed to get window surface: " << SDL_GetError() << std::endl;
                return; // Exit or handle the error appropriately
            }
            screenSurface = SDL_GetWindowSurface(sdlwindow);
            if (!screenSurface) {
                 std::cout << "Failed to get window surface: " << SDL_GetError() << std::endl;
                 return; // Exit or handle the error appropriately
            }
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 255, 255));
            SDL_UpdateWindowSurface(sdlwindow); 
            break;
        }
    }
}

void window::KeyListener(SDL_Event& e)
{
    bool s = true;
    WindowMode winMode{};
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_F11 && e.key.repeat == 0) {
            ChangeWinMode();
            std::cout << "Pressed F11!\n";

        }
    }
}


window::~window()
{
    WindowMode winmode{};
    SDL_FreeSurface(screenSurface);
    screenSurface = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(sdlwindow);
    sdlwindow == NULL;
    SDL_Quit();

}
