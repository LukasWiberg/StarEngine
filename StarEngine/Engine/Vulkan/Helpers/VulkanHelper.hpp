//
// Created by ReSung on 2021-12-31.
//

#ifndef B_OBJ_VULKANHELPER_HPP
#define B_OBJ_VULKANHELPER_HPP

#include <vulkan/vulkan_core.h>
#include "VulkanHelperTypes.hpp"

class VulkanHelper {
public:
    static void CreateBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    static uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
    static void CopyBuffer(VkDevice device, VkQueue queue, VkCommandPool commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDeviceSize dstOffset = 0, VkDeviceSize srcOffset = 0);

    static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physDevice, VkSurfaceKHR surface);

};


#endif //B_OBJ_VULKANHELPER_HPP
