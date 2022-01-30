//
// Created by ReSung on 2022-01-05.
//

#include "MeshHelper.hpp"

glm::vec3 MeshHelper::InterpolateVertices(glm::vec3 v1, glm::vec3 v2, float along) {
    return v1 + ((v2-v1)*along);
}
