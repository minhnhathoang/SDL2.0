#include "header.h"
#include "timer.h"

Timer::Timer() {
    currentTime = 0;
    elapsedTime = 0;
}

void Timer::reset() {
    currentTime = 0;
    elapsedTime = 0;
}

void Timer::update() {
    elapsedTime = currentTime += SDL_GetTicks() - currentTime;
    currentTime += elapsedTime;
}

uint64_t Timer::getCurrentTime() {
    return currentTime;
}

//int Timer::getHours() {
//    return (currentTime / (1000 * 60 * 60);
//}
//
//int Time::getMinutes() {
//    return (currentTime / (1000 * 60)) %
//}
//
//int Time::getSeconds() {
//
//}
