#include "header.h"
#include "utils.h"

static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int randUint(int r) {
    assert(r > 0 && "randomError: r must be positive");
    return rng() % (r + 1);
}

int randInt(int l, int r) {
    std::uniform_int_distribution<int> distrib(l, r);
    return distrib(rng);
}
