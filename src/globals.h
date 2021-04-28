#ifndef __globals__h
#define __globals__h

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

const int FPS = 60;

const int MAX_KEY = 400;

const double PI = acos(-1);

enum {
    VICTORY,
    DEFEAT
};

enum {
    LIGHT,
    FLASHLIGHT,
};

static const char* lights[] = {
    "assets/images/light.png",
    "assets/images/flashlight.png",
};

enum {
    PLAY,
    CONTINUE,
    RESTART,
    QUIT
};


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
    MAX_CREW = 16,
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
                                   "assets/images/die/die_boss.png",
                                 };

static const char* listGun[] {
    "assets/images/gun/0.png",
    "assets/images/gun/1.png",
    "assets/images/gun/2.png",
    "assets/images/gun/3.png",
    "assets/images/gun/4.png",
    "assets/images/gun/5.png",
    "assets/images/gun/6.png",
    "assets/images/gun/7.png",
    "assets/images/gun/8.png",
    "assets/images/gun/9.png",
    "assets/images/gun/10.png",
    "assets/images/gun/11.png",
    "assets/images/gun/12.png",
};

static const char* listAmmo[] {
    "assets/images/bullet/0.png",
    "assets/images/bullet/2.png",
    "assets/images/bullet/3.png",
    "assets/images/bullet/4.png",
    "assets/images/bullet/5.png",
    "assets/images/bullet/6.png",
    "assets/images/bullet/7.png",
    "assets/images/bullet/8.png",
    "assets/images/bullet/9.png",
    "assets/images/bullet/10.png",
    "assets/images/bullet/11.png",
};

static const char* listLight[] {
    "assets/images/light/1.png",
    "assets/images/light/2.png",
    "assets/images/light/3.png",
    "assets/images/light/4.png",
    "assets/images/light/5.png",
    "assets/images/light/6.png",
    "assets/images/light/7.png",
};

static const SDL_Color listColor[] = {
    { 19, 47, 210 },
    { 113, 73, 30 },
    { 43, 45, 46 },
    { 84, 239, 212 },
    { 43, 146, 88},
    { 27, 128, 53 },
    { 118, 255, 3 },
    { 77, 234, 52 },
    { 240, 123, 12 },
    { 243, 82, 188 },
    { 90, 55, 146 },
    { 225, 21, 21 },
    { 143, 129, 134 },
    { 202, 211, 213 },
    { 243, 246, 88 }
};


struct Mouse {
    int x, y, L, R;
    Mouse() : x(-1), y(-1), L(0), R(0) {}
};

#endif // __globals__h

