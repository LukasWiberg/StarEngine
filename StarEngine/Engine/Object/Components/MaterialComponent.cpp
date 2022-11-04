//
// Created by ReSung on 2021-09-09.
//

#include "MaterialComponent.hpp"
#include "../../Vulkan/RenderPipelineSingleton.hpp"

MaterialComponent::MaterialComponent(GameObject *gameObject, const char *vertPath, const char *fragPath)
        : Component(gameObject) {
    this->gameObject = gameObject;
    renderPipeline = RenderPipelineSingleton::AddPipeline(vertPath, fragPath);
}
