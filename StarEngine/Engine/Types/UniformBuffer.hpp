//
// Created by ReSung on 2021-08-17.
//

#ifndef STARENGINE_UNIFORMBUFFER_HPP
#define STARENGINE_UNIFORMBUFFER_HPP

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct PushConstantData {
    alignas(16) glm::vec3 transform;
};


#endif //STARENGINE_UNIFORMBUFFER_HPP
