//
// Created by ReSung on 2021-08-15.
//

#ifndef STARENGINE_VERTEX_HPP
#define STARENGINE_VERTEX_HPP

#include <glm/glm.hpp>
#include <array>
#include <vulkan/vulkan_core.h>

struct Vertex {
    glm::vec3 pos{};
    glm::vec3 color{};
    glm::vec2 texCoord{};

    Vertex(const glm::vec3 &pos, const glm::vec3 &color, const glm::vec2 &texCoord);

    Vertex() = default;

    static VkVertexInputBindingDescription GetBindingDescription();

    static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions();

    bool operator==(const Vertex& other) const;
};

#endif //STARENGINE_VERTEX_HPP
