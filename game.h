#ifndef __game__h
#define __game__h

#include "header.h"

class Game {

public:
    Game();
    ~Game();

    void handle();
    void update();
    void render();

    void quit();

    bool running();

    SDL_Renderer* renderer;
    SDL_Window* window;
private:

    bool isRunning;
};

#endif // __game__h
