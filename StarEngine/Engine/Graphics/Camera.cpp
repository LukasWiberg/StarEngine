//
// Created by ReSung on 2021-08-14.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"

Camera::Camera(glm::vec3 cameraSpeed) {
    this->cameraSpeed = cameraSpeed;
    UpdateCamera();
}

void Camera::ReCalculateCameraFront() {
    cameraFront[0] = cosf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));
    cameraFront[1] = -sinf(glm::radians(this->pitch));
    cameraFront[2] = sinf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));
    cameraFront = glm::normalize(cameraFront);
};

void Camera::UpdateCamera() {
    ReCalculateCameraFront();

    glm::vec3 forwardMovement = cameraSpeed*cameraFront*deltaForward;
    cameraPos += forwardMovement;

    glm::vec3 sideMovement = glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed*deltaSide;
    cameraPos += sideMovement;

    view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
}
