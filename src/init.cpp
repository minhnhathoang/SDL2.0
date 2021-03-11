#include "header.h"
#include "init.h"
#include "debug.h"


void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             int screenWidth, int screenHeight, const char* windowTitle) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        logSDLError("SDL_Init");
    }

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        logSDLError("Create Window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        logSDLError("Create Renderer");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);


    if (TTF_Init() < 0) {
        std::cout << TTF_GetError();
    }

    SDL_ShowCursor(false);

    cout << "SDL initialized successfully !" << '\n';
}
