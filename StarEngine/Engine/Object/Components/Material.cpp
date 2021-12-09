//
// Created by ReSung on 2021-09-09.
//

#include "Material.hpp"
#include "../../Vulkan/RenderPipelineSingleton.hpp"

Material::Material(GameObject *gameObject, const char *vertPath, const char *fragPath)
        : Component(gameObject) {
    this->gameObject = gameObject;
    renderPipeline = RenderPipelineSingleton::AddPipeline(vertPath, fragPath);
}
