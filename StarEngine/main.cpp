#include <iostream>
#include "Engine/StarEngine.hpp"

StarEngine *StarEngine::instance = nullptr;

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    StarEngine *engine = StarEngine::GetInstance();
    engine->StartEngine();
    return 0;
}
