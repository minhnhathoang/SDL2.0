#include "header.h"
#include "tilemap.h"
#include "game.h"

const int dr[] = { 0, -1, 0, 1, 1, 1, -1, -1 };
const int dc[] = { 1, 0, -1, 0, 1, -1, 1, -1 };

Map::Map() {

    mapID = "assets/images/map.png";

    Texture::getInstance()->load(mapID, 188, 250);

    freopen("map.txt", "r", stdin);

    nWidth = 250;
    nHeight = 188;

    tiles.resize(nWidth, vector<Tile>(nHeight));

    int cnt = 0;

    for (int j = 0; j < nHeight; ++j) {
        for (int i = 0; i < nWidth; ++i) {
            int typeTile;
            cin >> typeTile;
            tiles[i][j] = { i * TILE_WIDTH, j * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, typeTile, -1 };
            if (typeTile == 1) {
                tiles[i][j].id = ++cnt;
            }
        }
    }

    adj.resize(cnt + 1, vector<int>());

    for (int i = 0; i < nWidth; ++i) {
        for (int j = 0; j < nHeight; ++j) {
            if (tiles[i][j].id <= 0) continue;

            for (int k = 0; k < 2; ++k) {
                int u = i + dr[k];
                int v = j + dc[k];
                if (u >= 0 && v >= 0 && u < nWidth && v < nHeight) {
                    if (tiles[u][v].id > 0) {
                        addEdge(tiles[u][v].id, tiles[i][j].id);
                    }
                }
            }
        }
    }
}

void Map::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Map::render(SDL_Rect camera) {
    for (int i = 0; i < nWidth; ++i) {
        for (int j = 0; j < nHeight; ++j) {
            SDL_Rect src = { tiles[i][j].x, tiles[i][j].y, tiles[i][j].w, tiles[i][j].h };
            SDL_Rect dst = { i * 25 - camera.x, j * 25 - camera.y, 25, 25 };

            if (dst.x >= -30 && dst.x <= SCREEN_WIDTH + 30 && dst.y >= -30 && dst.y <= SCREEN_HEIGHT + 30) {
                Texture::getInstance()->render(mapID, src, dst);
            }

        }
    }
}

int Map::getTypeOfTile(int x, int y) {
    int u = x / 25;
    int v = y / 25;
    if (u < 0 || v < 0 || u >= nWidth || v >= nHeight) {
        return 0;
    }
    return tiles[u][v].type;
}

int Map::getTile(int x, int y) {
    int u = x / 25;
    int v = y / 25;
    if (u < 0 || v < 0 || u >= nWidth || v >= nHeight) {
        return 0;
    }
    return tiles[u][v].id;
}
