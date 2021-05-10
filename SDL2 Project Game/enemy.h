#ifndef __enemy__h
#define __enemy__h

#include "header.h"
#include "player.h"

class Enemy {

public:

    Enemy();
    ~Enemy();

    void update(SDL_Rect& camera, Player* player);
    void render(SDL_Rect camera);

    void findPath(int dst);

    bool testShot();

    int getID();
    int getX();
    int getY();
    int getHP();

    void addHP(int delta);
    float getScale();

    Weapon* weapon;

private:

    int ID;
    int gunID;

    int nFrames;

    int x, y;
    int dx, dy;
    int moveSpeed;
    float scale;

    int hp;

    int rate;
    int delay;

    SDL_RendererFlip flip;

    bool isMove;
    bool isShooting;
};

#endif // __enemy__h
