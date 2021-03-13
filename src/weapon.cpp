#include "header.h"
#include "utils.h"
#include "weapon.h"

Weapon::Weapon(SDL_Renderer* renderer) {

    sprites.resize(MAX_GUN);
    rate.resize(MAX_GUN);
    deltaY.resize(MAX_GUN);
    points.resize(MAX_GUN);
    delay.resize(MAX_GUN);
    projectiles.resize(MAX_GUN);
    speedBullet.resize(MAX_GUN);
    scales.resize(MAX_GUN);

    int id = 0;
    sprites[id] = new Texture(renderer, listGun[id], 6);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 10, 10 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.35;

    id = 1;
    sprites[id] = new Texture(renderer, listGun[id], 5);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 10, 10 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.9;

    id = 2;
    sprites[id] = new Texture(renderer, listGun[id], 5);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 30, 30 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.8;

    id = 3;
    sprites[id] = new Texture(renderer, listGun[id], 6);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 7, 7 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.8;

    id = 4;
    sprites[id] = new Texture(renderer, listGun[id], 6);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 7, 7 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.8;

    id = 5;
    sprites[id] = new Texture(renderer, listGun[id], 6);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 7, 7 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.8;

    id = 6;
    sprites[id] = new Texture(renderer, listGun[id], 6);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 7, 7 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.8;

    id = 7;
    sprites[id] = new Texture(renderer, listGun[id], 6);
    rate[id] = 60;
    deltaY[id] = 0;
    points[id] = {sprites[id]->getFrame(0).w / 2, sprites[id]->getFrame(0).h / 2};
    delay[id] = { 7, 7 };
    projectiles[id] = new Texture(renderer, listBullet[id], 1);
    speedBullet[id] = 30;
    scales[id] = 0.7;
}

void Weapon::update(SDL_Rect camera, Mouse mouse, int id, SDL_RendererFlip _flip, int _x, int _y) {

    x = _x;
    y = _y;

    isShooting = mouse.L;

    if (_flip == SDL_FLIP_HORIZONTAL) {
        flip = SDL_FLIP_VERTICAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    dx = camera.x;
    dy = camera.y;

    angle = getAngle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + deltaY[id], mouse.x, mouse.y);


    if (isShooting) {
        if (delay[id].first == delay[id].second) {
            Bullet bullet;
            bullet.dx = cos(angle * PI / 180);
            bullet.dy = sin(angle * PI / 180);
            bullet.x = x + 100 * bullet.dx;
            bullet.y = y + 100 * bullet.dy;
            bullet.angle = angle;
            bullet.time = 1;
            bullets.push_back(bullet);
        }
        --delay[id].first;
        if (delay[id].first < 0) {
            delay[id].first = delay[id].second;
        }
    } else {
        delay[id] = { delay[id].second, delay[id].second };
    }
}

void Weapon::render(SDL_Renderer* renderer, int id) {
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        SDL_Rect dst = projectiles[id]->getFrame(0);
        projectiles[id]->renderEx(renderer, it->x - dx, it->y - dy, dst.w, dst.h, it->angle);
        it->x += speedBullet[id] * it->dx;
        it->y += speedBullet[id] * it->dy;
    }

    int currentFrame = 0;
    if (isShooting) {
        currentFrame = (SDL_GetTicks() * rate[id] / 1000) % sprites[id]->nFrames;
    }
    sprites[id]->renderEx(renderer, x - dx, y - dy, sprites[id]->getFrame(currentFrame), angle, points[id], flip, scales[id]);
}
