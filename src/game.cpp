#include "header.h"
#include "game.h"

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        logSDLError("SDL_Init");
    }

    window = SDL_CreateWindow("Game SDL2", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError("Create Window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError("Create Renderer");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //assert(TTF_Init() == 0 && TTF_GetError());

    cout << "SDL initialized successfully !" << '\n';

    init();
}

void Game::init() {
    isRunning = true;

    SDL_ShowCursor(true);

    camera = { 0, 0, 0, 0 };


    tileMap = new Map(renderer);
    player = new Player(renderer);


}

void Game::handle() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->quit();
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode < MAX_KEY) {
                    keyboard[event.key.keysym.scancode] = 1;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.scancode < MAX_KEY) {
                    keyboard[event.key.keysym.scancode] = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:

                break;
            case SDL_MOUSEBUTTONUP:

                break;
            default:
                break;
        }
    }
    SDL_GetMouseState(&mouse.x, &mouse.y);
}

void Game::update() {

    player->update();

    updateCamera();



}

void Game::render() {
    SDL_RenderClear(renderer);

    tileMap->render(renderer, camera.x, camera.y);

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {

    }

    player->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::updateCamera() {
    camera.x = player->getX() - SCREEN_WIDTH / 2 + camera.w;
    camera.y = player->getY() - SCREEN_HEIGHT / 2 + camera.h;
}

bool Game::running() {
    return isRunning;
}

void Game::quit() {
    isRunning = false;
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
