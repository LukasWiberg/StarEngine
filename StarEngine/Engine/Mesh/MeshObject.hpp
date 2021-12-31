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
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
};


#endif //B_OBJ_MESHOBJECT_HPP
