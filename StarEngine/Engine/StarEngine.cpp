//
// Created by ReSung on 2021-08-14.
//

#include <iostream>
#include "StarEngine.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"


StarEngine *StarEngine::GetInstance() {
    if(!instance)
        instance = new StarEngine();
    return instance;
};

StarEngine::StarEngine() {
    std::cout << "ayo" << std::endl;

    vulkan = new StarVulkan();

    camera = new Camera();
    //Not yet used
    keyboard = new Keyboard(camera);
    mouse = new Mouse(camera);

    glfwSetKeyCallback(vulkan->window, Keyboard::KeyInput);
    glfwSetCursorPosCallback(vulkan->window, Mouse::MouseInput);
}

void StarEngine::StartEngine() {
    EngineLoop();
}

void StarEngine::EngineLoop() {
    while(!glfwWindowShouldClose(vulkan->window)) {
        glfwPollEvents();
        camera->UpdateCamera();
        //Draw();
    }
    //vkDeviceWaitIdle(device);
}