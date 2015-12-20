#include "Time.h"
#include <SDL2/SDL.h>
#include <iostream>

float deltaTime;
long deltaMillis;
long prevUpdate;

void UpdateDeltaTime() {
    long newTicks = SDL_GetTicks();
    long newDelta = newTicks-prevUpdate;
    prevUpdate = newTicks;
    if(newDelta > 50) {
        std::cout << "Frame took over 50ms! Using 20ms instead." << std::endl;
        newDelta = 20;
    }

    deltaTime = newDelta / 1000.f;
    deltaMillis = newDelta;
}

float GetDeltaTime() {
    return deltaTime;
}

long GetDeltaMillis() {
    return deltaMillis;
}

long GetCurrentMillis() {
    return prevUpdate;
}
