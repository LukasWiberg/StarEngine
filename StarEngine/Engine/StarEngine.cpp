//
// Created by ReSung on 2021-08-14.
//

#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "StarEngine.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"
#include "Constants.hpp"
#include "General/ScopedClock.hpp"


StarEngine *StarEngine::GetInstance() {
    if(!instance)
        instance = new StarEngine();
    return instance;
};

StarEngine::StarEngine() {
    vulkan = new StarVulkan();

    camera = new Camera(1.0f);
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
    ScopedClock c = ScopedClock();
    while(!glfwWindowShouldClose(vulkan->window)) {
        glfwPollEvents();
        camera->UpdateCamera(c.GetElapsedSeconds());
        c.Reset();
        DrawFrame();
    }
    vulkan->Cleanup();
}

void StarEngine::DrawFrame() {
    vkWaitForFences(vulkan->device, 1, &vulkan->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(vulkan->device, vulkan->swapChain, UINT64_MAX, vulkan->imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        vulkan->RecreateSwapChain();
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        printf("failed to acquire swap chain image!");
    }

    UpdateUniformBuffer(imageIndex);

    if(vulkan->imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(vulkan->device, 1, &vulkan->imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    vulkan->imagesInFlight[imageIndex] = vulkan->inFlightFences[currentFrame];


    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {vulkan->imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vulkan->commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {vulkan->renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(vulkan->device, 1, &vulkan->inFlightFences[currentFrame]);

    if(vkQueueSubmit(vulkan->graphicsQueue, 1, &submitInfo, vulkan->inFlightFences[currentFrame]) != VK_SUCCESS) {
        printf("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {vulkan->swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    presentInfo.pResults = nullptr;
    result = vkQueuePresentKHR(vulkan->presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false;
        vulkan->RecreateSwapChain();
    } else if (result != VK_SUCCESS) {
        std::cout << "failed to present swap chain image!" << std::endl;
    }

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}


void StarEngine::UpdateUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
//    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(90.0f), (float) vulkan->swapChainExtent.width / (float) vulkan->swapChainExtent.height, 0.1f, 1000.0f);
    ubo.model = glm::mat4(1.0f);
    ubo.view = camera->view;


    ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(vulkan->device, vulkan->uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(vulkan->device, vulkan->uniformBuffersMemory[currentImage]);
}