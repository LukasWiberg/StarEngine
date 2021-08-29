//
// Created by ReSung on 2021-08-21.
//

#ifndef STARENGINE_GAMEOBJECT_HPP
#define STARENGINE_GAMEOBJECT_HPP


#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../General/ModelHelper.hpp"
#include "Component.hpp"

class GameObject {
private:
    std::vector<Component> components;

public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    ModelObject model;
    glm::mat4 transform{};

    void UpdateTransform();

    GameObject(glm::vec3 position, glm::vec3 rotation, ModelObject model);
    GameObject(glm::vec3 position, glm::vec3 rotation);
    explicit GameObject(GameObject *gameObject);
    GameObject() = default;

    void LogicUpdate(double frameTime);
    void GraphicsUpdate(double frameTime);

};


#endif //STARENGINE_GAMEOBJECT_HPP
