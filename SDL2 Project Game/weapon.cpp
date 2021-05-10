#include "header.h"
#include "utils.h"
#include "weapon.h"
#include "effect.h"
#include "sound.h"
#include <algorithm>

Weapon::Weapon() {
    guns.clear();
    bullets.clear();
    guns.resize(MAX_GUN);
    used.resize(MAX_GUN, false);
}

void Weapon::reset() {
    fill(used.begin(), used.end(), false);
}

void Weapon::initGun(int ID, float _scale, bool use) {
    scale = _scale;
    if (use) {
        currentGun = ID;
    }

    if (used[ID]) {
        return;
    }

    Gun temp;
    switch (ID) {
        case 0:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 12;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 12;

            temp.frameRate = 20;
            temp.scaleFrame = 0.35;
            temp.nFrames = 2;

            temp.maxAmmo = 35;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;

            temp.color = rgb(255, 251, 213);
            temp.velocity = 40;
            temp.damage = 35;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 2);
            break;
        case 1:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 5;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 7;

            temp.frameRate = 20;
            temp.scaleFrame = 0.65;
            temp.nFrames = 2;

            temp.maxAmmo = 30;
            temp.magazineAmmo = 30;
            temp.reserveAmmo = 30;

            temp.color = rgb(255, 200, 0);
            temp.velocity = 40;
            temp.damage = 20;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 2);
            break;
        case 2:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 0;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 15;

            temp.frameRate = 60;
            temp.scaleFrame = 0.40;
            temp.nFrames = 6;

            temp.maxAmmo = 25;
            temp.magazineAmmo = 25;
            temp.reserveAmmo = 25;

            temp.color = rgb(172, 255, 255);
            temp.velocity = 60;
            temp.damage = 50;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
        case 3:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 9;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 13;

            temp.frameRate = 34;
            temp.scaleFrame = 0.35;
            temp.nFrames = 2;

            temp.magazineAmmo = 30;
            temp.reserveAmmo = 30;
            temp.maxAmmo = 30;

            temp.color = rgb(0, 255, 0);
            temp.velocity = 30;
            temp.damage = 60;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 2);
            break;
        case 4:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 0;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 15;

            temp.frameRate = 60;
            temp.scaleFrame = 0.8;
            temp.nFrames = 6;

            temp.magazineAmmo = 30;
            temp.reserveAmmo = 30;
            temp.maxAmmo = 30;

            temp.color = rgb(255, 255, 255);
            temp.velocity = 40;
            temp.damage = 35;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
        case 5:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 2;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 13;

            temp.frameRate = 60;
            temp.scaleFrame = 0.8;
            temp.nFrames = 6;

            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;


            temp.color = rgb(255, 255, 255);
            temp.velocity = 30;
            temp.damage = 35;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
        case 6:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 1;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 15;

            temp.frameRate = 19;
            temp.scaleFrame = 0.35;
            temp.nFrames = 2;

            temp.magazineAmmo = 30;
            temp.reserveAmmo = 30;
            temp.maxAmmo = 30;

            temp.color = rgb(169, 210, 255);
            temp.velocity = 30;
            temp.damage = 50;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 2);
            break;
        case 7:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 6;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 15;

            temp.frameRate = 40;
            temp.scaleFrame = 0.35;
            temp.nFrames = 5;

            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;

            temp.color = rgb(125, 125, 125);
            temp.velocity = 30;
            temp.damage = 40;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 5);
            break;
        case 8:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 4;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 20;

            temp.frameRate = 12;
            temp.scaleFrame = 0.7;
            temp.nFrames = 2;

            temp.magazineAmmo = 15;
            temp.reserveAmmo = 15;
            temp.maxAmmo = 15;

            temp.color = rgb(255, 0, 0);
            temp.velocity = 20;
            temp.damage = 25;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 2);
            break;
        case 9:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 2;
            temp.effectID = -1;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 40;

            temp.frameRate = 60;
            temp.scaleFrame = 0.7;
            temp.nFrames = 6;

            temp.magazineAmmo = 20;
            temp.reserveAmmo = 20;
            temp.maxAmmo = 20;

            temp.color = rgb(255, 255, 255);
            temp.velocity = 20;
            temp.damage = 20;
            temp.radius = 0;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
        case 10:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 9;
            temp.effectID = 3;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 150;

            temp.frameRate = 60;
            temp.scaleFrame = 0.35;
            temp.nFrames = 7;

            temp.magazineAmmo = 10;
            temp.reserveAmmo = 10;
            temp.maxAmmo = 10;

            temp.color = rgb(255, 255, 255);
            temp.velocity = 5;
            temp.damage = 100;
            temp.radius = 300;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 7);
            break;
        case 11:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.soundID = 9;
            temp.effectID = 2;

            temp.reloadTime.first = temp.reloadTime.second = 50;
            temp.delayTime.first = temp.delayTime.second = 150;

            temp.frameRate = 13;
            temp.scaleFrame = 0.35;
            temp.nFrames = 2;

            temp.magazineAmmo = 7;
            temp.reserveAmmo = 7;
            temp.maxAmmo = 7;

            temp.color = rgb(255, 255, 255);
            temp.velocity = 5;
            temp.damage = 200;
            temp.radius = 500;

            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[temp.projectileID]), 1, 1);
