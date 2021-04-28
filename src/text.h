#ifndef __text__h
#define __text__h

#include "header.h"
#include "texture.h"

class Text {

    map<int, TTF_Font*> mapFont;

public:

    static Text* getInstance() {
        static Text* instance;
        if (instance == nullptr) {
            instance = new Text();
        }
        return instance;
    }

    Text();

    void setRenderer(SDL_Renderer* _renderer);

    void render(int sizeFont, string mes, int x, int y, bool neg = 0, double scale = 1);

    void release();

private:

    TTF_Font* font;
    TTF_Font* font30;
    SDL_Renderer* renderer;
};

#endif // __text__h
