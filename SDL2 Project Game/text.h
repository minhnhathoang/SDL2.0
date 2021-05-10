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

    void render(int sizeFont, string mes, int x, int y, int align, SDL_Color _color);
    void render(int sizeFont, string mes, int x, int y, int align);

    void release();

    void setColor(int colorID);

private:

    SDL_Color color;
    SDL_Renderer* renderer;
};

#endif // __text__h
