//
// Created by ReSung on 2021-09-09.
//

#ifndef B_OBJ_MATERIAL_HPP
#define B_OBJ_MATERIAL_HPP


#include "../Component.hpp"
#include "../../Shaders/ShaderObject.hpp"
#include "../../Vulkan/RenderPipeline.hpp"

class Material: public Component  {
private:
    RenderPipeline *renderPipeline;

public:
    Material(GameObject *gameObject, const char *vertPath, const char *fragPath);

};


#endif //B_OBJ_MATERIAL_HPP
