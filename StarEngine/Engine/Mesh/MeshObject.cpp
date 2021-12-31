//
// Created by ReSung on 2021-12-31.
//

#include "MeshObject.hpp"
#include "../Vulkan/Helpers/VulkanHelper.hpp"

void MeshObject::CreateVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool) {
    size_t bufferSize = sizeof(vertices[0]) * vertices.size();

    VulkanHelper::CreateBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer,
                 vertexBufferMemory);

    uint64_t memoryOffset = 0;
    size_t stagingBufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    VulkanHelper::CreateBuffer(device, physicalDevice, stagingBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer,
                 stagingBufferMemory);

    void *data;
    vkMapMemory(device, stagingBufferMemory, 0, stagingBufferSize, 0, &data);
    memcpy(data, vertices.data(), stagingBufferSize);
    vkUnmapMemory(device, stagingBufferMemory);



    VulkanHelper::CopyBuffer(device, queue, commandPool, stagingBuffer, vertexBuffer, stagingBufferSize, 0);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}