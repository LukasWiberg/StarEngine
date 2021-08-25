//
// Created by ReSung on 2021-08-21.
//

#include "GameObject.hpp"

#include <utility>

GameObject::GameObject(glm::vec3 position, glm::quat rotation, ModelObject model) {
    this->position = position;
    this->rotation = rotation;
    this->model = std::move(model);
    UpdateTransform();
}

GameObject::GameObject(glm::vec3 position, glm::quat rotation) {
    this->position = position;
    this->rotation = rotation;
    UpdateTransform();
}

GameObject::GameObject(GameObject *gameObject) {
    this->position = gameObject->position;
    this->rotation = gameObject->rotation;
    UpdateTransform();
    this->model = ModelHelper::CopyModel(gameObject->model);
}

void GameObject::UpdateTransform() {
    glm::mat4 rot = glm::toMat4(rotation);
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    this->transform = rot * trans;
}
