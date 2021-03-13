#ifndef __weapon__h
#define __weapon__h

#include "header.h"
#include "texture.h"

class Weapon {

    struct Bullet {

        double x, y;
        double dx, dy;
        double angle;
        int time;

        Texture* projectile;
    };

public:
    Weapon(SDL_Renderer* renderer);
    ~Weapon() = default;

    void update(SDL_Rect camera, Mouse mouse, int id, SDL_RendererFlip _flip, int _x, int _y);

    void render(SDL_Renderer* renderer, int id);

private:

    bool isShooting;
    double angle;

    vector<int> deltaY;
    vector<SDL_Point> points;
    vector<int> rate;
    int x, y;
    vector<Texture*> sprites;

    vector<pair<int, int>> delay;

    vector<Texture*> projectiles;
    vector<int> speedBullet;
    vector<Bullet> bullets;

    SDL_RendererFlip flip;

    int dx, dy;
};

#endif // __weapon__h
