//
// Created by ReSung on 2021-08-21.
//

#include "GameObject.hpp"

#include <utility>

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, ModelObject model) {
    this->position = position;
    this->rotation = rotation;
    this->model = std::move(model);
    std::printf("1: %d\n", this->model.vertices.size());
    std::printf("2: %d\n", this->model.indices.size());

    for(auto &vertex : this->model.vertices) {
        vertex.pos += position;
    }
}

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation) {
    this->position = position;
    this->rotation = rotation;
}