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

void Texture::render(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst) {
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Texture::renderEx(SDL_Renderer* renderer, int x, int y, int w, int h, double angle) {
    SDL_Rect dst;

    dst.x = x - w / 2;
    dst.y = y - h / 2;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopyEx(renderer, texture, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void Texture::renderEx(SDL_Renderer* renderer, int x, int y, SDL_Rect src, double angle, SDL_Point point, SDL_RendererFlip flip) {
    SDL_Rect dst;

    dst.x = x - src.w / 2;
    dst.y = y - src.h / 2;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &point, flip);
}

void Texture::renderEx(SDL_Renderer* renderer, int x, int y, SDL_Rect src, double angle, SDL_Point point, SDL_RendererFlip flip, double scale) {
    SDL_Rect dst;

    dst.w = scale * src.w;
    dst.h = scale * src.h;

    dst.x = x - dst.w / 2;
    dst.y = y - dst.h / 2;


    SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, NULL, flip);
}

SDL_Rect Texture::getFrame(int id) {
    return frames[id];
}
