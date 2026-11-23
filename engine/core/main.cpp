#include <iostream>
#include "Engine.h"

int main() {

    std::cout << "============================\n";
    std::cout << "       ZETTON ENGINE\n";
    std::cout << "============================\n";

    std::cout << "Version: 0.1.1\n";
    std::cout << "Platform: Android Development\n";
    std::cout << "Architecture: ARM64\n\n";

    Engine engine;

    engine.initialize();

    engine.runForSeconds(3.0);

    return 0;
}
