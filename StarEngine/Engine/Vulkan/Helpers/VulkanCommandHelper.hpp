//
// Created by ReSung on 2021-12-31.
//

#ifndef B_OBJ_VULKANCOMMANDHELPER_HPP
#define B_OBJ_VULKANCOMMANDHELPER_HPP

#include <vulkan/vulkan_core.h>

class VulkanCommandHelper {
public:
    static VkCommandBuffer BeginSingleTimeCommand(VkDevice device, VkCommandPool commandPool);
    static void EndSingleTimeCommand(VkDevice device, VkCommandBuffer commandBuffer, VkCommandPool commandPool, VkQueue queue);
    static void BeginCommandBuffer(VkCommandBuffer cmdBuffer) ;
    static void EndCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue) ;
    static void CreateCommandPool(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool &commandPool, VkSurfaceKHR surface);
};


#endif //B_OBJ_VULKANCOMMANDHELPER_HPP
