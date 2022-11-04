//
// Created by ReSung on 2021-09-09.
//

#ifndef B_OBJ_MATERIALCOMPONENT_HPP
#define B_OBJ_MATERIALCOMPONENT_HPP


#include "../Component.hpp"
#include "../../Shaders/ShaderObject.hpp"
#include "../../Vulkan/RenderPipeline.hpp"

class MaterialComponent: public Component  {
private:
    RenderPipeline *renderPipeline;

public:
    MaterialComponent(GameObject *gameObject, const char *vertPath, const char *fragPath);

};


#endif //B_OBJ_MATERIALCOMPONENT_HPP
