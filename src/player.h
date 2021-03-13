#ifndef __player__h
#define __player__h

#include "texture.h"
#include "tilemap.h"
#include "weapon.h"

class Player {

public:
    Player(SDL_Renderer* renderer);

    ~Player();

    void update(Map* &tileMap, SDL_Rect camera, bool key[], Mouse mouse);
    void render(SDL_Renderer* renderer);


    int getX();
    int getY();

private:
    int idCrew;
    int idGun;

    Texture* sprites;
    Weapon* weapon;

    int nFrames;

    int x, y;
    int dx, dy;
    int moveSpeed;

    int rate;

    bool isMove = 0;

    SDL_RendererFlip flip;
};

#endif // __player__h
