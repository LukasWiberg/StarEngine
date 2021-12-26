//
// Created by ReSung on 2021-08-17.
//

#include <cstdint>
#include <vector>
#include "../Types/Vertex.hpp"

#ifndef STARENGINE_MODELHELPER_HPP
#define STARENGINE_MODELHELPER_HPP

struct ModelObject {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

class ModelHelper {
public:
    static ModelObject* LoadModel(const std::string& modelPath);
    static ModelObject CopyModel(ModelObject &model);
    static ModelObject CopyModel(ModelObject *model);
    static ModelObject* CreateCube();
};

#endif //STARENGINE_MODELHELPER_HPP