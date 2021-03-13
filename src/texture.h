#ifndef __texture__h
#define __texture__h

#include "header.h"

class Texture {

public:
    Texture(SDL_Renderer* renderer, const char* fileName);
    Texture(SDL_Renderer* renderer, const char* fileName, int _nFrames);
    ~Texture();

    void render(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst);
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect src);
    void render(SDL_Renderer* renderer, int x, int y, int w, int h);

    void renderEx(SDL_Renderer* renderer, int x, int y, int w, int h, double angle);
    void renderEx(SDL_Renderer* renderer, int x, int y, SDL_Rect src, double angle, SDL_Point point, SDL_RendererFlip flip);
    void renderEx(SDL_Renderer* renderer, int x, int y, SDL_Rect src, double angle, SDL_Point point, SDL_RendererFlip flip, double scale);

    SDL_Texture* getTexture();

    SDL_Rect getFrame(int id);


    int nFrames;

private:
    SDL_Texture* texture;

    vector<SDL_Rect> frames;
};

#endif // __texture__h
