//
// Created by ReSung on 2021-08-18.
//

#include <iostream>
#include <utility>
#include "ScopedClock.hpp"

ScopedClock::ScopedClock(std::string name, bool fps) {
    this->name = std::move(name);
    this->fps = fps;
    start = std::chrono::high_resolution_clock::now();
}

ScopedClock::ScopedClock() {
    start = std::chrono::high_resolution_clock::now();
}

ScopedClock::~ScopedClock() {
    if(!name.empty()) {
        auto end = std::chrono::high_resolution_clock::now();
        auto delta = ((double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())*0.000000001f;
        if(fps) {
            delta = 1.0f/delta;
        }
        std::cout << name << delta << std::endl;
    }
}

void ScopedClock::Reset() {
    start = std::chrono::high_resolution_clock::now();
}

double ScopedClock::GetElapsedSeconds() {
    auto end = std::chrono::high_resolution_clock::now();
    return ((double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())*0.000000001f;
}
