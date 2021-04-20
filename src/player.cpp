#include "player.h"
#include "utils.h"
#include "tilemap.h"
#include "game.h"

Player::Player() {

    hp = 100;
    oxy = 100;
    coin = 300;

    rate = 35;

    moveSpeed = 4;
    x = 2570 * 50 / 40 + 10;
    y = 752 * 50 / 40 + 10;
    nFrames = 25;

    idCrew = randUint(MAX_CREW - 1);

    Texture::getInstance()->load(string(listCrew[idCrew]), 1, 25);

    flip = SDL_FLIP_NONE;

    dx = dy = 0;

    isMove = 0;

    idGun = 0;
    weapon = new Weapon();

    weapon->initGun(10);
}


void Player::update(SDL_Rect& camera, bool keyboard[], Mouse mouse) {


    if (keyboard[SDL_SCANCODE_E]) {
        weapon->initGun(randUint(9));
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

    oxy--;

    isMove = keyboard[SDL_SCANCODE_W] | keyboard[SDL_SCANCODE_A] | keyboard[SDL_SCANCODE_S] | keyboard[SDL_SCANCODE_D];


    weapon->update(x, y, mouse.x, mouse.y, getAngle(x - camera.x, y - camera.y, mouse.x, mouse.y), mouse.L, flip);

}

void Player::render(SDL_Rect& camera) {

    int currentFrame = nFrames;

    if (isMove) {
        currentFrame = (SDL_GetTicks() * rate / 1000) % (nFrames - 1) + 1;
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
