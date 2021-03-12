#include "header.h"
#include "debug.h"

void logSDLError(const char* mes) {
    cerr << mes << ' ' << SDL_GetError() << '\n';
    exit(1);
}
