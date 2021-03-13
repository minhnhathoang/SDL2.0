#ifndef __globals__h
#define __globals__h

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int FPS = 60;

const int MAX_KEY = 400;

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

static const char* listCrew[] = { "assets/images/sprites/blue.png",
                                  "assets/images/sprites/brown.png",
                                  "assets/images/sprites/black.png",
                                  "assets/images/sprites/cyan.png",
                                  "assets/images/sprites/fortegreen.png",
                                  "assets/images/sprites/green.png",
                                  "assets/images/sprites/lightgreen.png",
                                  "assets/images/sprites/lime.png",
                                  "assets/images/sprites/orange.png",
                                  "assets/images/sprites/pink.png",
                                  "assets/images/sprites/purple.png",
                                  "assets/images/sprites/red.png",
                                  "assets/images/sprites/tan.png",
                                  "assets/images/sprites/white.png",
                                  "assets/images/sprites/yellow.png",
                                  "assets/images/sprites/boss.png",
                                };

static const char* listDeath[] = { "assets/images/die/die_blue.png",
                                   "assets/images/die/die_brown.png",
                                   "assets/images/die/die_black.png",
                                   "assets/images/die/die_cyan.png",
                                   "assets/images/die/die_fortegreen.png",
                                   "assets/images/die/die_green.png",
                                   "assets/images/die/die_lightgreen.png",
                                   "assets/images/die/die_lime.png",
                                   "assets/images/die/die_orange.png",
                                   "assets/images/die/die_pink.png",
                                   "assets/images/die/die_purple.png",
                                   "assets/images/die/die_red.png",
                                   "assets/images/die/die_tan.png",
                                   "assets/images/die/die_white.png",
                                   "assets/images/die/die_yellow.png",
                                 };

enum {
    RIFLE,
    PISTOL,

    MAX_GUN
};

static const char* listGun[] { "assets/images/gun/1.png",

                             };

static const char* listBullet[] { "assets/images/bullet/1.png",

                                };

struct Mouse {
    int x, y, L, R;
    Mouse() : x(-1), y(-1), L(0), R(0) {}
};

#endif // __globals__h

