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

    camera = new Camera();
    //Not yet used
    keyboard = new Keyboard(camera);
    mouse = new Mouse(camera);

    glfwSetKeyCallback(window, Keyboard::KeyInput);
    glfwSetCursorPosCallback(window, Mouse::MouseInput);

    EngineLoop();
}

void StarEngine::EngineLoop() {
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        camera->UpdateCamera();
        //Draw();
    }
    //vkDeviceWaitIdle(device);
}