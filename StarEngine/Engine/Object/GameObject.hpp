//
// Created by ReSung on 2021-08-21.
//

#ifndef STARENGINE_GAMEOBJECT_HPP
#define STARENGINE_GAMEOBJECT_HPP


#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../General/ModelHelper.hpp"

class GameObject {
private:

public:
    glm::vec3 position{};
    glm::quat rotation{};
    ModelObject model;
    glm::mat4 transform{};

    void UpdateTransform();

    GameObject(glm::vec3 position, glm::quat rotation, ModelObject model);
    GameObject(glm::vec3 position, glm::quat rotation);
    explicit GameObject(GameObject *gameObject);
    GameObject() = default;
};


#endif //STARENGINE_GAMEOBJECT_HPP
