#include "texture.h"

Texture::Texture(SDL_Renderer* renderer, const char* fileName) {
    texture = IMG_LoadTexture(renderer, fileName);
    if (texture == NULL) {
        logSDLError("Load Texture");
    }
}

Texture::Texture(SDL_Renderer* renderer, const char* fileName, int _nFrames) {
    texture = IMG_LoadTexture(renderer, fileName);
    if (texture == NULL) {
        logSDLError("Load Texture");
    }

    nFrames = _nFrames;
    frames.resize(nFrames);

    int width, height;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    for (int i = 0; i < nFrames; ++i) {
        frames[i].x = i * width / nFrames;
        frames[i].y = 0;
        frames[i].w = width / nFrames;
        frames[i].h = height;
    }
}

SDL_Texture* Texture::getTexture() {
    return texture;
}

void Texture::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect src) {
    SDL_Rect dst;
    dst.x = x - src.w / 2;
    dst.y = y - src.h / 2;
    dst.w = src.w;
    dst.h = src.h;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& src, const SDL_Rect& dst) {
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
