#include "player.h"
#include "utils.h"
#include "tilemap.h"

Player::Player(SDL_Renderer* renderer) {
    rate = 35;

    moveSpeed = 4;
    x = 2570;
    y = 752;
    nFrames = 25;

    idCrew = randUint(MAX_CREW);

    sprites = new Texture(renderer, listCrew[idCrew], 25);

    flip = SDL_FLIP_NONE;

    dx = dy = 0;

    isMove = 0;

    idGun = 0;
    weapon = new Weapon(renderer);
}

Player::~Player() {

}

void Player::update(Map* &tileMap, SDL_Rect camera, bool keyboard[], Mouse mouse) {

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

    if (tileMap->getTypeOfTile(x, y + 50) != 1) {
        x -= dx;
    }

    y += dy;

    if (tileMap->getTypeOfTile(x, y + 50) != 1) {
        y -= dy;
    }

    dx = camera.x;
    dy = camera.y;

    isMove = keyboard[SDL_SCANCODE_W] | keyboard[SDL_SCANCODE_A] | keyboard[SDL_SCANCODE_S] | keyboard[SDL_SCANCODE_D];

    weapon->update(camera, mouse, idGun, flip, x, y);
}

void Player::render(SDL_Renderer* renderer) {

    int currentFrame = nFrames - 1;

    if (isMove) {
        currentFrame = (SDL_GetTicks() * rate / 1000) % (nFrames - 1);
    }

    sprites->renderEx(renderer, x - dx, y - dy, sprites->getFrame(currentFrame), 0, SDL_Point { x - dx, y - dy }, flip);

    weapon->render(renderer, idGun);
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}
