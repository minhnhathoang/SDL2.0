#include "text.h"
#include "game.h"

Text::Text() {
    renderer = Game::getInstance()->getRenderer();
    mapFont.clear();
}

void Text::render(int sizeFont, string mes, int x, int y, bool alignRight) {

    if (mapFont.find(sizeFont) == mapFont.end()) {
        cerr << "Add Font " << sizeFont << '\n';
        mapFont[sizeFont] = TTF_OpenFont("font/purista.ttf", sizeFont);
    }

    //SDL_Color color = {0, 255, 0};
    //SDL_Color color = {254, 0, 4};
    //SDL_Color color = {13, 1, 255, 255};
    //SDL_Color color = {254, 136, 4};
    //SDL_Color color = {200, 0, 200};

    SDL_Color color = listColor[3];

    SDL_Surface* mesSurface = TTF_RenderText_Blended(mapFont[sizeFont], mes.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, mesSurface);

    int w, h;

    TTF_SizeText(mapFont[sizeFont], mes.c_str(), &w, &h);

    if (alignRight)
        x -= w;

    SDL_Rect dst =  { x, y, w, h };

    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(mesSurface);
    SDL_DestroyTexture(texture);
}

void Text::release() {

}
