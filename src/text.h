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

    void render(int sizeFont, string mes, int x, int y, bool alignRight = 0);

    void release();

private:

    SDL_Renderer* renderer;
};

#endif // __text__h
