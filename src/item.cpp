#include "item.h"

Item::Item() {
    boxBulletID = "assets/images/item/boxbullet.png";
    medkitID = "assets/images/item/medkit.png";
    flashlightID = "assets/images/item/flashlight.png";

    Texture::getInstance()->load(medkitID, 1, 1);
    Texture::getInstance()->load(boxBulletID, 1, 1);
    Texture::getInstance()->load(flashlightID, 1, 1);

     Texture::getInstance()->render(medkitID);
}

void Item::update(bool keyboard[]) {
    for (auto it = listBoxBullet.begin(); it != listBoxBullet.end(); ) {
        if (getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), it->x, it->y) <= 60) {
            listBoxBullet.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = listMedkit.begin(); it != listMedkit.end(); ) {
        if (getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), it->x, it->y) <= 60) {
            listMedkit.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = listFlashlight.begin(); it != listFlashlight.end(); ) {
        if (getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), it->x, it->y) <= 60) {
            listFlashlight.erase(it);
        } else {
            ++it;
        }
    }
    while (listMedkit.size() <= 10) {
        SDL_Point tmp;
        randomPosition(tmp.x, tmp.y);
        listMedkit.push_back(tmp);
        listFlashlight.push_back(tmp);
        listBoxBullet.push_back(tmp);
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
        Texture::getInstance()->render(flashlightID, it->x - camera.x, it->y - camera.y, 1, randInt(0, 360), SDL_FLIP_NONE, 1);
    }
}

void Item::randomPosition(int &x, int &y) {
    while (true) {
        x = randUint(4000);
        y = randUint(3000);
        if (Map::getInstance()->getTypeOfTile(x, y) == 1) break;
    }
}
