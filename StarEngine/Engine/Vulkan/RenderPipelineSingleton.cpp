//
// Created by ReSung on 2021-09-10.
//

#include "RenderPipelineSingleton.hpp"

RenderPipelineSingleton* RenderPipelineSingleton::instance = nullptr;

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

RenderPipeline* RenderPipelineSingleton::BasicPipeline() {
    return RenderPipelineSingleton::AddPipeline(RenderPipelineSingleton::instance->vulkan->device, RenderPipelineSingleton::instance->vulkan->swapChainExtent, RenderPipelineSingleton::instance->vulkan->descriptorSetLayout, RenderPipelineSingleton::instance->vulkan->renderPass, "Resources/Shaders/a-vert.spv", "Resources/Shaders/a-frag.spv");
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
    //TODO: For now just use the vert and frag paths to generate an id, prefer to use the memory/shader objects to generate id.
    std::string pipelineId;
    pipelineId.append(fragPath);
    pipelineId.append(vertPath);
    RenderPipeline *pipeline = RenderPipelineSingleton::instance->renderPipelines.Get(pipelineId);
    if(pipeline == nullptr) {
        pipeline = new RenderPipeline(device, swapChainExtent, descriptorSetLayout, renderPass, vertShader, fragShader);
        RenderPipelineSingleton::instance->renderPipelines.Add(pipelineId, pipeline);
        RenderPipelineSingleton::instance->ReCreateGraphicsPipelines();
    }

    return pipeline;
}

void RenderPipelineSingleton::ReCreateGraphicsPipelines() {
    if(!graphicsPipelines.empty()) {
        for(auto graphicsPipeline : graphicsPipelines) {
            vkDestroyPipeline(vulkan->device, graphicsPipeline, nullptr);
        }
        graphicsPipelines.clear();
    }
    graphicsPipelines.resize(renderPipelines.Size());

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
    return RenderPipelineSingleton::instance->renderPipelines.GetAll();
}

RenderPipelineSingleton::RenderPipelineSingleton() {
    shaders = new Dictionary<std::string, ShaderObject*>();
};

RenderPipelineSingleton::~RenderPipelineSingleton() {
    for(auto shader : *shaders) {
        delete(shader);
    }
    shaders->Clear();
    for(auto renderPipeline : renderPipelines) {
        delete(renderPipeline);
    }
    renderPipelines.Clear();

    for(auto graphicsPipeline : graphicsPipelines) {
        vkDestroyPipeline(vulkan->device, graphicsPipeline, nullptr);
    }
    graphicsPipelines.clear();
}

void RenderPipelineSingleton::Destroy() {
    getInstance()->~RenderPipelineSingleton();
}

RenderPipeline *RenderPipelineSingleton::GetRenderPipeline(int index) {
    return RenderPipelineSingleton::instance->renderPipelines.GetAtIndex(index);
}

VkPipeline RenderPipelineSingleton::GetGraphicsPipeline(int index) {
    return RenderPipelineSingleton::instance->graphicsPipelines[index];
}
