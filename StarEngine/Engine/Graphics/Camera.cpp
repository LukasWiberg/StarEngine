//
// Created by ReSung on 2021-08-14.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera.hpp"


Camera::Camera(float cameraSpeed) {
    this->cameraSpeed = cameraSpeed;
    UpdateCamera(0);
}

void Camera::ReCalculateCameraFront() {
    cameraFront[0] = cosf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));
    cameraFront[1] = -sinf(glm::radians(this->pitch));
    cameraFront[2] = sinf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));
    cameraFront = glm::normalize(cameraFront);
};

void Camera::UpdateCamera(double delta) {
    ReCalculateCameraFront();
    glm::vec3 forwardMovement = ((float)(delta*cameraSpeed))*cameraFront*(deltaForward+deltaBack);
    if(boost) {
        forwardMovement *= boostMultiplier;
    }
    cameraPos += forwardMovement;

    glm::vec3 sideMovement = glm::normalize(glm::cross(cameraFront, cameraUp))*((float)(delta*cameraSpeed))*(deltaLeft+deltaRight);
    if(boost) {
        sideMovement *= boostMultiplier;
    }
    cameraPos += sideMovement;

    view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
}
