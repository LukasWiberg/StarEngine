//
// Created by ReSung on 2021-08-21.
//

#ifndef STARENGINE_GAMEOBJECT_HPP
#define STARENGINE_GAMEOBJECT_HPP


#include <glm/glm.hpp>
#include "../General/ModelHelper.hpp"

class GameObject {
public:
    GameObject(const glm::vec3 &position, const glm::vec3 &rotation, const ModelObject &model);

    GameObject() = default;

private:
    glm::vec3 position;
    glm::vec3 rotation;
    ModelObject model;
};


#endif //STARENGINE_GAMEOBJECT_HPP
