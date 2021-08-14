//
// Created by ReSung on 2021-08-14.
//

#ifndef STARENGINE_KEYBOARD_HPP
#define STARENGINE_KEYBOARD_HPP


#include "../Graphics/Camera.hpp"

class Keyboard {
private:
    Camera *camera;
public:
    explicit Keyboard(Camera *camera);
    static void KeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};


#endif //STARENGINE_KEYBOARD_HPP
