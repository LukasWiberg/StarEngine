//
// Created by ReSung on 2021-08-14.
//

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "Keyboard.hpp"
#include "../StarEngine.hpp"


Keyboard::Keyboard(Camera *camera) {
    this->camera = camera;
}

void Keyboard::KeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    StarEngine *engine = StarEngine::GetInstance();

    if(key == GLFW_KEY_W && action == GLFW_PRESS){ engine->camera->deltaForward = glm::vec3(1.0, 1.0, 1.0); }
    if(key == GLFW_KEY_S && action == GLFW_PRESS){ engine->camera->deltaForward = -glm::vec3(1.0, 1.0, 1.0); }
    if(key == GLFW_KEY_A && action == GLFW_PRESS){ engine->camera->deltaSide = -glm::vec3(1.0, 1.0, 1.0); }
    if(key == GLFW_KEY_D && action == GLFW_PRESS){ engine->camera->deltaSide = glm::vec3(1.0, 1.0, 1.0); }

    if(key == GLFW_KEY_W && action == GLFW_RELEASE){ engine->camera->deltaForward = glm::vec3(0.0, 0.0, 0.0); }
    if(key == GLFW_KEY_S && action == GLFW_RELEASE){ engine->camera->deltaForward = glm::vec3(0.0, 0.0, 0.0); }
    if(key == GLFW_KEY_A && action == GLFW_RELEASE){ engine->camera->deltaSide = glm::vec3(0.0, 0.0, 0.0);}
    if(key == GLFW_KEY_D && action == GLFW_RELEASE){ engine->camera->deltaSide = glm::vec3(0.0, 0.0, 0.0);}

    if(key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, 1);
    }
}