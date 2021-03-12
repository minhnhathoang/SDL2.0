#ifndef __player__h
#define __player__h

#include "texture.h"
#include "weapon.h"

class Player {

public:
    Player(SDL_Renderer* renderer);

    ~Player();

    void update();
    void render(SDL_Renderer* renderer);


    int getX();
    int getY();

private:
    int ID;

    Texture* sprites;
    Weapon* weapon;

    int nFrames;

    int x, y;
    int moveSpeed;

    int rate;
    int currentFrame;
};

#endif // __player__h
