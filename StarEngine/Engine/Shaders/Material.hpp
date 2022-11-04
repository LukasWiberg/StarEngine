//
// Created by lukas on 2022-10-16.
//

#ifndef B_OBJ_MATERIALCOMPONENT_HPP
#define B_OBJ_MATERIAL_HPP

#include <vulkan/vulkan_core.h>

struct Binding {
public:
    int slot;
    int count;
    int typeInt;
    int stageFlagsInt;
    VkDescriptorType type;
    VkShaderStageFlagBits stageFlags;
    VkDescriptorSetLayoutBinding* immutableSamplers = nullptr;
};


class Material {
private:
    const char* vertShader;
    const char* fragShader;
    int bindingCount;
    Binding* bindings;
    VkDescriptorSetLayoutBinding* vkBindings;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDevice device;

public:
    explicit Material(const char *materialPath, VkDevice device);
};


#endif //B_OBJ_MATERIALCOMPONENT_HPP
