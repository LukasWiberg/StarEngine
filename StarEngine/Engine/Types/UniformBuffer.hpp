//
// Created by ReSung on 2021-08-17.
//

#ifndef STARENGINE_UNIFORMBUFFER_HPP
#define STARENGINE_UNIFORMBUFFER_HPP


#include <glm/glm.hpp>

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};


#endif //STARENGINE_UNIFORMBUFFER_HPP
