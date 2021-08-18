//
// Created by ReSung on 2021-08-17.
//

#include <cstdint>
#include "../Types/Vertex.hpp"

#ifndef STARENGINE_MODELHELPER_HPP
#define STARENGINE_MODELHELPER_HPP

#endif //STARENGINE_MODELHELPER_HPP

struct ModelObject {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

class ModelHelper {
public:
    static ModelObject LoadModel(const std::string& modelPath);
};