#include <iostream>
#include "Engine/StarEngine.hpp"

StarEngine *StarEngine::instance = nullptr;

int main() {
    StarEngine *engine = StarEngine::GetInstance();
    engine->StartEngine();
    return 0;
}
