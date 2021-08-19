//
// Created by ReSung on 2021-08-18.
//

#include <iostream>
#include "ScopedClock.hpp"

ScopedClock::ScopedClock() {
    start = std::chrono::high_resolution_clock::now();
}

ScopedClock::~ScopedClock() {
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << ((double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())*0.000000001f << std::endl;
}

void ScopedClock::Reset() {
    start = std::chrono::high_resolution_clock::now();
}

double ScopedClock::GetElapsedSeconds() {
    auto end = std::chrono::high_resolution_clock::now();
    return ((double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())*0.000000001f;
}
