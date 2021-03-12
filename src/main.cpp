#include "header.h"
#include "game.h"

int main(int argc, char* argv[]) {

    Uint32 frameStart, frameTime;

    Game* game = new Game();

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handle();

        game->update();

        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (1000 / FPS > frameTime) {
            SDL_Delay(1000 / FPS - frameTime);
        }
    }

    game->clean();

    return 0;
}
