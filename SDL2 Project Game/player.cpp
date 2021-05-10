#include "player.h"
#include "utils.h"
#include "tilemap.h"
#include "game.h"
#include "text.h"

Player::Player() {
    weapon = new Weapon();
    lockGuns.resize(12);
    Texture::getInstance()->load(string(listGun[0]), 1, 2);
    Texture::getInstance()->load(string(listGun[1]), 1, 2);
    Texture::getInstance()->load(string(listGun[2]), 1, 6);
    Texture::getInstance()->load(string(listGun[3]), 1, 2);
    Texture::getInstance()->load(string(listGun[4]), 1, 6);
    Texture::getInstance()->load(string(listGun[5]), 1, 6);
    Texture::getInstance()->load(string(listGun[6]), 1, 2);
    Texture::getInstance()->load(string(listGun[7]), 1, 5);
    Texture::getInstance()->load(string(listGun[8]), 1, 2);
    Texture::getInstance()->load(string(listGun[9]), 1, 6);
    Texture::getInstance()->load(string(listGun[10]), 1, 7);
    Texture::getInstance()->load(string(listGun[11]), 1, 2);
}

Player::~Player() {
    delete weapon;
}

void Player::init() {

    Texture::getInstance()->load(listCrew[ID], 1, nFrames = 25);

    flip = SDL_FLIP_NONE;

    x = 5572, y = 4600;

    dx = dy = 0;

    moveSpeed = 5;
    rate = 30;

    hp = 100;
    oxy = 10000;
    eLight = 10000;

    isMove = 0;

    scale = 1;

    weapon->reset();
    weapon->initGun(gunID = 0, scale);

    name = "";
    name = enterName(3, 9, 1, 60);

    fill(lockGuns.begin(), lockGuns.end(), false);
    lockGuns[0] = lockGuns[1] = lockGuns[8] = true;
}

void Player::setColor(int colorID) {
    ID = colorID;
    Texture::getInstance()->load(listCrew[ID], 1, nFrames = 25);
}

void Player::update(SDL_Rect& camera, bool keyboard[], Mouse mouse) {

    if (oxy <= 0 || hp <= 0) {
        return;
    }

    if (keyboard[SDL_SCANCODE_1] && lockGuns[0]) {
        weapon->initGun(gunID = 0, scale);
    } else if (keyboard[SDL_SCANCODE_2] && lockGuns[1]) {
        weapon->initGun(gunID = 1, scale);
    } else if (keyboard[SDL_SCANCODE_3] && lockGuns[2]) {
        weapon->initGun(gunID = 2, scale);
    } else if (keyboard[SDL_SCANCODE_4] && lockGuns[3]) {
        weapon->initGun(gunID = 3, scale);
    } else if (keyboard[SDL_SCANCODE_5] && lockGuns[4]) {
        weapon->initGun(gunID = 4, scale);
    } else if (keyboard[SDL_SCANCODE_6] && lockGuns[5]) {
        weapon->initGun(gunID = 5, scale);
    } else if (keyboard[SDL_SCANCODE_7] && lockGuns[6]) {
        weapon->initGun(gunID = 6, scale);
    } else if (keyboard[SDL_SCANCODE_8] && lockGuns[7]) {
        weapon->initGun(gunID = 7, scale);
    } else if (keyboard[SDL_SCANCODE_9] && lockGuns[8]) {
        weapon->initGun(gunID = 8, scale);
    } else if (keyboard[SDL_SCANCODE_0] && lockGuns[10]) {
        weapon->initGun(gunID = 10, scale);
    } else if (keyboard[SDL_SCANCODE_MINUS] && lockGuns[11]) {
        weapon->initGun(gunID = 11, scale);
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

    if (mouse.x > x -  camera.x) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_HORIZONTAL;
    }

    x += dx;

    if (Map::getInstance()->getTypeOfTile(x, y + 40 * scale) != 1) {
        x -= dx;
    }

    y += dy;

    if (Map::getInstance()->getTypeOfTile(x, y + 40 * scale) != 1) {
        y -= dy;
    }

    isMove = keyboard[SDL_SCANCODE_W] | keyboard[SDL_SCANCODE_A] | keyboard[SDL_SCANCODE_S] | keyboard[SDL_SCANCODE_D];

    weapon->update(x, y, mouse.x, mouse.y, getAngle(x - camera.x, y - camera.y, mouse.x, mouse.y), mouse.L, flip);

    oxy -= 0.7;

    for (int i = 0; i < MAX_GUN; ++i) {
        if (lockGuns[i] == true) {
            weapon->initGun(i, scale, 0);
        }
    }
}

bool Player::isShooting() {
    return weapon->isShooting();
}

void Player::render(SDL_Rect& camera, Mouse mouse) {

    if (oxy <= 0 || hp <= 0) {
        Effect::getInstance()->addDeath(ID, x, y, 1000, 0);
        return;
    }

    int currentFrame = nFrames;

    if (isMove) {
        currentFrame = (SDL_GetTicks() * rate / 1000) % (nFrames - 1) + 1;
    }

    if (gunID == 2) {
        weapon->laserSight(x - camera.x, y - camera.y - 10, mouse.x, mouse.y);
    }

    Texture::getInstance()->render(listCrew[ID], x - camera.x, y - camera.y, currentFrame, 0, flip, 0.8 * scale);

//    if (umbrella) {
//        Texture::getInstance()->load("assets/images/item/umbrella.png", 1, 1);
//        Texture::getInstance()->render("assets/images/item/umbrella.png", x - camera.x, y - camera.y - 15, 1, 0, flip, 0.2);
//    }

    weapon->render(camera);
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

float Player::getScale() {
    return scale;
}

string Player::getName() {
    return name;
}

void Player::setName(string _name) {
    name = _name;
}

int Player::getHP() {
    return hp;
}

void Player::addHP(float delta) {
    hp += delta;
    hp = min(hp, 100.0);
    hp = max(hp, 0.0);
}

int Player::getOxy() {
    oxy = min(oxy, 10000.0);
    oxy = max(oxy, 0.0);
    return oxy;
}

void Player::addOxy(float delta) {
    oxy += delta;
    oxy = min(oxy, 10000.0);
    oxy = max(oxy, 0.0);
}

int Player::getELight() {
    return eLight;
}

int Player::getID() {
    return ID;
}

pair<int, int> Player::getAmmunition() {
    return weapon->getAmmunition();
}

int Player::getGunID() {
    return gunID;
}

string Player::enterName(int minSize, int maxSize, bool show, int fontSize) {

    string text = "";

    SDL_Event event;

    bool quit = false;

    SDL_StartTextInput();
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_RETURN && text.size() >= minSize) {
                        quit = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                        text = text.substr(0, int(text.size() - 1));
                    }
                    break;
                case SDL_TEXTINPUT:
                    if (text.size() < maxSize) {
                        text += event.text.text;
                        cerr << text << endl;
                    }
                    break;
            }
        }
        if (show) {
            Text::getInstance()->render(40, "Enter your name", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, CENTER);
            if (text.size() < maxSize) {
                Text::getInstance()->render(fontSize, text + '_', SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CENTER);
            } else {
                Text::getInstance()->render(fontSize, text, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CENTER);
            }
            SDL_RenderPresent(Game::getInstance()->getRenderer());
            SDL_RenderClear(Game::getInstance()->getRenderer());
        }
    }
    SDL_StopTextInput();

    return text;
}
