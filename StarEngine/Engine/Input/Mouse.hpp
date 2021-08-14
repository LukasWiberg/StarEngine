//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_MOUSE_HPP
#define STARENGINE_MOUSE_HPP


#include "../Graphics/Camera.hpp"

class Mouse {
private:
    Camera *camera;
public:
    explicit Mouse(Camera *camera);
    static void MouseInput(GLFWwindow* window, double xPos, double yPos);
};


#endif //STARENGINE_MOUSE_HPP
