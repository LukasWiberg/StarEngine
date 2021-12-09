//
// Created by ReSung on 2021-08-21.
//

#ifndef STARENGINE_GAMEOBJECT_HPP
#define STARENGINE_GAMEOBJECT_HPP


#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "../General/ModelHelper.hpp"
class GameObject;
#include "Component.hpp"

class GameObject {
private:
    std::vector<Component*> components;

public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::mat4 transform{};

    void UpdateTransform();

    GameObject(glm::vec3 position, glm::vec3 rotation);
    explicit GameObject(GameObject *gameObject);
    GameObject() = default;

    void LogicUpdate(double frameTime);
    void GraphicsUpdate(double frameTime);


    template<class T>
    T* AddComponent(T *component) {
        this->components.push_back(component);
        return component;
    }

    template<class T>
    T* GetComponent() {
        for(auto component : components) {
            if(typeid(T).name()==typeid(*component).name()) {
                auto a = static_cast<T*>(component);
                return a;
            } else {
            }
        }
        throw std::runtime_error("No component with specified name found");
    }

};


#endif //STARENGINE_GAMEOBJECT_HPP
