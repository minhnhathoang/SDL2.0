#include "text.h"
#include "game.h"

Text::Text() {
    renderer = Game::getInstance()->getRenderer();
    mapFont.clear();
    color = listColor[0];
}

void Text::render(int sizeFont, string mes, int x, int y, int align, SDL_Color _color) {

    if (mapFont.find(sizeFont) == mapFont.end()) {
        cerr << "Add Font " << sizeFont << '\n';
        mapFont[sizeFont] = TTF_OpenFont("font/purista.ttf", sizeFont);
    }

    auto it = mapFont[sizeFont];

    SDL_Surface* mesSurface = TTF_RenderText_Blended(it, mes.c_str(), _color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, mesSurface);

    int w, h;

    TTF_SizeText(it, mes.c_str(), &w, &h);

    switch (align) {
        case LEFT:
            break;
        case CENTER:
            x -= w / 2;
            break;
        case RIGHT:
            x -= w;
            break;
    }

    SDL_Rect dst =  { x, y, w, h };

    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(mesSurface);
    SDL_DestroyTexture(texture);
}

void Text::render(int sizeFont, string mes, int x, int y, int align) {

    if (mapFont.find(sizeFont) == mapFont.end()) {
        cerr << "Add Font " << sizeFont << '\n';
        mapFont[sizeFont] = TTF_OpenFont("font/purista.ttf", sizeFont);
    }

    auto it = mapFont[sizeFont];

    SDL_Surface* mesSurface = TTF_RenderText_Blended(it, mes.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, mesSurface);

    int w, h;

    TTF_SizeText(it, mes.c_str(), &w, &h);

    switch (align) {
        case LEFT:
            break;
        case CENTER:
            x -= w / 2;
            break;
        case RIGHT:
            x -= w;
            break;
    }

    SDL_Rect dst =  { x, y, w, h };

    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(mesSurface);
    SDL_DestroyTexture(texture);
}

void Text::setColor(int colorID) {
    color = listColor[colorID];
}

void Text::release() {

}
