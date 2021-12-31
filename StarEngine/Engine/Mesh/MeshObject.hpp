//
// Created by ReSung on 2021-12-31.
//

#ifndef B_OBJ_MESHOBJECT_HPP
#define B_OBJ_MESHOBJECT_HPP


#include <vulkan/vulkan_core.h>
#include <vector>
#include "../Types/Vertex.hpp"

class MeshObject {
private:
    void CreateVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool);
    void CreateIndexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool);

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

    VkDeviceMemory indexBufferMemory = VK_NULL_HANDLE;

    VkDevice device = VK_NULL_HANDLE;

public:
    MeshObject(std::vector<Vertex> vertices, std::vector<uint32_t> indices, VkDevice device,
               VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool);
    ~MeshObject();

    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    size_t indexCount;
};


#endif //B_OBJ_MESHOBJECT_HPP
