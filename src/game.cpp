#include "game.h"

Game::Game() {

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

}

void Game::render() {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}


void Game::quit() {
    isRunning = false;
}

bool Game::running() {
    return isRunning;
}
