#ifndef __texture__h
#define __texture__h

#include "header.h"

class Texture {

public:
    Texture(SDL_Renderer* renderer, const char* fileName);
    Texture(SDL_Renderer* renderer, const char* fileName, int _nFrames);
    ~Texture();

    void render(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, const SDL_Rect& src, const SDL_Rect& dst);
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect src);
    void render(SDL_Renderer* renderer, int x, int y, int w, int h);

    SDL_Texture* getTexture();

private:
    SDL_Texture* texture;

    int nFrames;
    vector<SDL_Rect> frames;
};

#endif // __texture__h
