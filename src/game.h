#ifndef __game__h
#define __game__h

#include "header.h"

#include "enemy.h"
#include "item.h"

class Game {

public:

    static Game* getInstance() {
        static Game* instance;
        if (instance == nullptr) {
            instance = new Game();
        }
        return instance;
    }

    Game();

    void init();

    void handle();
    void update();
    void render();

    void endgame();

    void menu(int type);
    void renderHUD();

    void clean();
    void quit();

    bool running();

    void updateCamera();

    SDL_Renderer* getRenderer();

private:
    Mouse mouse;
    bool keyboard[MAX_KEY];

    vector<Enemy*> enemies;

    Item* item;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect camera;

    bool isRunning;
    int status;
    int currentLight;
    int currentWeather;

};

#endif // __game__h
