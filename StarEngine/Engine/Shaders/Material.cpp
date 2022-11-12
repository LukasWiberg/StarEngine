//
// Created by lukas on 2022-10-16.
//

#include <stdexcept>
#include "Material.hpp"
#include "json.h"
#include "../General/FileHelper.hpp"
#include "../General/Helpers.hpp"

Material::Material(const char *materialPath, VkDevice vkDevice) {
    device = vkDevice;

    std::vector<char> fileContent = FileHelper::ReadFile(materialPath);
    json_value_s* jsonRoot = json_parse(fileContent.data(), fileContent.size());
    json_object_s* jsonObject = json_value_as_object(jsonRoot);
    json_object_element_s* element = jsonObject->start;

    for(int i = 0; i < jsonObject->length; i++) {
        if(i != 0) {
            element = element->next;
        }
        if(Helpers::CompareString(element->name->string, "vertShader")) vertShader = json_value_as_string(element->value)->string;
        else if(Helpers::CompareString(element->name->string, "fragShader")) fragShader = json_value_as_string(element->value)->string;
        else if(Helpers::CompareString(element->name->string, "bindings")) {
            json_array_s *localBindings = json_value_as_array(element->value);
            bindingCount = (int) localBindings->length;
            bindings = new Binding[bindingCount];
            vkBindings = new VkDescriptorSetLayoutBinding[bindingCount];
            auto binding = localBindings->start;
            for(int j = 0; j < localBindings->length; j++) {
                if (j != 0) {
                    binding = binding->next;
                }
                auto bindingObj = json_value_as_object(binding->value);
                json_object_element_s* bindingElement = bindingObj->start;
                for(int k = 0; k<bindingObj->length; k++) {
                    if (k != 0) {
                        bindingElement = bindingElement->next;
                    }
                    if(Helpers::CompareString(bindingElement->name->string, "slot")) bindings[j].slot = std::stoi(json_value_as_number(bindingElement->value)->number);
                    else if(Helpers::CompareString(bindingElement->name->string, "count")) bindings[j].count = std::stoi(json_value_as_number(bindingElement->value)->number);
                    else if(Helpers::CompareString(bindingElement->name->string, "type")) bindings[j].typeInt = std::stoi(json_value_as_number(bindingElement->value)->number);
                    else if(Helpers::CompareString(bindingElement->name->string, "stageFlags")) bindings[j].stageFlagsInt = std::stoi(json_value_as_number(bindingElement->value)->number);
                }
                bindings[j].type = (VkDescriptorType) bindings[j].typeInt;
                bindings[j].stageFlags = (VkShaderStageFlagBits) bindings[j].stageFlagsInt;
                vkBindings[j].binding = bindings[j].slot;
                vkBindings[j].descriptorCount = bindings[j].count;
                vkBindings[j].descriptorType = bindings[j].type;
                vkBindings[j].stageFlags = bindings[j].stageFlags;
                vkBindings[j].pImmutableSamplers = nullptr;
            }
        }
    }

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = bindingCount;
    layoutInfo.pBindings = vkBindings;

    if(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}



void StarVulkan::CreateDescriptorPool() {
    std::array<VkDescriptorPoolSize, 3> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
    poolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[2].descriptorCount = static_cast<uint32_t>(swapChainImages.size());

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}


void StarVulkan::CreateDescriptorSets() {
    std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
    allocInfo.pSetLayouts = layouts.data();

    descriptorSets.resize(swapChainImages.size());
    if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < swapChainImages.size(); i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkDescriptorBufferInfo resolutionBufferInfo{};
        resolutionBufferInfo.buffer = generalDataBuffer;
        resolutionBufferInfo.offset = 0;
        resolutionBufferInfo.range = sizeof(GeneralData);

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = mainTex.textureImageView;
        imageInfo.sampler = textureSampler;

        std::array<VkWriteDescriptorSet, 3> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[2].dstSet = descriptorSets[i];
        descriptorWrites[2].dstBinding = 2;
        descriptorWrites[2].dstArrayElement = 0;
        descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[2].descriptorCount = 1;
        descriptorWrites[2].pBufferInfo = &resolutionBufferInfo;

        vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}
//endregion