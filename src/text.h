#ifndef __text__h
#define __text__h

#include "header.h"
#include "texture.h"

class Text {

public:
    Text();
    ~Text();

    void render();

private:
    TTF_Font* font;

    Texture* text = nullptr;
};

#endif // __text__h
