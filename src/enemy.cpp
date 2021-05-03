#include "enemy.h"
#include "utils.h"
#include "tilemap.h"
#include "algorithm"

Enemy::Enemy() {
    while (true) {
        x = randUint(4000);
        y = randUint(7000);
        if (Map::getInstance()->getTypeOfTile(x, y + scale * 40) == 1 &&
                getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), x, y) > 2000)
            break;
    }

    rate = 30;
    moveSpeed = randInt(1, 4);

    hp = 100;
    scale = randF(1, 2);

    nFrames = 25;

    ID = randUint(MAX_CREW - 1);

    Texture::getInstance()->load(listCrew[ID], 1, 25);

    flip = SDL_FLIP_NONE;

    dx = 0;
    dy = 0;

    isMove = 0;


    weapon = new Weapon();
    gunID = randUint(7);
    weapon->initGun(gunID, scale);
}

Enemy::~Enemy() {
    delete weapon;
}

void Enemy::update(SDL_Rect& camera, Player* player) {

    x += dx;

    if (Map::getInstance()->getTypeOfTile(x, y + scale * 40) != 1) {
        x -= dx;
        dx = 0;
    }

    y += dy;

    if (Map::getInstance()->getTypeOfTile(x, y + scale * 40) != 1) {
        y -= dy;
        dy = 0;
    }

    if (dx > 0) {
        flip = SDL_FLIP_NONE;
    } else if (dx < 0) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    if (dx || dy) {
        isMove = true;
    } else {
        isMove = false;
    }

    dx = dy = 0;

    weapon->update(x, y, player->getX(), player->getY(), getAngle(x, y, player->getX(), player->getY()), getDistance(x, y, player->getX(), player->getY()) <= 300, flip);
}

void Enemy::render(SDL_Rect camera) {

    int currentFrame = nFrames;

    if (isMove) {
        currentFrame = (SDL_GetTicks() * rate / 1000) % (nFrames - 1) + 1;
    }

    Texture::getInstance()->render(listCrew[ID], x - camera.x, y - camera.y, currentFrame, 0, flip, 0.8 * scale);
    weapon->render(camera);
}

void Enemy::findPath(int dst) {
    int src = Map::getInstance()->getTile(x, y + scale * 40);

    if (dst == src)
        return;

    queue<int> q;
    vector<int> vst(Map::getInstance()->adj.size() + 10, 0);

    while (!q.empty()) q.pop();

    q.push(dst);
    vst[dst] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : Map::getInstance()->adj[u]) {
            if (v == src) {
                if (v == u - 1) {
                    dx += moveSpeed;
                } else if (v == u + 1) {
                    dx -= moveSpeed;
                } else if (v < u) {
                    dy += moveSpeed;
                } else if (v > u) {
                    dy -= moveSpeed;
                }
                return;
            }
            if (vst[v] == 0) {
                q.push(v);
                vst[v] = 1;
            }
        }
    }
}

int Enemy::getX() {
    return x;
}

int Enemy::getY() {
    return y;
}

void Enemy::addHP(int delta) {
    hp += delta;
}

int Enemy::getHP() {
    return hp;
}

int Enemy::getID() {
    return ID;
}

float Enemy::getScale() {
    return scale;
}
