#include <iostream>
#include "Engine/StarEngine.hpp"

StarEngine *StarEngine::instance = nullptr;

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    try {
        StarEngine *engine = StarEngine::GetInstance();
        engine->StartEngine();
    } catch(std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
