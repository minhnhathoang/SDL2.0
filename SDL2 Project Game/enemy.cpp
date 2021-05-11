#include "enemy.h"
#include "game.h"

Enemy::Enemy() {

    scale = randF(1, 1.5);

    while (true) {
        x = randUint(4000);
        y = randUint(7000);
        if (Map::getInstance()->getTypeOfTile(x, y + scale * 40) == 1 &&
                getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), x, y) > 2000)
            break;
    }

    rate = 30;
    moveSpeed = randInt(3, 4);

    hp = 100 * scale;

    nFrames = 25;

    ID = randUint(MAX_CREW - 1);

    Texture::getInstance()->load(listCrew[ID], 1, 25);

    flip = SDL_FLIP_NONE;

    dx = 0;
    dy = 0;

    isMove = 0;

    delay = 100;

    weapon = new Weapon();
    gunID = randUint(9);
    if (Game::getInstance()->getTime() > 100000) {
        gunID = randUint(10);
    }
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

    if (dx > 0 || x < Player::getInstance()->getX()) {
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

    if (delay != 20) {
        --delay;
        if (delay < 0) {
            delay = 20;
        }
    }

    isShooting = false;
    if (delay == 20) {
        if (abs(y - player->getY()) <= 350 && (getDistance(x, y, player->getX(), player->getY()) <= 500)) {
            isShooting =  this->testShot();
        }
        --delay;
    }


    weapon->update(x, y, player->getX(), player->getY(), getAngle(x, y, player->getX(), player->getY()), isShooting, flip);
}

void Enemy::render(SDL_Rect camera) {

    if (!onScreen(x, y, camera)) return;

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

bool Enemy::testShot() {
    if (Player::getInstance()->getHP() <= 0 || Player::getInstance()->getOxy() <= 0) return false;

    Bullet bullet;
    bullet.angle = getAngle(x, y, Player::getInstance()->getX(), Player::getInstance()->getY());

    bullet.dx = cos(bullet.angle * PI / 180);
    bullet.dy = sin(bullet.angle * PI / 180);
    bullet.x = x + scale * 100 * bullet.dx;
    bullet.y = y + scale * 100 * bullet.dy;

    bullet.velocity = weapon->getGun(gunID).velocity;

    while (Map::getInstance()->getTypeOfTile(bullet.x, bullet.y) != 0) {
        bullet.x += bullet.velocity * bullet.dx;
        bullet.y += bullet.velocity * bullet.dy;
        if (getDistance(bullet.x, bullet.y, Player::getInstance()->getX(), Player::getInstance()->getY()) <= 50 * Player::getInstance()->getScale()) {
            return true;
        }
    }
    return false;
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
