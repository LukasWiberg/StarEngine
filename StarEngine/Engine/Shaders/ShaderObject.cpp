//
// Created by ReSung on 2021-08-21.
//

#include "ShaderObject.hpp"

#include <utility>
#include "../General/FileHelper.hpp"

ShaderObject::ShaderObject(std::string path, VkDevice device) {
    this->device = device;
    this->path = std::move(path);
    this->byteCode = FileHelper::ReadFile(this->path);
    this->shaderModule = CreateShaderModule(device, (const uint32_t *) this->byteCode.data(), this->byteCode.size());
}

VkShaderModule ShaderObject::CreateShaderModule(VkDevice device, const uint32_t *code, uint32_t codeSize) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = codeSize;
    createInfo.pCode = code;
    createInfo.pNext = VK_NULL_HANDLE;
    createInfo.flags = 0;

    VkShaderModule module;
    if(vkCreateShaderModule(device, &createInfo, nullptr, &module) != VK_SUCCESS) {
        printf("failed to create shader module!");
    }

    return module;
}

ShaderObject::~ShaderObject() {
    vkDestroyShaderModule(device, this->shaderModule, nullptr);
}
