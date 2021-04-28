#ifndef __enemy__h
#define __enemy__h

#include "header.h"
#include "tilemap.h"
#include "weapon.h"
#include "effect.h"
#include "player.h"

class Enemy {

public:
    Enemy();

    ~Enemy();

    void update(SDL_Rect& camera, Player* player);
    void render(SDL_Rect camera);

    void findPath(int dst);

    int getID();

    int getX();
    int getY();
    int getHP();
    void addHP(int delta);

    Weapon* weapon;

private:
    int idCrew;
    int idGun;


    int nFrames;

    int x, y;
    int dx, dy;
    int moveSpeed;
    int hp;

    int rate;

    bool isMove = 0;

    SDL_RendererFlip flip;

    float scale;

};

#endif // __enemy__h
