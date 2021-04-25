#include "effect.h"
#include "header.h"

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

    Texture::getInstance()->load(listEffect[0], 1, 5), frames[0] = 5, scales[0] = 1, rates[0] = 30, times[0] = 10;
    Texture::getInstance()->load(listEffect[1], 3, 3), frames[1] = 9, scales[1] = 1, rates[1] = 15, times[1] = 50;
    Texture::getInstance()->load(listEffect[2], 6, 5), frames[2] = 30, scales[2] = 1, rates[2] = 120, times[2] = 10;
    Texture::getInstance()->load(listEffect[3], 6, 6), frames[3] = 36, scales[3] = 6, rates[3] = 30, times[3] = 60;
    Texture::getInstance()->load(listEffect[4], 5, 6), frames[4] = 30, scales[4] = 8, rates[4] = 30, times[4] = 60;
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[4]), SDL_BLENDMODE_ADD);
    Texture::getInstance()->load(listEffect[5], 1, 8), frames[5] = 8, scales[5] = 1, rates[5] = 30, times[5] = 5;
    Texture::getInstance()->load(listEffect[6], 1, 8), frames[6] = 8, scales[6] = 0.5, rates[6] = 60, times[6] = 5;
    Texture::getInstance()->load(listEffect[7], 1, 8), frames[7] = 8, scales[7] = 1, rates[7] = 30, times[7] = 5;
    Texture::getInstance()->load(listEffect[8], 2, 8), frames[8] = 16, scales[8] = 1, rates[8] = 30, times[8] = 10;
    Texture::getInstance()->load(listEffect[9], 2, 4), frames[9] = 8, scales[9] = 0.7, rates[9] = 60, times[9] = 5;
    Texture::getInstance()->load(listEffect[10], 1, 8), frames[10] = 8, scales[10] = 1, rates[10] = 30, times[10] = 10;
    //Texture::getInstance()->load(listEffect[11], 4, 4), frames[11] = 8, scales[11] = 1, rates[11] = 30, times[11] = 10;
    Texture::getInstance()->load(listEffect[12], 7, 4), frames[12] = 27, scales[12] = 5, rates[12] = 15, times[12] = 90;
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[12]), SDL_BLENDMODE_ADD);

    Texture::getInstance()->load(listEffect[13], 6, 5), frames[13] = 28, scales[13] = 2, rates[13] = 15, times[13] = 90;
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture(listEffect[13]), SDL_BLENDMODE_ADD);
    //SDL_SetTextureColorMod(Texture::getInstance()->getTexture(listEffect[13]), 200, 0, 200);
    Texture::getInstance()->load(listEffect[14], 1, 8), frames[14] = 8, scales[14] = 1, rates[14] = 15, times[14] = 20;


}

void Effect::add(int ID, int x, int y) {
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
        Texture::getInstance()->render(string(listEffect[u.ID]), u.x - camera.x, u.y - camera.y, currentFrame, 0, SDL_FLIP_NONE, scales[u.ID]);
    }
}

void Effect::renderDeaths(SDL_Rect camera) {
    for (int i = 0; i < deaths.size(); ++i) {
        Death& u = deaths[i];
        if (u.time > 0) {
            Texture::getInstance()->render(deathsID[u.id], u.x - camera.x, u.y - camera.y);
        }

    }
}

void Effect::shake(SDL_Rect& camera, int delta) {
    camera.w = randUint(delta) - delta;
    camera.h = randUint(delta) - delta;
}

void Effect::redScreen() {
    static int timer = 0;
    SDL_SetRenderDrawColor(Texture::getInstance()->getRenderer(), 200, 0, 0, 200);
    if (++timer <= 10) {
        SDL_RenderFillRect(Texture::getInstance()->getRenderer(), NULL);
    }
    if (timer == 20) timer = 0;
}

void Effect::release() {

}

