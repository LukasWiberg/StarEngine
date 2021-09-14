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

RenderPipeline *RenderPipelineSingleton::AddPipeline(const char *vertPath, const char *fragPath) {
    return RenderPipelineSingleton::AddPipeline(RenderPipelineSingleton::instance->vulkan->device, RenderPipelineSingleton::instance->vulkan->swapChainExtent, RenderPipelineSingleton::instance->vulkan->descriptorSetLayout, RenderPipelineSingleton::instance->vulkan->renderPass, vertPath, fragPath);
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
    RenderPipelineSingleton::instance->ReCreateGraphicsPipelines();
    return RenderPipelineSingleton::instance->renderPipelines[RenderPipelineSingleton::instance->renderPipelines.size()];
}

void RenderPipelineSingleton::ReCreateGraphicsPipelines() {
    if(!graphicsPipelines.empty()) {
        for(auto graphicsPipeline : graphicsPipelines) {
            vkDestroyPipeline(vulkan->device, graphicsPipeline, nullptr);
        }
        graphicsPipelines.clear();
    }
    graphicsPipelines.resize(renderPipelines.size());

    std::vector<VkGraphicsPipelineCreateInfo> createInfos;
    for(auto renderPipeline : renderPipelines) {
        createInfos.push_back(renderPipeline->pipelineInfo);
    }

    VkResult res = vkCreateGraphicsPipelines(vulkan->device, VK_NULL_HANDLE, createInfos.size(), createInfos.data(), nullptr, graphicsPipelines.data());
    if(res != VK_SUCCESS) {
        printf("failed to create graphics pipelines!");
    }
}

std::vector<RenderPipeline*> RenderPipelineSingleton::GetRenderPipelines() {
    return RenderPipelineSingleton::instance->renderPipelines;
}

RenderPipelineSingleton::RenderPipelineSingleton() {
    shaders = new Dictionary<std::string, ShaderObject*>();
};

RenderPipelineSingleton::~RenderPipelineSingleton() {
    shaders->Clear();
    for(auto renderPipeline : renderPipelines) {
        delete(renderPipeline);
    }
    renderPipelines.clear();

    for(auto graphicsPipeline : graphicsPipelines) {
        vkDestroyPipeline(vulkan->device, graphicsPipeline, nullptr);
    }
    graphicsPipelines.clear();
}

void RenderPipelineSingleton::Destroy() {
    getInstance()->~RenderPipelineSingleton();
}


RenderPipelineSingleton* RenderPipelineSingleton::instance = nullptr;

RenderPipeline *RenderPipelineSingleton::GetRenderPipeline(int index) {
    return RenderPipelineSingleton::instance->renderPipelines[index];
}

VkPipeline RenderPipelineSingleton::GetGraphicsPipeline(int index) {
    return RenderPipelineSingleton::instance->graphicsPipelines[index];
}
