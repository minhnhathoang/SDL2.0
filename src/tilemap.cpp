#include "header.h"
#include "tilemap.h"

Map::Map(SDL_Renderer* renderer) {
    tMap = new Texture(renderer, "assets/images/map.png");

    freopen("assets/map.txt", "r", stdin);

    nWidth = 122;
    nHeight = 61;

    tiles.resize(nWidth, vector<Tile>(nHeight));

    for (int j = 0; j < nHeight; ++j) {
        for (int i = 0; i < nWidth; ++i) {
            int typeTile;
            cin >> typeTile;
            tiles[i][j] = { i * TILE_WIDTH, j * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, typeTile };
        }
    }

}

Map::~Map() {

}

void Map::render(SDL_Renderer* renderer, int x, int y) {
    for (int i = 0; i < nWidth; ++i) {
        for (int j = 0; j < nHeight; ++j) {

            SDL_Rect src = { tiles[i][j].x, tiles[i][j].y, tiles[i][j].w, tiles[i][j].h };
            SDL_Rect dst = { i * 40 - x, j * 40 - y, 40, 40 };

            tMap->render(renderer, src, dst);
        }
    }
}
