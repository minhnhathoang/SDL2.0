#ifndef __weapon__h
#define __weapon__h

#include "header.h"
#include "texture.h"
#include "structs.h"

struct Gun {
    int ID;

    int maxAmmo;
    int magazineAmmo;
    int reserveAmmo;

    int projectileID;
    int soundID;
    int effectID;

    SDL_Color color;

    int damage;
    float velocity;
    float radius;

    int nFrames;
    int frameRate;
    float scaleFrame;

    pair<int, int> reloadTime;
    pair<int, int> delayTime;
};


class Weapon {

public:
    Weapon();
    ~Weapon();

    void initGun(int ID, float _scale);

    void update(int _x, int _y, int x_dst, int y_dst, float angle, bool _shooting, SDL_RendererFlip _flip);
    void render(SDL_Rect& camera);

    void reload();

    void laserSight(int x1, int y1, int x2, int y2);

    bool isShooting();

    pair<int, int> getAmmunition();

    vector<Bullet> bullets;

private:

    int x, y;

    float angle;
    float scale;

    int currentGun;

    bool shooting;

    vector<Gun> guns;
    vector<bool> used;
    SDL_RendererFlip flip;
};

#endif // __weapon__h
