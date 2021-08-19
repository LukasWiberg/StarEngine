//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_STARENGINE_HPP
#define STARENGINE_STARENGINE_HPP

#define GLFW_INCLUDE_VULKAN
#include <chrono>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include "Graphics/Camera.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"
#include "Vulkan/StarVulkan.hpp"

class StarEngine {
private:
    static StarEngine *instance;
    StarEngine();

    StarVulkan *vulkan;
    Keyboard *keyboard;
    Mouse *mouse;
    uint32_t currentFrame = 0;
    bool framebufferResized = false;

    //Runtime
    void EngineLoop();
    void DrawFrame();
    void UpdateUniformBuffer(uint32_t currentImage);
public:
    static StarEngine *GetInstance();
    void StartEngine();

    Camera *camera;
};


#endif //STARENGINE_STARENGINE_HPP
