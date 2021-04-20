#include "game.h"

int main(int argc, char* argv[]) {

    Uint32 frameStart, frameTime;

    while (true) {

        if (Game::getInstance()->restarting() == true) {
            delete Game::getInstance()->player;
            Game::getInstance()->init();
        } else {
            Game::getInstance()->menu(0);
        }

        while (Game::getInstance()->running()) {
            frameStart = SDL_GetTicks();

            Game::getInstance()->handle();

            Game::getInstance()->update();

            Game::getInstance()->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (1000 / FPS > frameTime) {
                SDL_Delay(1000 / FPS - frameTime);
            }
        }

        if (Game::getInstance()->restarting() == false) {
            Game::getInstance()->clean();
            break;
        }
    }

    return 0;
}
