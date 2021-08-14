//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_STARENGINE_HPP
#define STARENGINE_STARENGINE_HPP

#define GLFW_INCLUDE_VULKAN
#include <chrono>
#include <GLFW/glfw3.h>
#include "Graphics/Camera.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"

class StarEngine {
private:
    static StarEngine *instance;
    StarEngine();

    GLFWwindow *window;

    Keyboard *keyboard;
    Mouse *mouse;

    void EngineLoop();
public:
    static StarEngine *GetInstance();
    Camera *camera;
};


#endif //STARENGINE_STARENGINE_HPP
