//
// Created by ReSung on 2021-12-31.
//

#include "MeshObject.hpp"

#include <utility>
#include "../Vulkan/Helpers/VulkanHelper.hpp"

MeshObject::MeshObject(std::vector<Vertex> vertices, std::vector<uint32_t> indices, VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool) {
    this->vertices=std::move(vertices);
    this->indices=std::move(indices);
    this->device = device;
    CreateVertexBuffer(device, physicalDevice, queue, commandPool);
    CreateIndexBuffer(device, physicalDevice, queue, commandPool);
    indexCount = this->indices.size();
}

void MeshObject::CreateVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool) {
    size_t bufferSize = sizeof(vertices[0]) * vertices.size();

    VulkanHelper::CreateBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer,
                 vertexBufferMemory);

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

void MeshObject::CreateIndexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool) {
    size_t bufferSize = sizeof(indices[0]) * indices.size();


    VulkanHelper::CreateBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                               VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    size_t stagingBufferSize = sizeof(indices[0]) * indices.size();
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    VulkanHelper::CreateBuffer(device, physicalDevice, stagingBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer,
                               stagingBufferMemory);

    void *data;
    vkMapMemory(device, stagingBufferMemory, 0, stagingBufferSize, 0, &data);

    memcpy(data, indices.data(), stagingBufferSize);

    vkUnmapMemory(device, stagingBufferMemory);

    VulkanHelper::CopyBuffer(device, queue, commandPool, stagingBuffer, indexBuffer, stagingBufferSize, 0);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

MeshObject::~MeshObject() {
    vkDestroyBuffer(device, indexBuffer, nullptr);
    vkFreeMemory(device, indexBufferMemory, nullptr);
    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);
}