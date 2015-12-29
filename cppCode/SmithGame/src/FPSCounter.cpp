#include "FPSCounter.h"

#include <iostream>

FPSCounter::FPSCounter() : m_prevPrintout(0), m_framesSincePrintout(0) {}

void FPSCounter::NextFrame() {
    m_framesSincePrintout++;
    uint32_t diff = SDL_GetTicks() - m_prevPrintout;
    if(diff>=1000) {
        std::cout << "FPS: " << (m_framesSincePrintout*1000.f/diff) << std::endl;
        m_prevPrintout=SDL_GetTicks();
        m_framesSincePrintout = 0;
    }
}
