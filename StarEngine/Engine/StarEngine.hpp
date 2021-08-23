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
#include "Object/GameObject.hpp"

class StarEngine {
private:
    static StarEngine *instance;
    StarEngine();

    StarVulkan *vulkan;
    Keyboard *keyboard;
    Mouse *mouse;
    uint32_t currentFrame = 0;
    uint32_t iterator = 0;

    //Runtime
    void EngineLoop();
    void DrawFrame();
    void UpdateUniformBuffer(uint32_t currentImage);
    void UpdateVertexBuffer();

    uint32_t gameObjectCount = 2;
    std::vector<GameObject> gameObjects;

public:
    static StarEngine *GetInstance();
    void StartEngine();

    Camera *camera;
    bool framebufferResized = false;
};


#endif //STARENGINE_STARENGINE_HPP
