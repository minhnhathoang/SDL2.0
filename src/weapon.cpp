#include "header.h"
#include "utils.h"
#include "weapon.h"
#include <algorithm>
#include "effect.h"
#include "sound.h"

Weapon::Weapon() {
    guns.clear();
    bullets.clear();
    guns.resize(10);
    shooting = false;
    //currentGun = 0;
}

void Weapon::initGun(int ID, float _scale) {
    currentGun = ID;
    scale = _scale;
    Gun temp;
    switch (ID) {
        case 0:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 10;
            temp.delayTime.first = temp.delayTime.second = 10;
            temp.velocity = 60;
            temp.frameRate = 60;
            temp.scaleFrame = 0.35;
            temp.nFrames = 6;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 0;
            temp.effectID = 5;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
        case 1:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 5;
            temp.delayTime.first = temp.delayTime.second = 5;
            temp.velocity = 40;
            temp.frameRate = 60;
            temp.scaleFrame = 0.9;
            temp.nFrames = 5;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 6;
            temp.effectID = 12;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 5);
            break;
        case 2:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 20;
            temp.delayTime.first = temp.delayTime.second = 20;
            temp.velocity = 30;
            temp.frameRate = 60;
            temp.scaleFrame = 0.8;
            temp.nFrames = 5;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 2;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 5);
            break;
         case 3:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 10;
            temp.delayTime.first = temp.delayTime.second = 10;
            temp.velocity = 30;
            temp.frameRate = 60;
            temp.scaleFrame = 0.8;
            temp.nFrames = 6;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 2;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
         case 4:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 10;
            temp.delayTime.first = temp.delayTime.second = 10;
            temp.velocity = 30;
            temp.frameRate = 60;
            temp.scaleFrame = 0.8;
            temp.nFrames = 6;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 0;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
         case 5:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 10;
            temp.delayTime.first = temp.delayTime.second = 10;
            temp.velocity = 30;
            temp.frameRate = 60;
            temp.scaleFrame = 0.8;
            temp.nFrames = 6;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 1;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
         case 6:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 10;
            temp.delayTime.first = temp.delayTime.second = 10;
            temp.velocity = 30;
            temp.frameRate = 40;
            temp.scaleFrame = 0.35;
            temp.nFrames = 5;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 12;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 5);
            break;
         case 7:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 10;
            temp.delayTime.first = temp.delayTime.second = 10;
            temp.velocity = 30;
            temp.frameRate = 60;
            temp.scaleFrame = 0.7;
            temp.nFrames = 6;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 2;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 6);
            break;
        case 8:
            temp.ID = ID;
            temp.projectileID = ID;
            temp.reloadTime.first = temp.reloadTime.second = 10;
            temp.delayTime.first = temp.delayTime.second = 10;
            temp.velocity = 10;
            temp.frameRate = 60;
            temp.scaleFrame = 0.35;
            temp.nFrames = 7;
            temp.magazineAmmo = 35;
            temp.reserveAmmo = 35;
            temp.maxAmmo = 35;
            temp.soundID = 16;
            temp.effectID = 13;
            guns[ID] = temp;
            Texture::getInstance()->load(string(listAmmo[ID]), 1, 1);
            Texture::getInstance()->load(string(listGun[ID]), 1, 7);
            break;
        default:
            break;
    }
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

    if (shooting == true) {
        if (guns[currentGun].magazineAmmo > 0) {
            if (guns[currentGun].delayTime.first == guns[currentGun].delayTime.second) {
                Bullet bullet;
                bullet.dx = cos(angle * PI / 180);
                bullet.dy = sin(angle * PI / 180);
                bullet.x = x + 100 * bullet.dx;
                bullet.y = y + 100 * bullet.dy;
                bullet.velocity = guns[currentGun].velocity;
                bullet.angle = angle;
                bullet.time = 1;
                bullet.projectileID = currentGun;
                bullet.soundID = guns[currentGun].soundID;
                bullet.effectID = guns[currentGun].effectID;
                bullets.push_back(bullet);
                Sound::getInstance()->playChunks(guns[currentGun].soundID, 0);
                --guns[currentGun].magazineAmmo;
            }
            --guns[currentGun].delayTime.first;
            if (guns[currentGun].delayTime.first < 0) {
                guns[currentGun].delayTime.first = guns[currentGun].delayTime.second;
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
    Sound::getInstance()->playChunks(3, 1);

    int u = min({ guns[currentGun].reserveAmmo,
                  guns[currentGun].maxAmmo,
                  min(guns[currentGun].maxAmmo - guns[currentGun].magazineAmmo, guns[currentGun].reserveAmmo) });
    guns[currentGun].reserveAmmo -= u;
    guns[currentGun].magazineAmmo += u;
}

void Weapon::laserSight(int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(Texture::getInstance()->getRenderer(), 200, 0, 0, 255);
    //SDL_SetRenderDrawBlendMode(Texture::getInstance()->getRenderer(), SDL_BLENDMODE_NONE);
    SDL_RenderDrawLine(Texture::getInstance()->getRenderer(), x1, y1, x2, y2);

    //SDL_SetRenderDrawBlendMode(Texture::getInstance()->getRenderer(), SDL_BLENDMODE_NONE);
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

    Texture::getInstance()->render(string(listGun[currentGun]), x - camera.x, y - camera.y, currentFrame, angle, flip, guns[currentGun].scaleFrame * 0.8f * scale);
    //Texture::getInstance()->render(string(listGun[currentGun]), x - camera.x, y - camera.y, currentFrame, angle, flip, guns[currentGun].scaleFrame * 2.0f);
}
