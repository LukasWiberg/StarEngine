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
    std::vector<VkPipeline> graphicsPipelines;
    Dictionary<std::string, ShaderObject*> *shaders;

    StarVulkan *vulkan = nullptr;

    void ReCreateGraphicsPipelines();

    virtual ~RenderPipelineSingleton();
public:
    static RenderPipelineSingleton *getInstance();
    RenderPipelineSingleton(RenderPipelineSingleton &other) = delete;
    void operator=(const RenderPipelineSingleton &) = delete;
    static RenderPipeline *AddPipeline(const char *vertPath, const char *fragPath);
    static RenderPipeline *AddPipeline(VkDevice device, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VkRenderPass renderPass, const char *vertPath, const char *fragPath);
    static std::vector<RenderPipeline*> GetRenderPipelines();

    static RenderPipeline *GetRenderPipeline(int index);
    static VkPipeline GetGraphicsPipeline(int index);

    static void Initialize(StarVulkan *vulkan);
    static void Destroy();
};


#endif //B_OBJ_RENDERPIPELINESINGLETON_HPP
