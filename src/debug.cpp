#include <iostream>

#include "SDL.h"
#include "debug.h"

void logSDLError(std::string mes) {
    std::cerr << mes << ' ' << SDL_GetError() << '\n';
    exit(1);
}
