#ifndef __texture__h
#define __texture__h

#include "header.h"

class Texture {

    struct textureData {
        SDL_Texture* texture;
        int nFrames;
        int width, height;
        int row, col;
    };

    map<string, textureData> textureMap;

    Texture();

public:

    static Texture* getInstance() {
        static Texture* instance;
        if (instance == nullptr) {
            instance = new Texture();
        }
        return instance;
    }

    void setRenderer(SDL_Renderer* _renderer);
    SDL_Texture* getTexture(string ID);

    void load(string ID, int row, int col);

    void render(string ID, int x, int y, int currentFrames, float angle, SDL_RendererFlip flip = SDL_FLIP_NONE, float scale = 1.0f, SDL_Point* point = nullptr);

    void render(string ID, SDL_Rect src, SDL_Rect dst);

    void render(string ID, int x, int y);

    void render(string ID);

    void destroy(string ID);

    SDL_Renderer* getRenderer();

    void release();

private:

    SDL_Renderer* renderer;

};

#endif // __texture__h
