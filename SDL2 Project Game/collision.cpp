#include "collision.h"
#include "effect.h"

void checkCollision(Player* player, vector<Enemy*>& enemies, SDL_Rect& camera) {
    bool flag = false;
    for (auto it = player->weapon->bullets.begin(); it != player->weapon->bullets.end(); ++it) {
        if (it->time > 0) {
            for (int j = 0; j < enemies.size(); ++j) {
                auto v = enemies[j];
                if (v->getHP() >= 0) {
                    float distance = getDistance(it->x, it->y, v->getX(), v->getY());
                    if (distance <= 50 * v->getScale()) {
                        it->time = 0;
                        if (it->radius > 0) {
                            flag = true;
                            break;
                        }
                        v->addHP(-it->damage);
                        Effect::getInstance()->addHit(it->x, it->y, it->color);
                        Effect::getInstance()->add(0, it->x, it->y);
                        Effect::getInstance()->add(it->effectID, it->x, it->y);
                        break;
                    }
                }
            }
            if (it->time > 0 && Map::getInstance()->getTypeOfTile(it->x, it->y) == 0) {
                it->time = 0;
                if (it->radius > 0) {
                    flag = true;
                    continue;
                }
                Effect::getInstance()->addHit(it->x, it->y, it->color);
            }
        }
    }

    for (int i = 0; i < enemies.size(); ++i) {
        for (auto it = enemies[i]->weapon->bullets.begin(); it != enemies[i]->weapon->bullets.end(); ++it) {
            if (it->time > 0) {
                float distance = getDistance(it->x, it->y, player->getX(), player->getY());
                if (distance <= 50 * player->getScale()) {
                    player->addHP(-it->damage / 10);
                    it->time = 0;
                    Effect::getInstance()->addHit(it->x, it->y, it->color);
                    Effect::getInstance()->add(0, it->x, it->y);
                    Effect::getInstance()->redScreen(1);
                    break;
                }
            }
            if (it->time > 0 && Map::getInstance()->getTypeOfTile(it->x, it->y) == 0) {
                it->time = 0;
                Effect::getInstance()->addHit(it->x, it->y, it->color);
            }
        }
    }

    if (flag) {
        for (auto it = player->weapon->bullets.begin(); it != player->weapon->bullets.end(); ++it) {
            if (it->time == 0 && it->radius > 0) {
                Effect::getInstance()->add(it->effectID, it->x, it->y);
                Effect::getInstance()->shake(camera, 50);
                Sound::getInstance()->playChunks(8, 3);
                for (int j = 0; j < enemies.size(); ++j) {
                    auto v = enemies[j];
                    if (v->getHP() >= 0) {
                        double distance = getDistance(it->x, it->y, v->getX(), v->getY());
                        if (distance <= it->radius) {
                            v->addHP(-it->damage);
                            Effect::getInstance()->add(0, it->x, it->y);
                        }
                    }
                }
            }
        }
    }
}
