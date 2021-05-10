#ifndef __game__h
#define __game__h

#include "header.h"
#include "enemy.h"

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

    void option();

    SDL_Renderer* getRenderer();

    int getTime();

private:
    Mouse mouse;
    bool keyboard[MAX_KEY];

    vector<Enemy*> enemies;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect camera;

    bool isRunning;
    int status;
    int currentLight;
    int currentWeather;
    bool showTab;

    int time;

    int score;
};

#endif // __game__h
