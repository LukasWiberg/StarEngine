//
// Created by ReSung on 2021-08-17.
//

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobj_loader.h>
#include <glm/glm.hpp>
#include <iostream>
#include "ModelHelper.hpp"

ModelObject* ModelHelper::LoadModel(const std::string& modelPath) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
        throw std::runtime_error(warn + err);
    }

    auto *ret = new ModelObject();
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            ret->vertices.emplace_back(Vertex{glm::vec3(attrib.vertices[3 * index.vertex_index + 0],attrib.vertices[3 * index.vertex_index + 1],attrib.vertices[3 * index.vertex_index + 2]),
                                     glm::vec3(1.0f,1.0f,1.0f),
                                     glm::vec2(attrib.texcoords[2 * index.texcoord_index + 0], 1.0f - attrib.texcoords[2 * index.texcoord_index + 1])});
            ret->indices.push_back(ret->indices.size());
        }
    }

    return ret;
}

ModelObject ModelHelper::CopyModel(ModelObject *model) {
    ModelObject ret{};
    ret.vertices = model->vertices;
    ret.indices = model->indices;
    return ret;
}

ModelObject ModelHelper::CopyModel(ModelObject &model) {
    ModelObject ret{};
    ret.vertices = model.vertices;
    ret.indices = model.indices;
    return ret;
}

ModelObject* ModelHelper::CreateCube() {
    auto *ret = new ModelObject();

    float texX = 0.0f;
    float texY = 0.0f;

    ret->vertices.resize(24);
    //Side 1
    ret->vertices[0] = Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)};
    ret->vertices[1] = Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)};
    ret->vertices[2] = Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)};
    ret->vertices[3] = Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)};

    //Side 2
    ret->vertices[4] = Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)};
    ret->vertices[5] = Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)};
    ret->vertices[6] = Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)};
    ret->vertices[7] = Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)};

    //Side 3
    ret->vertices[8] = Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)};
    ret->vertices[9] = Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)};
    ret->vertices[10] = Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)};
    ret->vertices[11] = Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX+ 0.05, texY)};

    //Side 4
    ret->vertices[12] = Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)};
    ret->vertices[13] = Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)};
    ret->vertices[14] = Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)};
    ret->vertices[15] = Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)};

    //Top
    ret->vertices[16] = Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)};
    ret->vertices[17] = Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)};
    ret->vertices[18] = Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)};
    ret->vertices[19] = Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)};

    //Bottom
    ret->vertices[20] = Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)};
    ret->vertices[21] = Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)};
    ret->vertices[22] = Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)};
    ret->vertices[23] = Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)};



    ret->indices = {
            1, 2, 0,        //Side 1
            1, 3, 2,
            4, 5, 7,        //Side 2
            4, 7, 6,
            11, 8, 10,      //Side 3
            11, 9, 8,
            14, 13, 12,     //Side 4
            14, 15, 13,
            16, 19, 18,     //Top
            16, 17, 19,
            23, 21, 20,     //Bottom
            23, 20, 22,
    };

    return ret;
}