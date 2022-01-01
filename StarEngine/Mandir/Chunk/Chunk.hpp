//
// Created by ReSung on 2021-12-27.
//

#ifndef B_OBJ_CHUNK_HPP
#define B_OBJ_CHUNK_HPP


#include "glm/vec2.hpp"
#include "../../Engine/Object/GameObject.hpp"
#include "../Block/Block.hpp"
#include "../../Engine/Noise/NoiseObject.hpp"

class Chunk {
private:
    static const int chunkX = 16;
    static const int chunkY = 256;
    static const int chunkZ = 16;
    Block blocks[chunkX][chunkY][chunkZ]{};
    void AddModelData(const ModelObject& model, glm::vec3 modelPos, glm::vec2 textureOffset);
    int indexIndex = 0;
    int vertexIndex = 0;
    int vertexIndexOffset = 0;

public:
    explicit Chunk(NoiseObject* noiseObject, glm::vec3 pos);
    glm::vec3 pos{};

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};


#endif //B_OBJ_CHUNK_HPP
