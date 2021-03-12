#include "player.h"
#include "utils.h"

Player::Player(SDL_Renderer* renderer) {
    moveSpeed = 4;
    x = 2570;
    y = 752;
    sprites = new Texture(renderer, listCrew[randUint(MAX_CREW)]);
}

Player::~Player() {

}

void Player::update() {

}

void Player::render(SDL_Renderer* renderer) {

    int currentFrame = (SDL_GetTicks() * rate / 1000) % nFrames;

}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}
