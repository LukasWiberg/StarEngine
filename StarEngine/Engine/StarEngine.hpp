//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_STARENGINE_HPP
#define STARENGINE_STARENGINE_HPP

#define GLFW_INCLUDE_VULKAN
#include <chrono>
#include <GLFW/glfw3.h>
#include <random>
#include <vulkan/vulkan.hpp>
#include "Graphics/Camera.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"
#include "Vulkan/StarVulkan.hpp"
#include "Object/GameObject.hpp"

class StarEngine {
private:
    std::random_device rd;
    std::mt19937 randGen{rd()}; // or std::default_random_engine e{rd()};
    std::uniform_real_distribution<double> dist{-10.0, 10.0};
    static StarEngine *instance;
    StarEngine();

    StarVulkan *vulkan;
    Keyboard *keyboard;
    Mouse *mouse;
    uint32_t currentFrame = 0;
    uint32_t iterator = 0;
    double rotIterator = 0.0f;

    //Runtime
    void EngineLoop();
    void DrawFrame(double frameTime);
    void UpdateUniformBuffer(uint32_t currentImage);

    VkCommandBuffer StartRenderPass(VkCommandBuffer cmdBuffer);
    void EndRenderCommand(VkCommandBuffer cmdBuffer, uint32_t imageIndex);

    uint32_t gameObjectCount = 2048;
    std::vector<GameObject*> gameObjects;

    void GraphicsUpdate(double frameTime);
    void LogicUpdate(double frameTime);

public:
    static StarEngine *GetInstance();
    void StartEngine();
    virtual ~StarEngine();

    Camera *camera;
    bool framebufferResized = false;
};


#endif //STARENGINE_STARENGINE_HPP
