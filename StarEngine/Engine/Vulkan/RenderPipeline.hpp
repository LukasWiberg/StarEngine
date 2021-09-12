//
// Created by ReSung on 2021-09-09.
//

#ifndef B_OBJ_RENDERPIPELINE_HPP
#define B_OBJ_RENDERPIPELINE_HPP


#include <vulkan/vulkan_core.h>
#include <vector>
#include <array>
#include "../Shaders/ShaderObject.hpp"

class RenderPipeline {
private:
    VkDevice device;
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
    VkVertexInputBindingDescription bindingDescription{};
    std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
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
    VkRect2D scissor{};
    VkOffset2D offset = {0, 0};


public:
    VkPipelineLayout pipelineLayout{};
    VkGraphicsPipelineCreateInfo pipelineInfo{};
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
    RenderPipeline(VkDevice device, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VkRenderPass renderPass, ShaderObject *vertShader, ShaderObject *fragShader);
};


#endif //B_OBJ_RENDERPIPELINE_HPP
