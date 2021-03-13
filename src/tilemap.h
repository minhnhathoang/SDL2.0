#ifndef __tilemap__h
#define __tilemap__h

#include "header.h"
#include "texture.h"

class Map {

    struct Tile {
        int x, y, w, h;
        int type;
    };

public:

    Map(SDL_Renderer* renderer);
    ~Map();

    void render(SDL_Renderer* renderer, int x, int y);


    int getTypeOfTile(int x, int y);

private:

    vector<vector<Tile>> tiles;

    Texture* tMap;
    int nWidth, nHeight;
};


#endif // __tilemap__h
