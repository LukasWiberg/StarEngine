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
    glm::vec3 cameraSpeed{};

public:
    glm::vec3 deltaForward = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 deltaSide = glm::vec3(0.0f, 0.0f, 0.0f);

    float yaw = 0.0f, pitch = 0.0f;

    explicit Camera(glm::vec3 cameraSpeed = glm::vec3(0.001f, 0.001f, 0.001f));
    void ReCalculateCameraFront();
    void UpdateCamera();

    glm::mat4 view{};
};


#endif //STARENGINE_CAMERA_HPP
