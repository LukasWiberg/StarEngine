//
// Created by ReSung on 2021-08-28.
//

#ifndef STARENGINE_COMPONENT_HPP
#define STARENGINE_COMPONENT_HPP
class Component;
#include "GameObject.hpp"

class Component {
public:
    int id;
    GameObject *gameObject;

    explicit Component(GameObject *gameObject);

};


#endif //STARENGINE_COMPONENT_HPP
