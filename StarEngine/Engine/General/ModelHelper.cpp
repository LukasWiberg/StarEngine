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
    float texY = 0.05f;

    //Side 1
    ret->vertices.emplace_back(Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)});

    //Side 2
    ret->vertices.emplace_back(Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)});
    ret->vertices.emplace_back(Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)});

    //Side 3
    ret->vertices.emplace_back(Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX+ 0.05, texY)});

    //Side 4
    ret->vertices.emplace_back(Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)});

    texY = 0.00f;

    //Top
    ret->vertices.emplace_back(Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)});

    texY = 0.1f;

    //Bottom
    ret->vertices.emplace_back(Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY + 0.05)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX + 0.05, texY)});
    ret->vertices.emplace_back(Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(texX, texY)});



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

    std::cout << ret->indices.size() << std::endl;
    std::cout << ret->vertices.size() << std::endl;
    return ret;
}