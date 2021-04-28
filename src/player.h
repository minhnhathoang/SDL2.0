#ifndef __player__h
#define __player__h

#include "texture.h"
#include "tilemap.h"
#include "weapon.h"
#include "sound.h"
#include "effect.h"

class Player {

public:

    static Player* getInstance() {
        static Player* instance;
        if (instance == nullptr) {
            instance = new Player();
        }
        return instance;
    }

    Player();


    void init();
    void update(SDL_Rect& camera, bool key[], Mouse mouse);
    void render(SDL_Rect& camera);

    int getX();
    int getY();
    float getScale();
    int getHP();
    int getOxy();
    int getCoin();
    int getELight();
    void addHP(int delta);

    string getID();

    int getIDGun();

    pair<int, int> getAmmunition();

    Weapon* weapon;
    int idCrew;
    int energyLight;
private:
    int idGun;

    int nFrames;

    int x, y;
    int dx, dy;
    int moveSpeed;

    int hp, oxy, coin;

    int rate;

    bool isMove = 0;

    SDL_RendererFlip flip;


    float scale = 1;
};

#endif // __player__h
