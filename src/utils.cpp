#include "header.h"
#include "utils.h"

static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int randUint(int r) {
    assert(r >= 0 && "randomError: r must be positive");
    return rng() % (r + 1);
}

int randInt(int l, int r) {
    std::uniform_int_distribution<int> distrib(l, r);
    return distrib(rng);
}

double getDistance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double getAngle(int x1, int y1, int x2, int y2) {
    double angle = atan2(y2 - y1, x2 - x1) * 180 / PI;
    return angle;
}
