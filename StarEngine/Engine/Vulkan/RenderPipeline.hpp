//
// Created by ReSung on 2021-09-09.
//

#ifndef B_OBJ_RENDERPIPELINE_HPP
#define B_OBJ_RENDERPIPELINE_HPP


#include <vulkan/vulkan_core.h>
#include <vector>
#include "../Shaders/ShaderObject.hpp"

class RenderPipeline {
private:


public:
    //Temp
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
    VkVertexInputBindingDescription bindingDescription;
    std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
    std::vector<ShaderObject*> shaderObjects;
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    VkPipelineViewportStateCreateInfo viewportState{};
    VkViewport viewport{};
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    VkPipelineMultisampleStateCreateInfo multisampling{};
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    VkPipelineColorBlendStateCreateInfo colorBlending{};
    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    VkPushConstantRange pushConstantRange{};
    VkRect2D scissor;
    VkOffset2D offset = {0, 0};



    VkPipelineLayout pipelineLayout{};
    VkGraphicsPipelineCreateInfo pipelineInfo{};
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
    RenderPipeline(VkDevice device, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VkRenderPass renderPass, int config);
};


#endif //B_OBJ_RENDERPIPELINE_HPP
