#ifndef __player__h
#define __player__h

#include "texture.h"
#include "tilemap.h"
#include "weapon.h"
#include "sound.h"
#include "effect.h"

class Player {

public:
    Player();

    ~Player() = default;

    void update(SDL_Rect& camera, bool key[], Mouse mouse);
    void render(SDL_Rect& camera);

    int getX();
    int getY();
    int getHP();
    int getOxy();
    int getCoin();
    void addHP(int delta);

    string getID();

    int getIDGun();

    pair<int, int> getAmmunition();

    Weapon* weapon;
    int idCrew;
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
};

#endif // __player__h
