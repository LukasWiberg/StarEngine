//
// Created by ReSung on 2021-08-21.
//

#include "GameObject.hpp"

#include <utility>
#include <glm/gtx/euler_angles.hpp>
#include <algorithm>
#include <iostream>

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation) {
    this->position = position;
    this->rotation = rotation;
    UpdateTransform();
}

GameObject::GameObject(GameObject *gameObject) {
    this->position = gameObject->position;
    this->rotation = gameObject->rotation;
    UpdateTransform();
}

void GameObject::UpdateTransform() {
    glm::vec3 rotRads = glm::radians(rotation);
    glm::mat4 rot = glm::eulerAngleXYZ(rotRads.x, rotRads.y, rotRads.z);
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    this->transform = rot * glm::inverse(trans);
}

void GameObject::LogicUpdate(double frameTime) {
//    this->position += glm::vec3((((float)rand()/RAND_MAX)-0.5f)*frameTime*5, (((float)rand()/RAND_MAX)-0.5f)*frameTime*5, (((float)rand()/RAND_MAX)-0.5f)*frameTime*5);
//    this->rotation = glm::vec3(std::clamp(this->rotation.x+(((float)rand()/RAND_MAX)-0.5f)*(float)frameTime*50.0f, 0.0f, 360.0f), 0.0f, 0.0f);
}

void GameObject::GraphicsUpdate(double frameTime) {
}

