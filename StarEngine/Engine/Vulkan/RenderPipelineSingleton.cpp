//
// Created by ReSung on 2021-09-10.
//

#include "RenderPipelineSingleton.hpp"

RenderPipelineSingleton *RenderPipelineSingleton::getInstance() {
    if(RenderPipelineSingleton::instance==nullptr){
        throw std::runtime_error("RenderPipelineSingleton not initialized!");
    }
    return RenderPipelineSingleton::instance;
}

void RenderPipelineSingleton::AddPipeline(VkDevice device, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VkRenderPass renderPass) {
    RenderPipelineSingleton *pInstace = getInstance();
    pInstace->shaders->Add("Resources/Shaders/a-vert.spv", new ShaderObject("Resources/Shaders/a-vert.spv", device));
    pInstace->shaders->Add("Resources/Shaders/a-frag.spv", new ShaderObject("Resources/Shaders/a-frag.spv", device));
    pInstace->shaders->Add("Resources/Shaders/b-frag.spv", new ShaderObject("Resources/Shaders/b-frag.spv", device));

    pInstace->renderPipelines.push_back(new RenderPipeline(device, swapChainExtent, descriptorSetLayout, renderPass, "Resources/Shaders/a-vert.spv", "Resources/Shaders/a-frag.spv"));
}

void RenderPipelineSingleton::Initialize(StarVulkan *vulkan) {
    instance = new RenderPipelineSingleton();
    instance->vulkan = vulkan;
}

RenderPipelineSingleton::RenderPipelineSingleton() {
    shaders = new Dictionary<std::string, ShaderObject*>();
};
RenderPipelineSingleton* RenderPipelineSingleton::instance = nullptr;
//Dictionary<std::string, ShaderObject*> *RenderPipelineSingleton::shaders = new Dictionary<std::string, ShaderObject*>();