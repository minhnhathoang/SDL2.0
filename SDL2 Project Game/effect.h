#ifndef __effect__h
#define __effect__h

#include "header.h"
#include "texture.h"
#include "structs.h"

static const char* listEffect[] {
    "assets/images/effect/0.png",
    "assets/images/effect/1.png",
    "assets/images/effect/2.png",
    "assets/images/effect/3.png",
    "assets/images/fire.png",
    "assets/images/fire1.png",
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
    void update();
    void render(SDL_Rect camera);

    void addDeath(int id, int x, int y, int time, float angle);
    void renderDeaths(SDL_Rect camera);

    void shake(SDL_Rect& camera, int _time = 0);
    void redScreen(int type);

    void alert(SDL_Color color);

    void light(int type, float angle, SDL_Rect camera);

    void weather(int type, SDL_Rect camera);

    void addHit(int x, int y, SDL_Color color);
    void renderHit(SDL_Rect camera);

    void release();

private:

    vector<Death> deaths;
    vector<string> deathsID;

    vector<int> frames;
    vector<int> times;
    vector<int> rates;
    vector<float> scales;
    vector<Explosion> explosions;

    vector<SDL_Rect> pRain;
    vector<Particle> pSnow;
    vector<Particle> pHit;

};

#endif // __effect__h
