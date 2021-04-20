#include "text.h"

Text::Text() {
    //font = TTF_OpenFont("font/megatron.otf", 40);
    font = TTF_OpenFont("font/purista.ttf", 40);
    //font = TTF_OpenFont("font/DejaVuSans.ttf", 70);
    //TTF_SetFontOutline(font, 1);
    //TTF_SetFontHinting(font, TTF_HINTING_MONO);

}

void Text::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Text::render(string mes, int x, int y, bool neg, double scale) {
    //SDL_Color color = {0, 255, 0};
    //SDL_Color color = {254, 0, 4};
    //SDL_Color color = {13, 1, 255, 255};
    SDL_Color color = {254, 136, 4};

    //SDL_Color color = listColor[4];

    SDL_Surface* mesSurface = TTF_RenderText_Blended(font, mes.c_str(), color);
    //SDL_Surface* mesSurface = TTF_RenderText_Shaded(font, mes.c_str(), color, color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, mesSurface);

    int w, h;

    TTF_SizeText(font, mes.c_str(), &w, &h);

    w *= scale;
    h *= scale;

    if (neg) x -= w;

    SDL_Rect dst =  { x, y, w, h };

    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(mesSurface);
    SDL_DestroyTexture(texture);
}
