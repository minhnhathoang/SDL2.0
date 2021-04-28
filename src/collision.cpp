#include "collision.h"
#include "effect.h"

void checkCollision(Player* player, vector<Enemy*>& enemies) {
    for (auto it = player->weapon->bullets.begin(); it != player->weapon->bullets.end(); ++it) {
        if (it->time > 0) {
            for (int j = 0; j < enemies.size(); ++j) {
                auto v = enemies[j];
                if (v->getHP() >= 0) {
                    if (getDistance(it->x, it->y, v->getX(), v->getY()) <= 50) {
                        //Effect::getInstance()->add(0, v->getX(), v->getY());
                        Effect::getInstance()->add(2, it->x, it->y);
                        v->addHP(-20);
                        it->time = 0;
                        Effect::getInstance()->add(it->effectID, it->x, it->y);
                        break;
                    }
                }
            }
            if (it->time > 0 && Map::getInstance()->getTypeOfTile(it->x, it->y) == 0) {
                it->time = 0;
                Effect::getInstance()->add(it->effectID, it->x, it->y);
            }
        }
    }
    for (int i = 0; i < enemies.size(); ++i) {
        for (auto it = enemies[i]->weapon->bullets.begin(); it != enemies[i]->weapon->bullets.end(); ++it) {
            if (it->time > 0) {
                if (getDistance(it->x, it->y, player->getX(), player->getY()) <= 50) {
                    player->addHP(-5);
                    it->time = 0;
                    Effect::getInstance()->add(it->effectID, it->x, it->y);
                    Effect::getInstance()->redScreen(0);
                    break;
                }
            }
            if (it->time > 0 && Map::getInstance()->getTypeOfTile(it->x, it->y) == 0) {
                it->time = 0;
                Effect::getInstance()->add(it->effectID, it->x, it->y);
            }
        }
    }
}
