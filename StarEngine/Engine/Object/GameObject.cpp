//
// Created by ReSung on 2021-08-21.
//

#include "GameObject.hpp"

GameObject::GameObject(const glm::vec3 &position, const glm::vec3 &rotation, const ModelObject &model) : position(
        position), rotation(rotation), model(model) {

}