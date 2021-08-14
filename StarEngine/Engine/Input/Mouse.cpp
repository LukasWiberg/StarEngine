//
// Created by ReSung on 2021-08-14.
//

#include <GLFW/glfw3.h>
#include "Mouse.hpp"
#include "../Constants.hpp"
#include "../StarEngine.hpp"


Mouse::Mouse(Camera *camera) {
    this->camera = camera;
}

void Mouse::MouseInput(GLFWwindow* window, double xPos, double yPos) {
    StarEngine *engine = StarEngine::GetInstance();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window, &xPos, &yPos);
    glfwSetCursorPos(window, (float)WINDOW_WIDTH/2, (float)WINDOW_HEIGHT/2);

    float xOffset;
    float yOffset;

    xOffset = ((float)xPos - (float)WINDOW_WIDTH / 2);
    yOffset = ((float)yPos - (float)WINDOW_HEIGHT / 2);

    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    engine->camera->yaw += xOffset;
    engine->camera->pitch += yOffset;


    if(engine->camera->pitch > 89.0f)
        engine->camera->pitch = 89.0f;
    if(engine->camera->pitch < -89.0f)
        engine->camera->pitch = -89.0f;

    engine->camera->ReCalculateCameraFront();
}
