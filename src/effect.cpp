#include "effect.h"
#include "header.h"
#include "player.h"

Effect::Effect() {
    deaths.clear();
    explosions.clear();
    frames.resize(20);
    scales.resize(20);
    rates.resize(20);
    times.resize(20);

    for (int i = 0; i < MAX_CREW; ++i) {
        deathsID.push_back(string(listDeath[i]));
        Texture::getInstance()->load(deathsID[i], 1, 1);
    }

    Texture::getInstance()->load(listEffect[0], 6, 5), frames[0] = 30, scales[0] = 1, rates[0] = 120, times[0] = 10;

    Texture::getInstance()->load(listEffect[1], 5, 6), frames[1] = 30, scales[1] = 8, rates[1] = 30, times[1] = 60;
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[1]), SDL_BLENDMODE_ADD);


    Texture::getInstance()->load(listEffect[2], 6, 4), frames[2] = 24, scales[2] = 5, rates[2] = 15, times[2] = 90;
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[2]), SDL_BLENDMODE_ADD);

    Texture::getInstance()->load(listEffect[3], 6, 5), frames[3] = 28, scales[3] = 2, rates[3] = 15, times[3] = 90;
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[3]), SDL_BLENDMODE_ADD);


    /////Texture::getInstance()->load(listEffect[8], 2, 8), frames[8] = 16, scales[8] = 1, rates[8] = 30, times[8] = 10;
//    Texture::getInstance()->load(listEffect[15], 1, 1), frames[15] = 1, scales[15] = 1, rates[15] = 15, times[15] = 100;
//    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[15]), SDL_BLENDMODE_BLEND);
//
//
//    Texture::getInstance()->load(listEffect[16], 1, 13), frames[16] = 13, scales[16] = 0.5, rates[16] = 12, times[16] = 1000;
//    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[16]), SDL_BLENDMODE_ADD);
//
//    Texture::getInstance()->load(listEffect[17], 1, 15), frames[17] = 15, scales[17] = 0.4, rates[17] = 40, times[17] = 1000;
//    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[17]), SDL_BLENDMODE_ADD);



    Texture::getInstance()->load(lights[LIGHT], 1, 1);
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(lights[LIGHT]), SDL_BLENDMODE_ADD);

    Texture::getInstance()->load(lights[FLASHLIGHT], 1, 1);
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(lights[FLASHLIGHT]), SDL_BLENDMODE_ADD);



    Texture::getInstance()->load("assets/images/die/blood.png", 1, 1);

    Texture::getInstance()->load("assets/images/raindrops.png", 1, 1);
    Texture::getInstance()->load("assets/images/snow.png", 1, 1);
    Texture::getInstance()->load("assets/images/sun.png", 1, 1);
    Texture::getInstance()->load("assets/images/hit.png", 1, 1);
}

void Effect::add(int ID, int x, int y) {
    if (ID < 0) return;
    explosions.push_back(Explosion(ID, x, y, times[ID]));
}

void Effect::addDeath(int id, int x, int y, int time, float angle) {
    deaths.push_back(Death(id, x, y, time, angle));
}

void Effect::update() {
    for (auto it = deaths.begin(); it != deaths.end(); ) {
        auto& u = *it;
        u.time--;
        if (u.time <= 0) {
            deaths.erase(it);
        } else {

            ++it;
        }
    }
    for (auto it = explosions.begin(); it != explosions.end(); ) {
        auto& u = *it;
        u.time--;
        if (u.time <= 0) {
            explosions.erase(it);
        } else {

            ++it;
        }
    }
}

void Effect::render(SDL_Rect camera) {
    for (int i = 0; i < explosions.size(); ++i) {
        Explosion& u = explosions[i];
        int currentFrame = (SDL_GetTicks() * rates[u.ID] / 1000) % frames[u.ID] + 1;
        Texture::getInstance()->render(listEffect[u.ID], u.x - camera.x, u.y - camera.y, currentFrame, 0, SDL_FLIP_NONE, scales[u.ID]);
    }
}

void Effect::renderDeaths(SDL_Rect camera) {

    for (int i = 0; i < deaths.size(); ++i) {
        Death& u = deaths[i];
        if (u.time > 0) {
            Texture::getInstance()->render("assets/images/die/bl.png", u.x - camera.x, u.y - camera.y, 1, 0, SDL_FLIP_NONE, u.scale * 1.5);
            Texture::getInstance()->render(deathsID[u.id], u.x - camera.x, u.y - camera.y, 1, 0, SDL_FLIP_NONE, u.scale * 0.8);
        }
    }
}

void Effect::shake(SDL_Rect& camera, int delta) {
    camera.w = randUint(delta) - delta;
    camera.h = randUint(delta) - delta;
}

void Effect::redScreen(int type) {
    static int time = 0;
    static int u = 100;
    if (type == -1) {
        time = 0;
    } else if (type == 1) {
        time = 20;
    } else {
        if (time == 0) return;
        --time;
        SDL_SetTextureAlphaMod(Texture::getInstance()->getTexture(listEffect[15]), u -= 10);
        SDL_RenderCopy(Texture::getInstance()->getRenderer(), Texture::getInstance()->getTexture(listEffect[15]), NULL, NULL);
    }
}

