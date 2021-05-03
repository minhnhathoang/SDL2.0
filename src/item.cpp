#include "item.h"

Item::Item() {
    boxBulletID = "assets/images/item/boxbullet.png";
    medkitID = "assets/images/item/medkit.png";
    flashlightID = "assets/images/item/flashlight.png";
    //umbrella = "assets/images/item/umbrella.png";

    Texture::getInstance()->load(medkitID, 1, 1);
    Texture::getInstance()->load(boxBulletID, 1, 1);
    Texture::getInstance()->load(flashlightID, 1, 1);
}

void Item::update(bool keyboard[]) {
    for (auto it = listBoxBullet.begin(); it != listBoxBullet.end(); ) {
        if (getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), it->x, it->y) <= 80 && keyboard[SDL_SCANCODE_Z]) {
            listBoxBullet.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = listMedkit.begin(); it != listMedkit.end(); ) {
        if (getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), it->x, it->y) <= 80 && keyboard[SDL_SCANCODE_Z]) {
            listMedkit.erase(it);
            Player::getInstance()->addHP(20);
        } else {
            ++it;
        }
    }

    for (auto it = listFlashlight.begin(); it != listFlashlight.end(); ) {
        if (++it->time) {
            if (it->time % 3 <= 0) {
                it->angle += 10;
            }
            if (it->time >= 1000) {
                it->time = 0;
            }
        }
        if (getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), it->x, it->y) <= 80 && keyboard[SDL_SCANCODE_Z]) {
            listFlashlight.erase(it);
        } else {
            ++it;
        }
    }

    while (listMedkit.size() <= 1) {
        SDL_Point tmp;
        randomPosition(tmp.x, tmp.y);
        listMedkit.push_back(tmp);
    }

    while (listFlashlight.size() <= 1) {
        SDL_Point tmp;
        randomPosition(tmp.x, tmp.y);
        listFlashlight.push_back({tmp.x, tmp.y, randUint(360), 0});
    }
}

void Item::render(SDL_Rect camera) {
    for (auto it = listBoxBullet.begin(); it != listBoxBullet.end(); ++it) {
        //Texture::getInstance()->render(boxBulletID, it->x - camera.x, it->y - camera.y);
    }

    for (auto it = listMedkit.begin(); it != listMedkit.end(); ++it) {
        Texture::getInstance()->render(medkitID, it->x - camera.x, it->y - camera.y);
    }

    for (auto it = listFlashlight.begin(); it != listFlashlight.end(); ++it) {
        Texture::getInstance()->render(flashlightID, it->x - camera.x, it->y - camera.y, 1, it->angle, SDL_FLIP_NONE, 1);
    }
}

void Item::randomPosition(int &x, int &y, int distance) {
    while (true) {
        x = randUint(4000);
        y = randUint(3000);
        if (Map::getInstance()->getTypeOfTile(x, y) == 1 &&
                getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), x, y) > distance)
            break;
    }
}
