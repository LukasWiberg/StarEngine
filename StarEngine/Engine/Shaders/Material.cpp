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
                auto layoutBinding = new VkDescriptorSetLayoutBinding();
                vkBindings[j].binding = bindings[j].slot;
                vkBindings[j].descriptorCount = bindings[j].count;
                vkBindings[j].descriptorType = bindings[j].type;
                vkBindings[j].stageFlags = bindings[j].stageFlags;
                vkBindings[j].pImmutableSamplers = nullptr;
            }
        }
    }

    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutBinding samplerLayoutBinding{};
    samplerLayoutBinding.binding = 1;
    samplerLayoutBinding.descriptorCount = 1;
    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    samplerLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutBinding resLayoutBinding{};
    resLayoutBinding.binding = 2;
    resLayoutBinding.descriptorCount = 1;
    resLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    resLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    resLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutBinding bc[3] = {uboLayoutBinding, samplerLayoutBinding, resLayoutBinding};

    VkDescriptorSetLayoutCreateInfo li{};
    li.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    li.bindingCount = 3;
    li.pBindings = bc;


    if(vkCreateDescriptorSetLayout(device, &li, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = bindingCount;
    layoutInfo.pBindings = vkBindings;

    if(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}