void Effect::light(int type, float angle, SDL_Rect camera) {
    if (type < 0)
        return;

    SDL_Texture* shadow = SDL_CreateTexture(Texture::getInstance()->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetTextureBlendMode(shadow, SDL_BLENDMODE_MOD);


    SDL_SetRenderTarget(Texture::getInstance()->getRenderer(), shadow);

    SDL_SetRenderDrawColor(Texture::getInstance()->getRenderer(), 10, 10, 10, 255);
    SDL_RenderFillRect(Texture::getInstance()->getRenderer(), nullptr);


    if ( Player::getInstance()->isShooting()) {
        Texture::getInstance()->render(lights[LIGHT], Player::getInstance()->getX() - camera.x, Player::getInstance()->getY() - camera.y, 1, angle, SDL_FLIP_NONE, 10);
        Texture::getInstance()->render(lights[type], Player::getInstance()->getX() - camera.x, Player::getInstance()->getY() - camera.y, 1, angle, SDL_FLIP_NONE, 3);
    } else {
        Texture::getInstance()->render(lights[type], Player::getInstance()->getX() - camera.x, Player::getInstance()->getY() - camera.y, 1, angle, SDL_FLIP_NONE, 3);
    }

    SDL_SetRenderTarget(Texture::getInstance()->getRenderer(), nullptr);
    SDL_RenderCopy(Texture::getInstance()->getRenderer(), shadow, NULL, NULL);
    SDL_DestroyTexture(shadow);
}

void Effect::addHit(int x, int y, SDL_Color color) {
    int nB = randInt(7, 10);
    for (int i = 0; i <= nB; ++i) {
        float angle = randInt(-20, 150);
        Particle u;
        u.dx = cos(angle * PI / 180);
        u.dy = sin(angle * PI / 180);
        u.x = x;
        u.y = y;
        u.velocity = randInt(2, 7);
        u.angle = angle;
        u.time = 15;
        u.scale = randF(1, 2);
        u.alpha = randUint(255);
        u.color = color;
        pHit.push_back(u);
    }
}

void Effect::renderHit(SDL_Rect camera) {
    for (auto it = pHit.begin(); it != pHit.end(); ) {
        if (it->time-- <= 0) {
            pHit.erase(it);
        } else {
            it->x += it->velocity * it->dx;
            it->y += it->velocity * it->dy;
            ++it;
        }
    }
    for (auto it = pHit.begin(); it != pHit.end(); ++it) {
        SDL_SetTextureAlphaMod(Texture::getInstance()->getTexture("assets/images/hit.png"), it->alpha);
        SDL_SetTextureColorMod(Texture::getInstance()->getTexture("assets/images/hit.png"), it->color.r, it->color.g, it->color.b);
        Texture::getInstance()->render("assets/images/hit.png", it->x - camera.x, it->y - camera.y, 1, it->angle, SDL_FLIP_NONE, it->scale);
    }
}

void Effect::weather(int type, SDL_Rect camera) {
    switch (type) {
        case NONE:
            break;
        case RAIN:
            while (pRain.size() <= 200) {
                pRain.push_back({randInt(0, SCREEN_WIDTH), randInt(-SCREEN_HEIGHT, 0), randUint(255), randInt(10, 20)});
            }
            for (int i = 0; i < pRain.size(); ++i) {
                auto &u = pRain[i];
                Texture::getInstance()->render("assets/images/raindrops.png", u.x, u.y);
                SDL_SetTextureAlphaMod(Texture::getInstance()->getTexture("assets/images/raindrops.png"), u.w);
                u.y += u.h;
                if (u.y >= SCREEN_HEIGHT) {
                    u.x = randInt(0, SCREEN_WIDTH);
                    u.y = randInt(-SCREEN_HEIGHT, 0);
                }
            }
            break;
        case SUNNY:
            Texture::getInstance()->render("assets/images/sun.png");
            break;
        case SNOW:
            static int timer = 0;
            ++timer;
            if (timer % 10 == 0) {
                int nB = randInt(1, 30);
                for (int i = 0; i <= nB; ++i) {
                    float angle = randInt(50, 150);
                    Particle u;
                    u.dx = cos(angle * PI / 180);
                    u.dy = sin(angle * PI / 180);
                    u.x = randInt(Player::getInstance()->getX() - SCREEN_WIDTH / 2 - 100, Player::getInstance()->getX() + SCREEN_WIDTH / 2 + 100);
                    u.y = camera.y - 3;
                    u.velocity = randInt(2, 7);
                    u.angle = angle;
                    u.time = 500;
                    u.scale = randF(1, 4);
                    u.alpha = randUint(255);
                    pSnow.push_back(u);
                }
            }
            for (auto it = pSnow.begin(); it != pSnow.end(); ) {
                it->time--;
                if (it->y >= camera.y + SCREEN_HEIGHT) {
                    pSnow.erase(it);
                } else {
                    it->x += it->velocity * it->dx;
                    it->y += it->velocity * it->dy;
                    ++it;
                }
            }
            for (auto it = pSnow.begin(); it != pSnow.end(); ++it) {
                SDL_SetTextureAlphaMod(Texture::getInstance()->getTexture("assets/images/snow.png"), it->alpha);
                Texture::getInstance()->render("assets/images/snow.png", it->x - camera.x, it->y - camera.y, 1, it->angle, SDL_FLIP_NONE, it->scale);
            }
            break;
    }

}

void Effect::release() {

}

