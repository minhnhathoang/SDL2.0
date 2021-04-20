#ifndef __tilemap__h
#define __tilemap__h

#include "header.h"
#include "texture.h"

class Map {

    struct Tile {
        int x, y, w, h;
        int type;
        int id;
    };

public:

    static Map* getInstance() {
        static Map* instance;
        if (instance == nullptr) {
            instance = new Map();
        }
        return instance;
    }

    Map();

    void render(SDL_Rect camera);

    void addEdge(int u, int v);


    int getTypeOfTile(int x, int y);
    int getTile(int x, int y);


    vector<vector<Tile>> tiles;

    vector<vector<int>> adj;

    string mapID;
    int nWidth, nHeight;
private:

};


#endif // __tilemap__h
