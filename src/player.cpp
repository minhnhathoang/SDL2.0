#include "player.h"
#include "utils.h"
#include "tilemap.h"
#include "game.h"
#include "text.h"

Player::Player() {
    weapon = new Weapon();
}

Player::~Player() {
    delete weapon;
}

void Player::init() {
    ID = randUint(MAX_CREW - 1);
    Texture::getInstance()->load(listCrew[ID], 1, nFrames = 25);

    flip = SDL_FLIP_NONE;

    x = 5572, y = 4600;

    dx = dy = 0;

    moveSpeed = 4;
    rate = 35;

    hp = 100;
    oxy = 10000;
    energyLight = 5000;

    isMove = 0;

    scale = 1;
    for (int i = 0; i < 10; ++i) {
        weapon->initGun(i, scale);
    }

    gunID = 0;
    weapon->initGun(gunID, scale);

    name = "";
    name = enterName(3, 9, 1, 60, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2);
}


void Player::update(SDL_Rect& camera, bool keyboard[], Mouse mouse) {

    if (oxy <= 0 || hp <= 0) {
        return;
    }

    if (keyboard[SDL_SCANCODE_E]) {
        weapon->initGun(randUint(8), scale);
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

    if (weapon->isShooting() == true) {
        //Effect::getInstance()->shake(camera, 10);
        SDL_SetTextureColorMod(Texture::getInstance()->getTexture("assets/images/modmap222.png"), randUint(255), randUint(255), randUint(255));
    }

}

bool Player::isShooting() {
    return weapon->isShooting();
}

void Player::render(SDL_Rect& camera) {

    if (oxy <= 0 || hp <= 0) {
        Effect::getInstance()->addDeath(ID, x, y, 1000, 0);
        return;
    }

    int currentFrame = nFrames;

    if (isMove) {
        currentFrame = (SDL_GetTicks() * rate / 1000) % (nFrames - 1) + 1;
    }


    if (ID == 0) {
        int m1, m2;
        SDL_GetMouseState(&m1, &m2);
        weapon->laserSight(x - camera.x, y - camera.y - 10, m1, m2);
    }

    Texture::getInstance()->render(listCrew[ID], x - camera.x, y - camera.y, currentFrame, 0, flip, 0.8 * scale);


    //Texture::getInstance()->load("assets/images/umbrella.png", 1, 1);

    //Texture::getInstance()->render("assets/images/umbrella.png", x - camera.x, y - camera.y - 15, 1, 0, flip, 0.2);
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

void Player::addHP(int delta) {
    hp += delta;
    hp = min(hp, 100);
    hp = max(hp, 0);
}

int Player::getOxy() {
    oxy = min(oxy, 10000);
    oxy = max(oxy, 0);
    return oxy;
}

void Player::addOxy(int delta) {
    oxy += delta;
    oxy = min(oxy, 10000);
    oxy = max(oxy, 0);
}

int Player::getELight() {
    return energyLight;
}

string Player::getID() {
    return string(listCrew[ID]);
}

pair<int, int> Player::getAmmunition() {
    return weapon->getAmmunition();
}

int Player::getGunID() {
    return gunID;
}

string Player::enterName(int minSize, int maxSize, bool show, int fontSize, int x, int y) {

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
            if (text.size() < maxSize) {
                Text::getInstance()->render(40, "Enter your name ", x - 15, y - 50);
                Text::getInstance()->render(fontSize, text + '_', x, y);
            } else {
                Text::getInstance()->render(40, "Enter your name ", x - 15, y - 50);
                Text::getInstance()->render(fontSize, text, x, y);
            }
            SDL_RenderPresent(Game::getInstance()->getRenderer());
            SDL_RenderClear(Game::getInstance()->getRenderer());
        }
    }
    SDL_StopTextInput();

    return text;
}
