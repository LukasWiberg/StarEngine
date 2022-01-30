//
// Created by ReSung on 2022-01-05.
//

#ifndef B_OBJ_MESHHELPER_HPP
#define B_OBJ_MESHHELPER_HPP


#include "glm/vec3.hpp"

class MeshHelper {
public:
    static glm::vec3 InterpolateVertices(glm::vec3 v1, glm::vec3 v2, float along = 0.5);
};


#endif //B_OBJ_MESHHELPER_HPP
