#include "header.h"
#include "game.h"

int main(int argc, char* argv[]) {

    initSDL(Game::window, Game::renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "GAME SDL2");

    Uint32 frameStart, frameTime;

    if (game->init()) {
        while (game->running()) {
            frameStart = SDL_GetTicks();

            game->handle();

            game->update();

            game->render();

            frameTime = SDL_GetTicks() - frameStart;
            if (PER_FRAME > frameTime) {
                SDL_Delay(PER_FRAME - frameTime);
            }

        }
    } else {
        std::cout << "Game initialization failed ...! " << '\n';

        return -1;
    }

    game->clean();

    return 0;
}
