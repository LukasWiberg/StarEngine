//
// Created by ReSung on 2021-09-10.
//

#ifndef B_OBJ_RENDERPIPELINESINGLETON_HPP
#define B_OBJ_RENDERPIPELINESINGLETON_HPP
#include "RenderPipeline.hpp"
#include "StarVulkan.hpp"
#include "../General/Dictionary.hpp"


class RenderPipelineSingleton {
private:
    RenderPipelineSingleton();

    static RenderPipelineSingleton *instance;
    std::vector<RenderPipeline*> renderPipelines;
//    std::vector<ShaderObject*> shaders;
    Dictionary<std::string, ShaderObject*> *shaders;

    StarVulkan *vulkan = nullptr;

public:
    static RenderPipelineSingleton *getInstance();
    RenderPipelineSingleton(RenderPipelineSingleton &other) = delete;
    void operator=(const RenderPipelineSingleton &) = delete;
    static void AddPipeline(VkDevice device, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VkRenderPass renderPass);

    static void Initialize(StarVulkan *vulkan);
};


#endif //B_OBJ_RENDERPIPELINESINGLETON_HPP
