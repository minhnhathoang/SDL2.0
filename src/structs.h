#ifndef __structs__h
#define __structs__h

#include "texture.h"

struct Explosion {
    int ID;
    int x, y;
    int time;

    Explosion(int _ID, int _x, int _y, int _time) {
        ID = _ID;
        x = _x;
        y = _y;
        time = _time;
    }
};

struct Death {
    int id;
    int x, y;
    int time;
    float angle;

    Death(int _id, int _x, int _y, int _time, float _angle) {
        id = _id;
        x = _x;
        y = _y;
        time = _time;
        angle = _angle;
    }
};

struct Bullet {

    double x, y;
    double dx, dy;
    double angle;
    int time;
    int projectileID;
    int soundID;
    int effectID;

};

#endif // __structs__h

