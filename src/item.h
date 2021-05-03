#ifndef __item__h
#define __item__h

#include "header.h"
#include "player.h"
#include "tilemap.h"
#include "texture.h"

struct FLight {
    int x, y;
    double angle;
    int time;
};

class Item {

public:
    Item();

    void update(bool keyboard[]);
    void render(SDL_Rect camera);

    void randomPosition(int &x, int &y, int distance = -1);

private:

    string boxBulletID;
    vector<SDL_Point> listBoxBullet;

    string flashlightID;
    vector<FLight> listFlashlight;

    string medkitID;
    vector<SDL_Point> listMedkit;

};

#endif // __item__h
