#include "Time.h"
#include <SDL2/SDL.h>
#include <iostream>

uint32_t deltaMillis;
float    deltaTime;
uint32_t prevUpdate;
float    prevUpdateSeconds;
uint32_t ingameMillis;
float    ingameSeconds;

void UpdateDeltaTime() {
    uint32_t newTicks = SDL_GetTicks();
    uint32_t newDelta = newTicks-prevUpdate;
    prevUpdate = newTicks;
    prevUpdateSeconds = prevUpdate/1000.f;
    if(newDelta > 50) {
        std::cout << "Frame took over 50ms! Using 20ms instead." << std::endl;
        newDelta = 20;
    }

    deltaTime = newDelta / 1000.f;
    deltaMillis = newDelta;
}

void UpdateIngameTime() {
    ingameMillis+=deltaMillis;
    ingameSeconds=ingameMillis/1000.f;
}

inline uint32_t GetDeltaMillis() {
    return deltaMillis;
}

float GetDeltaTime() {
    return deltaTime;
}

inline uint32_t GetCurrentMillis() {
    return prevUpdate;
}

float GetCurrentSeconds() {
    return prevUpdateSeconds;
}

inline uint32_t GetIngameMillis() {
    return ingameMillis;
}

float GetIngameSeconds() {
    return ingameSeconds;
}
