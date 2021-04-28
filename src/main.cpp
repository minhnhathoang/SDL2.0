#include "game.h"

int main(int argc, char* argv[]) {

    Uint32 frameStart, frameTime;

    while (true) {

        if (Game::getInstance()->restarting() == true) {
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
            cout << frameTime << endl;
        }

        if (Game::getInstance()->restarting() == false) {
            break;
        }
    }

    Game::getInstance()->clean();

    return 0;
}
