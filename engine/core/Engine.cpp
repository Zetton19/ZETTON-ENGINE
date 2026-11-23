#include "Engine.h"

#include <iostream>
#include <thread>

Engine::Engine()
    : initialized(false),
      deltaTime(0.0),
      frameCount(0) {
}

void Engine::initialize() {
    initialized = true;
    previousFrame = Clock::now();

    std::cout << "[CORE] Engine initialized\n";
}

void Engine::runForSeconds(double seconds) {

    if (!initialized) {
        std::cout << "[ERROR] Engine not initialized\n";
        return;
    }

    const auto startTime = Clock::now();

    auto nextFrame = startTime;

    const std::chrono::duration<double> targetFrame(1.0 / 60.0);

    while (true) {

        auto currentTime = Clock::now();

        double elapsed =
            std::chrono::duration<double>(
                currentTime - startTime
            ).count();

        if (elapsed >= seconds) {
            break;
        }

        deltaTime =
            std::chrono::duration<double>(
                currentTime - previousFrame
            ).count();

        previousFrame = currentTime;

        frameCount++;

        nextFrame += std::chrono::duration_cast<Clock::duration>(
            targetFrame
        );

        std::this_thread::sleep_until(nextFrame);
    }

    double actualTime =
        std::chrono::duration<double>(
            Clock::now() - startTime
        ).count();

    double fps = frameCount / actualTime;

    std::cout << "\n[ENGINE REPORT]\n";
    std::cout << "Frames: " << frameCount << "\n";
    std::cout << "FPS: " << fps << "\n";
    std::cout << "Delta Time: " << deltaTime << " seconds\n";
    std::cout << "[CORE] Game loop finished\n";
}
