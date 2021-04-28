#ifndef __item__h
#define __item__h

#include "header.h"
#include "player.h"
#include "tilemap.h"
#include "texture.h"

class Item {

public:
    Item();

    void update(bool keyboard[]);
    void render(SDL_Rect camera);

    void randomPosition(int &x, int &y);

private:

    string boxBulletID;
    vector<SDL_Point> listBoxBullet;

    string flashlightID;
    vector<SDL_Point> listFlashlight;

    string medkitID;
    vector<SDL_Point> listMedkit;


};

#endif // __item__h
