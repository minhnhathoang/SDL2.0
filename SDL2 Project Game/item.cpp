#include "item.h"
#include "text.h"
#include "game.h"

Item::Item() {
    MAX_ITEM = 7;

    itemID.clear();
    listItem.clear();

    itemID.resize(MAX_ITEM);
    glowID.resize(MAX_ITEM);
    listItem.resize(MAX_ITEM);

    itemID[0] = "assets/images/item/0.png";
    itemID[1] = "assets/images/item/1.png";
    itemID[2] = "assets/images/item/2.png";
    itemID[3] = "assets/images/item/3.png";
    itemID[4] = "assets/images/item/4.png";
    itemID[5] = "assets/images/item/5.png";
    itemID[6] = "assets/images/item/6.png";

    glowID[0] = "assets/images/item/gl0.png";
    glowID[1] = "assets/images/item/gl1.png";
    glowID[2] = "assets/images/item/gl2.png";
    glowID[3] = "assets/images/item/gl3.png";
    glowID[4] = "assets/images/item/gl4.png";
    glowID[5] = "assets/images/item/gl5.png";
    glowID[6] = "assets/images/item/gl6.png";

    for (int i = 0; i < MAX_ITEM; ++i) {
        Texture::getInstance()->load(itemID[i], 1, 1);
        Texture::getInstance()->load(glowID[i], 1, 1);
    }

    Texture::getInstance()->load("assets/images/radar.png", 1, 1);
}

void Item::init() {
    itemsOfPlayer.resize(MAX_ITEM, 0);
    for (int i = 0; i < listItem.size(); ++i) {
        listItem[i].clear();
    }
}

void Item::update(bool keyboard[]) {
    for (int i = 0; i < listItem.size(); ++i) {

        while (listItem[i].size() < 1) {
            Data temp;
            if (randomPosition(temp.x, temp.y, randInt(3000, 4500))) {
                temp.flip = randUint(1);
                listItem[i].push_back(temp);
            }
        }

        for (auto it = listItem[i].begin(); it != listItem[i].end(); ) {
            int distance = getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), it->x, it->y);
            if (distance <= 70 && keyboard[SDL_SCANCODE_Z]) {
                Sound::getInstance()->playChunks(13, 1);
                ++itemsOfPlayer[i];
                listItem[i].erase(it);
            } else {
                ++it;
            }
        }
    }
}

void Item::render(SDL_Rect camera, Mouse mouse) {
    for (int i = 0; i < listItem.size(); ++i) {
        for (auto u : listItem[i]) {
            if (!onScreen(u.x, u.y, camera)) continue;
            SDL_RendererFlip flip = u.flip == 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
            if (getDistance(u.x - camera.x, u.y - camera.y, mouse.x, mouse.y) < 50) {
                Texture::getInstance()->setColor(glowID[i], listColor[Player::getInstance()->getID()]);

                Texture::getInstance()->render(glowID[i], u.x - camera.x, u.y - camera.y, 1, 0, flip, 0.5);
            }
            Texture::getInstance()->render(itemID[i], u.x - camera.x, u.y - camera.y, 1, 0, flip, 0.5);
        }
    }
}

void Item::renderTab(Mouse mouse) {
    int x = 770, y = 650;
    for (int i = 0; i < MAX_ITEM; ++i) {
        if (mouse.x >= x - 40 && mouse.x <= x + 40 && mouse.y >= y - 40 && mouse.y <= y + 40) {
            Texture::getInstance()->setColor(glowID[i], listColor[Player::getInstance()->getID()]);
            Texture::getInstance()->load(glowID[i], 1, 1);
            Texture::getInstance()->render(glowID[i], x, y, 0.3);
            if (mouse.R && itemsOfPlayer[i] > 0) {

                int u = Player::getInstance()->getGunID();

                switch (i) {
                    case 0:
                        --itemsOfPlayer[i];
                        Player::getInstance()->addHP(30);
                        break;
                    case 1:
                        --itemsOfPlayer[i];
                        Player::getInstance()->addOxy(3500);
                        break;
                    case 2:
                        if (u == 2 || u == 4 || u == 6) {
                            --itemsOfPlayer[i];
                            Player::getInstance()->weapon->addAmmo();
                        }
                        break;
                    case 3:
                        if (u == 0 || u == 1 || u == 7) {
                            --itemsOfPlayer[i];
                            Player::getInstance()->weapon->addAmmo();
                        }
                        break;
                    case 4:
                        if (u == 5 || u == 1 || u == 0) {
                            --itemsOfPlayer[i];
                            Player::getInstance()->weapon->addAmmo();
                        }
                        break;
                    case 5:
                        if (u == 3 || u == 8) {
                            --itemsOfPlayer[i];
                            Player::getInstance()->weapon->addAmmo();
                        }
                        break;
                    case 6:
                        if (u == 10 || u == 11) {
                            --itemsOfPlayer[i];
                            Player::getInstance()->weapon->addAmmo();
                        }
                        break;
                }

            }
            Text::getInstance()->render(20, "x" + to_string(itemsOfPlayer[i]), x + 30, y, LEFT);
        }
        Texture::getInstance()->render(itemID[i], x, y, 0.3);
        x += 80;
    }

    x = 1320, y = 100;
    for (int i = 0; i <= 11; ++i) {
        if (Player::getInstance()->lockGuns[i] == false) continue;
        Texture::getInstance()->render(listGun[i], x, y, 1, 0, SDL_FLIP_HORIZONTAL, Player::getInstance()->weapon->getGun(i).scaleFrame * 0.7);
        y += 45;
    }
}

bool Item::randomPosition(int &x, int &y, int distance) {
    int cnt = 0;
    while (cnt < 10) {
        x = randUint(6100);
        y = randUint(4460);
        if (Map::getInstance()->getTypeOfTile(x, y) == 1 &&
                getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), x, y) > distance)
            return true;
        ++cnt;
    }
    return false;
}

void Item::radar(Player* player, vector<Enemy*>& enemies, int x, int y, float radius, float scale) {
    static float angle = 0;
    angle += 3;

    Texture::getInstance()->setColor("assets/images/radar.png", listColor[player->getID()]);
    Texture::getInstance()->render("assets/images/radar.png", x, y, 1, angle, SDL_FLIP_NONE);

    Texture::getInstance()->setColor("assets/images/particle.png", listColor[player->getID()]);
    Texture::getInstance()->setAlpha("assets/images/particle.png");

    Texture::getInstance()->render("assets/images/particle.png", x, y, 2.5);

    for (auto it : enemies) {
        double distance = getDistance(player->getX(), player->getY(), it->getX(), it->getY());
        if (distance > radius) continue;
        SDL_Point temp = { it->getX() - player->getX(), it->getY() - player->getY() };
        Texture::getInstance()->setColor("assets/images/particle.png", listColor[it->getID()]);
        Texture::getInstance()->render("assets/images/particle.png", x + temp.x / scale, y + temp.y / scale, 2.5);
    }
    Texture::getInstance()->setColor("assets/images/particle.png");
}
