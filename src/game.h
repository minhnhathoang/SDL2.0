#ifndef __game__h
#define __game__h

#include "header.h"

#include "tilemap.h"
#include "player.h"
#include "enemy.h"

class Game {

public:
    Game();
    ~Game();

    void init();

    void handle();
    void update();
    void render();

    void clean();
    void quit();

    bool running();


    void updateCamera();

private:

    Player* player;
    vector<Enemy*> enemies;

    Map* tileMap;

    SDL_Rect camera;

    bool isRunning;

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    Mouse mouse;
    bool keyboard[MAX_KEY];
};

#endif // __game__h
