#ifndef __weapon__h
#define __weapon__h

#include "header.h"
#include "texture.h"

class Weapon {

public:
    Weapon();
    ~Weapon();

    void render(SDL_Renderer* renderer);

private:
    Texture* sprites;

    double angle;
    SDL_Point point;
    int ID;
    int nFrames, currentFrame;
};

#endif // __weapon__h
