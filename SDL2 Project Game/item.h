#ifndef __item__h
#define __item__h

#include "header.h"
#include "player.h"
#include "tilemap.h"
#include "texture.h"
#include "enemy.h"

class Item {

    struct Data {
        int x, y;
        int time;
        float angle;
        float scale;
        int type;

        bool flip;
    };

public:

    static Item* getInstance() {
        static Item* instance;
        if (instance == nullptr) {
            instance = new Item();
        }
        return instance;
    }

    Item();

    void init();

    void update(bool keyboard[]);
    void render(SDL_Rect camera, Mouse mouse);
    void renderTab(Mouse mouse);

    bool randomPosition(int &x, int &y, int distance = -1);


    void radar(Player* player, vector<Enemy*>& enemies, int x, int y, float radius, float scale);

private:
    int MAX_ITEM;

    vector<string> itemID;
    vector<string> glowID;
    vector<vector<Data>> listItem;
    vector<int> itemsOfPlayer;
};

#endif // __item__h
