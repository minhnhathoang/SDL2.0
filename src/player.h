#ifndef __player__h
#define __player__h

#include "texture.h"
#include "tilemap.h"
#include "weapon.h"
#include "sound.h"
#include "effect.h"

class Player {

public:

    static Player* getInstance() {
        static Player* instance;
        if (instance == nullptr) {
            instance = new Player();
        }
        return instance;
    }

    Player();
    ~Player();

    void init();
    void update(SDL_Rect& camera, bool key[], Mouse mouse);
    void render(SDL_Rect& camera);

    int getX();
    int getY();
    float getScale();
    int getHP();
    int getOxy();
    int getCoin();
    int getELight();
    void addHP(int delta);
    void addOxy(int delta);

    string getName();
    void setName(string _name);

    string enterName(int minSize, int maxSize, bool show, int fontSize, int x, int y);

    bool isShooting();

    string getID();

    int getGunID();

    pair<int, int> getAmmunition();

    Weapon* weapon;
    int energyLight;

private:
    int ID;
    string name;
    int gunID;

    int nFrames;

    int x, y;
    int dx, dy;
    int moveSpeed;

    int hp, oxy;

    int rate;

    bool isMove = 0;

    SDL_RendererFlip flip;


    float scale = 1;
};

#endif // __player__h
