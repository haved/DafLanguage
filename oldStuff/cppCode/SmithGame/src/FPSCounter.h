#pragma once

#include <SDL2/SDL.h>

class FPSCounter {
public:
    FPSCounter();
    void NextFrame();
private:
    uint32_t m_prevPrintout;
    uint32_t m_framesSincePrintout;
};
