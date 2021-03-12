#ifndef __globals__h
#define __globals__h

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int FPS = 60;

const int MAX_KEY = 255;

const double PI = acos(-1);


enum {
    BLUE,
    BROWN,
    BLACK,
    CYAN,
    FORTEGREEN,
    GREEN,
    LIGHTGREEN,
    LIME,
    ORANGE,
    PINK,
    PURPLE,
    RED,
    TAN,
    WHITE,
    YELLOW,
    BOSS,
    MAX_CREW = 15,
};

static const char* listCrew[] = { "image/blue.png",
                                  "image/brown.png",
                                  "image/black.png",
                                  "image/cyan.png",
                                  "image/fortegreen.png",
                                  "image/green.png",
                                  "image/lightgreen.png",
                                  "image/lime.png",
                                  "image/orange.png",
                                  "image/pink.png",
                                  "image/purple.png",
                                  "image/red.png",
                                  "image/tan.png",
                                  "image/white.png",
                                  "image/yellow.png",
                                  "image/boss.png",
                                };


#endif // __globals__h

