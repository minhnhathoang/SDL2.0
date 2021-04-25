#ifndef __game__h
#define __game__h

#include "header.h"

#include "tilemap.h"
#include "player.h"
#include "enemy.h"
#include "text.h"
#include "sound.h"
#include "effect.h"
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
    bool restarting();


    void updateCamera();

    SDL_Renderer* getRenderer();

    Player* player = nullptr;
private:

    vector<Enemy*> enemies;


    SDL_Rect camera;


    SDL_Window* window;
    SDL_Renderer* renderer;

    Mouse mouse;
    bool keyboard[MAX_KEY];

    bool isRestarting = 0;
    bool isRunning;

    int status;

};

#endif // __game__h
