//
// Created by ReSung on 2021-08-14.
//

#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "StarEngine.hpp"
#include "Constants.hpp"
#include "General/ScopedClock.hpp"


StarEngine *StarEngine::GetInstance() {
    if(!instance)
        instance = new StarEngine();
    return instance;
};

StarEngine::StarEngine() {
    srand((unsigned)time(nullptr));
    vulkan = new StarVulkan();
    {
        auto c = ScopedClock("GameObject creation time: ", false);
        gameObjects.resize(gameObjectCount);
        gameObjects[0] = GameObject(glm::vec3(0,0,0), glm::vec3(0.0f, 0.0f, 0.0f), ModelHelper::LoadModel("Resources/Meshes/a.obj"));

        for(int i = 1; i<gameObjectCount; i++) {
            gameObjects[i] = GameObject(&gameObjects[0]);
//            gameObjects[i] = GameObject(glm::vec3(0,0,0), glm::vec3(0,0,0), ModelHelper::LoadModel("Resources/Meshes/a.obj"));
            uint32_t lastVertexIndex = this->vulkan->vertices.size();
            this->vulkan->vertices.resize(lastVertexIndex+gameObjects[i].model.vertices.size());
            for(int j = 0; j<gameObjects[i].model.vertices.size(); j++) {
                this->vulkan->vertices[lastVertexIndex+j] = gameObjects[i].model.vertices[j];
            }
            uint32_t lastIndexIndex = this->vulkan->indices.size();
            this->vulkan->indices.resize(lastIndexIndex+gameObjects[i].model.indices.size());
            for(int j = 0; j<gameObjects[i].model.indices.size(); j++) {
                this->vulkan->indices[lastIndexIndex+j] = lastVertexIndex+gameObjects[i].model.indices[j];
            }
        }
    }

    vulkan->Initialize();

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
        ScopedClock d = ScopedClock("FPS: ", true);
        glfwPollEvents();
        auto frameTime = c.GetElapsedSeconds();

        this->LogicUpdate(frameTime);
        this->GraphicsUpdate(frameTime);

        camera->UpdateCamera(frameTime);
        c.Reset();
//        UpdateVertexBuffer();
        DrawFrame(frameTime);
    }
    vulkan->Cleanup();
}

void StarEngine::LogicUpdate(double frameTime) {
    for(int i = 0; i<gameObjects.size(); i++) {
        gameObjects[i].LogicUpdate(frameTime);
    }
}

void StarEngine::GraphicsUpdate(double frameTime) {
    for(int i = 0; i<gameObjects.size(); i++) {
        gameObjects[i].GraphicsUpdate(frameTime);
    }
}

void StarEngine::DrawFrame(double frameTime) {
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

    VkCommandBuffer cmdBuffer = StartRenderCommand();


    VkBuffer vertexBuffers[] = {this->vulkan->vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(cmdBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(cmdBuffer, this->vulkan->indexBuffer, 0, VK_INDEX_TYPE_UINT32);

    vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->vulkan->pipelineLayout, 0, 1, &this->vulkan->descriptorSets[currentFrame], 0, nullptr);

    int32_t vertexOffset = 0;
    for(auto & gameObject : gameObjects) {
        PushConstantData constants{};
        constants.transform = gameObject.transform;
//        constants.transform = glm::mat4(1.0f);
        vkCmdPushConstants(cmdBuffer, this->vulkan->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstantData), &constants);
        vkCmdDrawIndexed(cmdBuffer, gameObject.model.indices.size(), 1, 0, vertexOffset, 0);
        vertexOffset += (int32_t) gameObject.model.vertices.size();
    }


    EndRenderCommand(cmdBuffer, imageIndex);
    rotIterator+=frameTime;

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

VkCommandBuffer StarEngine::StartRenderCommand() {
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = this->vulkan->renderPass;
    renderPassInfo.framebuffer = this->vulkan->swapChainFrameBuffers[currentFrame];
    VkOffset2D offset = {0, 0};
    renderPassInfo.renderArea.offset = offset;
    renderPassInfo.renderArea.extent = this->vulkan->swapChainExtent;

    VkClearValue clearValues[2];
    VkClearColorValue clearColor = {{0.0f, 0.0f, 0.0f, 1.0f}};
    VkClearDepthStencilValue clearDepthStencil = {1.0f, 0};
    clearValues[0].color = clearColor;
    clearValues[1].depthStencil = clearDepthStencil;

    renderPassInfo.clearValueCount = 2;
    renderPassInfo.pClearValues = clearValues;

    VkCommandBuffer cmdBuffer = this->vulkan->BeginSingleTimeCommands(this->vulkan->mainCommandPool);
    vkCmdBeginRenderPass(cmdBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->vulkan->graphicsPipeline);
    return cmdBuffer;
}

void StarEngine::EndRenderCommand(VkCommandBuffer cmdBuffer, uint32_t imageIndex) {
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {vulkan->imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vulkan->commandBuffers[imageIndex];

    vkCmdEndRenderPass(cmdBuffer);
    this->vulkan->EndSingleTimeCommands(cmdBuffer, this->vulkan->mainCommandPool, this->vulkan->graphicsQueue);

    VkSemaphore signalSemaphores[] = {vulkan->renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(vulkan->device, 1, &vulkan->inFlightFences[currentFrame]);

    if(vkQueueSubmit(vulkan->graphicsQueue, 1, &submitInfo, vulkan->inFlightFences[currentFrame]) != VK_SUCCESS) {
        printf("Failed to submit draw command buffer!");
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
    VkResult result = vkQueuePresentKHR(vulkan->presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false;
        vulkan->RecreateSwapChain();
    } else if (result != VK_SUCCESS) {
        std::cout << "Failed to present swap chain image!" << std::endl;
    }
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

//void StarEngine::UpdateVertexBuffer() {
//    for(Vertex &vert : vulkan->vertices) {
//        vert.pos = vert.pos + glm::vec3((((float)rand()/RAND_MAX)-0.5f)*0.01f, (((float)rand()/RAND_MAX)-0.5f)*0.01f, (((float)rand()/RAND_MAX)-0.5f)*0.01f);
//    }
//
//    vkDeviceWaitIdle(vulkan->device);
//
//    void* data;
//    vkMapMemory(vulkan->device, vulkan->vertexBufferMemory, 0, sizeof(vulkan->vertices[0])*vulkan->vertices.size(), 0, &data);
//    memcpy(data, vulkan->vertices.data(), sizeof(vulkan->vertices[0])*vulkan->vertices.size());
//    vkUnmapMemory(vulkan->device, vulkan->vertexBufferMemory);
//}