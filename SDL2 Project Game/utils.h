#ifndef __utils__h
#define __utils__h

int randUint(int r); // [0, r]

int randInt(int l, int r); // [l, r]

float randF(float l, float r); // [lf, rf]

double getDistance(double x1, double y1, double x2, double y2);

double getAngle(int x1, int y1, int x2, int y2);

bool onScreen(int x, int y, SDL_Rect camera);

#define rgb(red, green, blue) SDL_Color {red, green, blue}
#define rgbA(red, green, blue, alpha) SDL_Color {red, green, blue, alpha}

#endif // __utils__h
