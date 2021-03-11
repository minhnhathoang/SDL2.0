#ifndef __text__h
#define __text__h

#include "header.h"

class Text {

public:
    Text();
    ~Text();

    void render();

private:
    TTF_Font* font;

};

#endif // __text__h
