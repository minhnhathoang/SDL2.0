#ifndef __weapon__h
#define __weapon__h

#include "header.h"
#include "texture.h"
#include "structs.h"

class Weapon {

public:

    Weapon();
    ~Weapon() = default;

    void reset();

    void initGun(int ID, float _scale, bool use = true);

    void update(int _x, int _y, int x_dst, int y_dst, float angle, bool _shooting, SDL_RendererFlip _flip);
    void render(SDL_Rect& camera);

    void reload();
    void addAmmo();

    void laserSight(int x1, int y1, int x2, int y2);

    bool isShooting();

    Gun getGun(int id);

    pair<int, int> getAmmunition();

    vector<Bullet> bullets;


private:

    int x, y;

    float angle;
    float scale;

    int currentGun;

    bool shooting;

    SDL_RendererFlip flip;

    vector<bool> used;
    vector<Gun> guns;
};

#endif // __weapon__h
