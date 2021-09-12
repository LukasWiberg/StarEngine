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


void RenderPipelineSingleton::Initialize(StarVulkan *vulkan) {
    instance = new RenderPipelineSingleton();
    instance->vulkan = vulkan;
}

RenderPipeline *RenderPipelineSingleton::AddPipeline(VkDevice device, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VkRenderPass renderPass, const char *vertPath, const char *fragPath) {
    auto vertShader = RenderPipelineSingleton::instance->shaders->Get(vertPath);
    auto fragShader = RenderPipelineSingleton::instance->shaders->Get(fragPath);

    if(vertShader == nullptr) {
        vertShader = new ShaderObject(vertPath, device);
        RenderPipelineSingleton::instance->shaders->Add(vertPath, vertShader);
    }

    if(fragShader == nullptr) {
        fragShader = new ShaderObject(fragPath, device);
        RenderPipelineSingleton::instance->shaders->Add(fragPath, fragShader);
    }

    RenderPipelineSingleton::instance->renderPipelines.push_back(new RenderPipeline(device, swapChainExtent, descriptorSetLayout, renderPass, vertShader, fragShader));
    return RenderPipelineSingleton::instance->renderPipelines[RenderPipelineSingleton::instance->renderPipelines.size()];
}

std::vector<RenderPipeline*> RenderPipelineSingleton::GetRenderPipelines() {
    return RenderPipelineSingleton::instance->renderPipelines;
}

RenderPipelineSingleton::RenderPipelineSingleton() {
    shaders = new Dictionary<std::string, ShaderObject*>();
};

RenderPipelineSingleton::~RenderPipelineSingleton() {
    shaders->Clear();
}

void RenderPipelineSingleton::Destroy() {
    getInstance()->~RenderPipelineSingleton();
}


RenderPipelineSingleton* RenderPipelineSingleton::instance = nullptr;
