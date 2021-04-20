#include "item.h"

Item::Item() {
    boxBulletID = "assets/images/item/boxbullet.png";
    medkitID = "assets/images/item/medkit.png";
    flashlightID = "assets/images/item/flashlight.png";
}

void Item::update(Player* player, bool keyboard[]) {
    for (auto it = listBoxBullet.begin(); it != listBoxBullet.end(); ) {
        if (getDistance(player->getX(), player->getY(), it->x, it->y) <= 60) {
            listBoxBullet.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = listFlashlight.begin(); it != listFlashlight.end(); ) {

    }

    while (listBoxBullet.size() <= 10) {
        SDL_Point tmp;
        randomPosition(tmp.x, tmp.y);
        listBoxBullet.push_back(tmp);
    }
}

void Item::render(SDL_Rect camera) {
    for (auto it = listBoxBullet.begin(); it != listBoxBullet.end(); ++it) {
        Texture::getInstance()->render(boxBulletID, it->x - camera.x, it->y - camera.y);
    }
}

void Item::randomPosition(int &x, int &y) {
    while (true) {
        x = randUint(4000);
        y = randUint(3000);
        if (Map::getInstance()->getTypeOfTile(x, y) == 1) break;
    }
}
