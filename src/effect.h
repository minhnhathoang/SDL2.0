#ifndef __effect__h
#define __effect__h

#include "header.h"
#include "texture.h"
#include "structs.h"

static const char* listEffect[] {
    "assets/images/effect/blood.png",
    "assets/images/effect/1.png",
    "assets/images/effect/2.png",
    "assets/images/effect/3.png",
    "assets/images/effect/4.png",
    "assets/images/effect/5.png",
    "assets/images/effect/6.png",
    "assets/images/effect/7.png",
    "assets/images/effect/8.png",
    "assets/images/effect/9.png",
    "assets/images/effect/10.png",
    "assets/images/effect/11.png",
    "assets/images/effect/12.png",
    "assets/images/effect/13.png",
    "assets/images/effect/14.png",
    "assets/images/effect/15.png",
    "assets/images/effect/16.png",
};

class Effect {

public:

    static Effect* getInstance() {
        static Effect* instance;
        if (instance == nullptr) {
            instance = new Effect();
        }
        return instance;
    }

    Effect();

    void add(int ID, int x, int y);
    void render(SDL_Rect camera);

    void addDeath(int id, int x, int y, int time, float angle);
    void renderDeaths(SDL_Rect camera);

    void shake(SDL_Rect& camera, int delta);
    void redScreen();

    void update();

    void release();


private:
    vector<string> deathsID;

    vector<Death> deaths;
    vector<Explosion> explosions;

    vector<int> frames;
    vector<int> times;
    vector<int> rates;
    vector<float> scales;

};

#endif // __effect__h
