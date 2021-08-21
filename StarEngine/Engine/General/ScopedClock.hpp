//
// Created by ReSung on 2021-08-18.
//

#ifndef STARENGINE_SCOPEDCLOCK_HPP
#define STARENGINE_SCOPEDCLOCK_HPP


#include <chrono>

class ScopedClock {
private:
    bool fps = false;
    std::string name;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> start;
public:
    explicit ScopedClock(std::string name, bool fps);
    ScopedClock();

    virtual ~ScopedClock();

    double GetElapsedSeconds();

    void Reset();
};


#endif //STARENGINE_SCOPEDCLOCK_HPP
