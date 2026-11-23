#pragma once

#include <chrono>

class Engine {
public:
    Engine();

    void initialize();
    void runForSeconds(double seconds);

private:
    bool initialized;

    double deltaTime;
    unsigned int frameCount;

    using Clock = std::chrono::steady_clock;

    Clock::time_point previousFrame;
};
