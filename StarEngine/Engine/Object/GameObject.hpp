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
    std::vector<void*> components;
    std::vector<const char*> componentTypes;

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
    T* AddComponent(T* component) {
        this->components.push_back(component);
        this->componentTypes.push_back(typeid(T).name());
        return component;
    }

    template<class T>
    T* GetComponent() {
        int i = 0;
        for(auto componentType : componentTypes) {
            if(typeid(T).name()==componentType) {
                return static_cast<T*>(components[i]);
            }
            i++;
        }
        return nullptr;
    }

};


#endif //STARENGINE_GAMEOBJECT_HPP
