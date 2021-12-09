//
// Created by ReSung on 2021-08-18.
//

#include <iostream>
#include <utility>
#include "ScopedClock.hpp"

ScopedClock::ScopedClock(std::string name, bool fps, bool ms) {
    this->name = std::move(name);
    this->fps = fps;
    this->ms = ms;
    start = std::chrono::high_resolution_clock::now();
}

ScopedClock::ScopedClock() {
    start = std::chrono::high_resolution_clock::now();
}

ScopedClock::~ScopedClock() {
    if(!name.empty()) {
        double delta;
        if(fps || !ms) {
            delta = GetElapsedSeconds();
        } else {
            std::cout << name << (double)GetElapsedNanoSeconds()*0.000001 << "ms" << std::endl;
            return;
        };

        if(fps) {
            delta = 1.0f/delta;
        }

        std::cout << name << delta << std::endl;
    }
}

void ScopedClock::Reset() {
    start = std::chrono::high_resolution_clock::now();
}

long long ScopedClock::GetElapsedNanoSeconds() {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double ScopedClock::GetElapsedSeconds() {
    auto end = std::chrono::high_resolution_clock::now();
    return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()*0.000000001;
}
