#include "player.h"
#include "utils.h"
#include "tilemap.h"
#include "game.h"

Player::Player() {
    weapon = new Weapon();
}

void Player::init() {

    idCrew = idCrew = randUint(MAX_CREW - 1);
    Texture::getInstance()->load(string(listCrew[idCrew]), 1, nFrames = 25);

    rate = 35;

    x = 5572, y = 4600;
    //x = 2000, y = 2000;
    dx = dy = 0;
    moveSpeed = 3;

    hp = 100;
    oxy = 100;
    energySpotlight = 100;
    coin = 300;

    flip = SDL_FLIP_NONE;
    isMove = 0;

    idGun = 0;
    weapon->initGun(idGun);

}


void Player::update(SDL_Rect& camera, bool keyboard[], Mouse mouse) {

    if (oxy <= 0 || hp <= 0) {
        return;
    }

    if (keyboard[SDL_SCANCODE_E]) {
        weapon->initGun(randUint(8));
    }
    if (keyboard[SDL_SCANCODE_R]) {
        weapon->reload();
    }

    dx = 0;
    dy = 0;

    if (keyboard[SDL_SCANCODE_W]) {
        dy -= moveSpeed;
    }
    if (keyboard[SDL_SCANCODE_S]) {
        dy += moveSpeed;
    }
    if (keyboard[SDL_SCANCODE_A]) {
        dx -= moveSpeed;
    }
    if (keyboard[SDL_SCANCODE_D]) {
        dx += moveSpeed;
    }

    if (mouse.x > SCREEN_WIDTH / 2) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_HORIZONTAL;
    }

    x += dx;

    if (Map::getInstance()->getTypeOfTile(x, y + 40) != 1) {
        x -= dx;
    }

    y += dy;

    if (Map::getInstance()->getTypeOfTile(x, y + 40) != 1) {
        y -= dy;
    }


    isMove = keyboard[SDL_SCANCODE_W] | keyboard[SDL_SCANCODE_A] | keyboard[SDL_SCANCODE_S] | keyboard[SDL_SCANCODE_D];


    weapon->update(x, y, mouse.x, mouse.y, getAngle(x - camera.x, y - camera.y, mouse.x, mouse.y), mouse.L, flip);

    if (weapon->isShooting() == true) {
        //Effect::getInstance()->shake(camera, 10);
    }

}

void Player::render(SDL_Rect& camera) {

    if (oxy <= 0 || hp <= 0) {
        Effect::getInstance()->addDeath(idCrew, x, y, 1000, 0);
        return;
    }

    int currentFrame = nFrames;

    if (isMove) {
        currentFrame = (SDL_GetTicks() * rate / 1000) % (nFrames - 1) + 1;
    }


    if (idGun == 0) {
        int m1, m2;
        SDL_GetMouseState(&m1, &m2);
        weapon->laserSight(x - camera.x, y - camera.y - 10, m1, m2);
    }

    Texture::getInstance()->render(string(listCrew[idCrew]), x - camera.x, y - camera.y, currentFrame, 0, flip, 0.8f);

    weapon->render(camera);

}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

int Player::getHP() {
    return hp;
}

int Player::getOxy() {
    oxy = min(oxy, 100);
    oxy = max(oxy, 0);
    return oxy;
}

int Player::getCoin() {
    return coin;
}

void Player::addHP(int delta) {
    hp += delta;
    hp = min(hp, 100);
    hp = max(hp, 0);
}

string Player::getID() {
    return string(listCrew[idCrew]);
}

pair<int, int> Player::getAmmunition() {
    return weapon->getAmmunition();
}

int Player::getIDGun() {
    return idGun;
}
