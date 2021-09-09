//
// Created by ReSung on 2021-09-09.
//

#ifndef B_OBJ_MATERIAL_HPP
#define B_OBJ_MATERIAL_HPP


#include "../Component.hpp"
#include "../../Shaders/ShaderObject.hpp"

class Material: public Component  {
public:
    Material(ShaderObject shader);

private:
    void *shaderData = nullptr;

public :
    ShaderObject shader;

};


#endif //B_OBJ_MATERIAL_HPP
