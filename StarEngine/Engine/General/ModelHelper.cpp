//
// Created by ReSung on 2021-08-17.
//

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobj_loader.h>
#include <glm/glm.hpp>
#include "ModelHelper.hpp"

ModelObject ModelHelper::LoadModel(const std::string& modelPath) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    std::vector<struct Vertex> vertexBuffer;
    std::vector<uint32_t> indexBuffer;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
        throw std::runtime_error(warn + err);
    }


    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            struct Vertex vertex{};

            vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 1.0f, 1.0f};


            vertexBuffer.push_back(vertex);
            indexBuffer.push_back(indexBuffer.size());
        }
    }
    ModelObject ret{};

    ret.vertices = vertexBuffer;
    ret.indices = indexBuffer;
    std::printf("ayo3: %d", ret.vertices.size());
    std::printf("ayo4: %d", ret.indices.size());
    return ret;
}