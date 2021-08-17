#include <iostream>
#include "Engine/StarEngine.hpp"

StarEngine *StarEngine::instance = nullptr;

int main() {
    std::cout << "Hello, World!" << std::endl;
    StarEngine *engine = StarEngine::GetInstance();
    engine->StartEngine();
    return 0;
}
