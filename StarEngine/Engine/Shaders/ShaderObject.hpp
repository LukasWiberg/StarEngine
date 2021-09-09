//
// Created by ReSung on 2021-08-21.
//

#ifndef STARENGINE_SHADEROBJECT_HPP
#define STARENGINE_SHADEROBJECT_HPP


#include <vector>
#include <vulkan/vulkan_core.h>
#include <string>

class ShaderObject {
private:
    VkDevice device;
    std::string path;
    std::vector<char> byteCode;

public:
    VkShaderModule shaderModule = nullptr;

    ShaderObject(std::string path, VkDevice device);
    static VkShaderModule CreateShaderModule(VkDevice device, const uint32_t *code, uint32_t codeSize) ;

    virtual ~ShaderObject();
};


#endif //STARENGINE_SHADEROBJECT_HPP
