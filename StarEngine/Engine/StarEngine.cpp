//
// Created by ReSung on 2021-08-14.
//

#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
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
        this->vulkan->verticesList.resize(1);
        this->vulkan->indicesList.resize(1);
        for(int i = 0; i<gameObjectCount; i++) {
            if(i == 0) {
                gameObjects[0] = GameObject(glm::vec3(0,0,0), glm::vec3(0.0f, 0.0f, 0.0f), ModelHelper::LoadModel("Resources/Meshes/b.obj"));
            } else {
                gameObjects[i] = GameObject(&gameObjects[0]);
                gameObjects[i].position = glm::vec3(dist(randGen),dist(randGen),dist(randGen));
            }
            uint32_t lastVertexIndex = this->vulkan->verticesList[0].size();
            this->vulkan->verticesList[0].resize(lastVertexIndex + gameObjects[i].model.vertices.size());
            for(int j = 0; j<gameObjects[i].model.vertices.size(); j++) {
                this->vulkan->verticesList[0][lastVertexIndex + j] = gameObjects[i].model.vertices[j];
            }
            uint32_t lastIndexIndex = this->vulkan->indicesList[0].size();
            this->vulkan->indicesList[0].resize(lastIndexIndex + gameObjects[i].model.indices.size());
            for(int j = 0; j<gameObjects[i].model.indices.size(); j++) {
                this->vulkan->indicesList[0][lastIndexIndex + j] = lastVertexIndex + gameObjects[i].model.indices[j];
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
//        ScopedClock d = ScopedClock("FPS: ", true);
        glfwPollEvents();
        auto frameTime = c.GetElapsedSeconds();

        this->LogicUpdate(frameTime);
        this->GraphicsUpdate(frameTime);

        camera->UpdateCamera(frameTime);
        c.Reset();
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
        gameObjects[i].UpdateTransform();
    }
}

void StarEngine::DrawFrame(double frameTime) {
    vkWaitForFences(vulkan->device, 1, &vulkan->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(vulkan->device, vulkan->swapChain, UINT64_MAX, vulkan->imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        vulkan->RecreateSwapChain();
        return;
    } else if (result != VK_SUCCESS) {
        if(result != VK_SUBOPTIMAL_KHR) {
            printf("failed to acquire swap chain image!");
        }
    }


    UpdateUniformBuffer(imageIndex);

    if(vulkan->imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(vulkan->device, 1, &vulkan->imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    vulkan->imagesInFlight[imageIndex] = vulkan->inFlightFences[currentFrame];

    VkCommandBuffer cmdBuffer = this->vulkan->BeginSingleTimeCommands(this->vulkan->mainCommandPool);
    StartRenderPass(cmdBuffer);
    vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->vulkan->graphicsPipelines[0]);


    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &this->vulkan->vertexBuffers[0], offsets);

    vkCmdBindIndexBuffer(cmdBuffer, this->vulkan->indexBuffers[0], 0, VK_INDEX_TYPE_UINT32);

    vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->vulkan->renderPipelines[1]->pipelineLayout, 0, 1, &this->vulkan->descriptorSets[currentFrame], 0, nullptr);

    int32_t vertexOffset = 0;
    for(int i = 0; i<(int)std::floor(gameObjects.size()/2); i++) {
        auto gameObject = gameObjects[i];

        PushConstantData constants{};
        constants.transform = gameObject.transform;
        vkCmdPushConstants(cmdBuffer, this->vulkan->renderPipelines[0]->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstantData), &constants);
        vkCmdDrawIndexed(cmdBuffer, gameObject.model.indices.size(), 1, 0, vertexOffset, 0);
        vertexOffset += (int32_t) gameObject.model.vertices.size();
    }


    vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->vulkan->graphicsPipelines[1]);

    for(int i = (int)std::floor(gameObjects.size()/2); i<gameObjects.size(); i++) {
        auto gameObject = gameObjects[i];
        PushConstantData constants{};
        constants.transform = gameObject.transform;
        vkCmdPushConstants(cmdBuffer, this->vulkan->renderPipelines[1]->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstantData), &constants);
        vkCmdDrawIndexed(cmdBuffer, gameObject.model.indices.size(), 1, 0, vertexOffset, 0);
        vertexOffset += (int32_t) gameObject.model.vertices.size();
    }
    vkCmdEndRenderPass(cmdBuffer);



    EndRenderCommand(cmdBuffer, imageIndex);
    rotIterator+=frameTime;
    this->currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

VkCommandBuffer StarEngine::StartRenderPass(VkCommandBuffer cmdBuffer) {
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

    vkCmdBeginRenderPass(cmdBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
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
    ubo.proj = glm::perspective(glm::radians(90.0f), (float) vulkan->swapChainExtent.width / (float) vulkan->swapChainExtent.height, 0.1f, 1000.0f);
    ubo.model = glm::mat4(1.0f);
    ubo.view = camera->view;


    ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(vulkan->device, vulkan->uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(vulkan->device, vulkan->uniformBuffersMemory[currentImage]);
}