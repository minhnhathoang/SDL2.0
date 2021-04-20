#ifndef __text__h
#define __text__h

#include "header.h"
#include "texture.h"

class Text {

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

    void render(string mes, int x, int y, bool neg = 0, double scale = 1);

private:

    TTF_Font* font;
    SDL_Renderer* renderer;
};

#endif // __text__h
