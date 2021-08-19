//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_CAMERA_HPP
#define STARENGINE_CAMERA_HPP


#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  0.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
    float cameraSpeed = 0.001f;
    float boostMultiplier = 5.0f;

public:
    glm::vec3 deltaForward = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 deltaBack = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 deltaRight = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 deltaLeft = glm::vec3(0.0f, 0.0f, 0.0f);
    bool boost = false;

    float yaw = 0.0f, pitch = 0.0f;

    explicit Camera(float cameraSpeed = 0.001f);
    void ReCalculateCameraFront();
    void UpdateCamera(double delta);

    glm::mat4 view{};
};


#endif //STARENGINE_CAMERA_HPP
