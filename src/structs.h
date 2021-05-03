#ifndef __structs__h
#define __structs__h

#include "texture.h"

struct Mouse {
    int x, y, L, R;
    Mouse() : x(-1), y(-1), L(0), R(0) {}
};

struct Explosion {
    int ID;
    int x, y;
    int time;

    Explosion(int _ID, int _x, int _y, int _time) :
        ID(_ID),
        x(_x),
        y(_y),
        time(_time) {}
};

struct Death {
    int id;
    int x, y;
    int time;
    float scale;

    Death(int _id, int _x, int _y, int _time, float _scale) :
        id(_id),
        x(_x),
        y(_y),
        time(_time),
        scale(_scale) {}
};

struct Bullet {
    double x, y;
    double dx, dy;
    double angle;
    int time;
    double velocity;
    int damage;
    float radius;
    int projectileID;
    int soundID;
    int effectID = 2;
    float scale = 1;
    int alpha = 255;

    SDL_Color color;

    Bullet() : effectID(2) {}
};

struct Particle {
    double x, y;
    double dx, dy;
    double angle;
    int time;
    double velocity;
    float scale = 1;
    int alpha = 255;
    SDL_Color color;
};



#endif // __structs__h

