//
// Created by ReSung on 2021-08-18.
//

#ifndef STARENGINE_SCOPEDCLOCK_HPP
#define STARENGINE_SCOPEDCLOCK_HPP


#include <chrono>

class ScopedClock {
private:
    bool fps = false;
    bool ms = false;
    std::string name;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> start;
public:
    explicit ScopedClock(std::string name, bool fps, bool ms = false);
    ScopedClock();

    virtual ~ScopedClock();

    double GetElapsedSeconds();
    long long GetElapsedNanoSeconds();

    void Reset();
};


#endif //STARENGINE_SCOPEDCLOCK_HPP
