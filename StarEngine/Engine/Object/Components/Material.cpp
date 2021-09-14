//
// Created by ReSung on 2021-09-09.
//

#include "Material.hpp"
#include "../../Vulkan/RenderPipelineSingleton.hpp"

Material::Material(const char* vertPath, const char* fragPath) {
    renderPipeline = RenderPipelineSingleton::AddPipeline(vertPath, fragPath);
}