//            Texture::getInstance()->load(string(listGun[ID]), 1, 2);
            break;
        default:
            break;
    }
    used[ID] = true;
}

void Weapon::update(int _x, int _y, int x_dst, int y_dst, float _angle, bool _shooting, SDL_RendererFlip _flip) {

    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (it->time <= 0) {
            bullets.erase(it);
        } else {
            ++it;
        }
    }

    x = _x;
    y = _y;

    shooting = _shooting;

    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (it->time == 0) {
            bullets.erase(it);
        } else {
            it->x += it->velocity * it->dx;
            it->y += it->velocity * it->dy;
            ++it;
        }
    }

    angle = _angle;

    if (_flip == SDL_FLIP_HORIZONTAL) {
        flip = SDL_FLIP_VERTICAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    if (guns[currentGun].delayTime.first != guns[currentGun].delayTime.second) {
        --guns[currentGun].delayTime.first;
        if (guns[currentGun].delayTime.first < 0) {
            guns[currentGun].delayTime.first = guns[currentGun].delayTime.second;
        }
    }

    if (guns[currentGun].reloadTime.first != guns[currentGun].reloadTime.second) {
        --guns[currentGun].reloadTime.first;
        if (guns[currentGun].reloadTime.first < 0) {
            guns[currentGun].reloadTime.first = guns[currentGun].reloadTime.second;
        }
    }


    if (shooting == true) {
        //shooting = false;
        if (guns[currentGun].magazineAmmo > 0) {
            if (guns[currentGun].delayTime.first == guns[currentGun].delayTime.second) {
                Bullet bullet;
                bullet.projectileID = guns[currentGun].projectileID;
                bullet.soundID = guns[currentGun].soundID;
                bullet.effectID = guns[currentGun].effectID;

                bullet.dx = cos(angle * PI / 180);
                bullet.dy = sin(angle * PI / 180);
                bullet.x = x + scale * 100 * bullet.dx;
                bullet.y = y + scale * 100 * bullet.dy;

                bullet.time = 1;
                bullet.velocity = guns[currentGun].velocity;
                bullet.angle = angle;
                bullet.damage = guns[currentGun].damage;
                bullet.radius = guns[currentGun].radius;
                bullet.color = guns[currentGun].color;
                bullets.push_back(bullet);

                Sound::getInstance()->playChunks(guns[currentGun].soundID, 0);
                --guns[currentGun].magazineAmmo;
                shooting = true;
            --guns[currentGun].delayTime.first;
            }
        } else {
            shooting = false;
        }
    }
}

bool Weapon::isShooting() {
    return shooting;
}

void Weapon::reload() {
    if (guns[currentGun].reloadTime.first != guns[currentGun].reloadTime.second) return;
    --guns[currentGun].reloadTime.first;

    Sound::getInstance()->playChunks(3, 1);

    int u = min({ guns[currentGun].reserveAmmo,
                  guns[currentGun].maxAmmo,
                  min(guns[currentGun].maxAmmo - guns[currentGun].magazineAmmo, guns[currentGun].reserveAmmo) });
    guns[currentGun].reserveAmmo -= u;
    guns[currentGun].magazineAmmo += u;
}

void Weapon::addAmmo() {
    guns[currentGun].reserveAmmo += guns[currentGun].maxAmmo;
}

void Weapon::laserSight(int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawBlendMode(Texture::getInstance()->getRenderer(), SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(Texture::getInstance()->getRenderer(), 255, 0, 0, 255);

    float angle = getAngle(x1, y1, x2, y2);
    if ((angle >= 0 && angle < 90) || (angle > -180 && angle < -90)) {
        x1 += 9;
    } else {
        x1 -= 9;
    }
    SDL_RenderDrawLine(Texture::getInstance()->getRenderer(), x1, y1, x2, y2);
}

pair<int, int> Weapon::getAmmunition() {
    return make_pair(guns[currentGun].magazineAmmo, guns[currentGun].reserveAmmo);
}

void Weapon::render(SDL_Rect& camera) {
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        Texture::getInstance()->render(string(listAmmo[it->projectileID]), it->x - camera.x, it->y - camera.y, 1, it->angle, flip, scale);
    }

    int currentFrame = 1;
    if (shooting) {
        currentFrame = (SDL_GetTicks() * guns[currentGun].frameRate / 1000) % guns[currentGun].nFrames + 1;
    }
    if (onScreen(x, y, camera)) {
        Texture::getInstance()->render(string(listGun[currentGun]), x - camera.x, y - camera.y, currentFrame, angle, flip, guns[currentGun].scaleFrame * 0.8f * scale);
    }
}

Gun Weapon::getGun(int id) {
    return guns[id];
}
