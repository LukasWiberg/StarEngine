//
// Created by ReSung on 2021-12-27.
//

#ifndef B_OBJ_CHUNK_HPP
#define B_OBJ_CHUNK_HPP


#include "glm/vec2.hpp"
#include "../../Engine/Object/GameObject.hpp"
#include "../Block/Block.hpp"
#include "../../Engine/Noise/NoiseObject.hpp"

struct MeshData {
    glm::vec3 pos;
    Block type;
    bool xPos = false, xNeg = false, zPos = false, zNeg = false, yPos = false, yNeg = false;
};

class Chunk {
private:
    static const int chunkX = 16;
    static const int chunkY = 256;
    static const int chunkZ = 16;
    Block blocks[chunkX][chunkY][chunkZ]{};
    uint32_t indexIndex = 0;
    uint32_t vertexIndex = 0;
    uint32_t vertexIndexOffset = 0;
    uint32_t visibleFaces = 0;
    std::vector<MeshData> meshData;


    void AddModelData(const ModelObject& model, glm::vec3 modelPos, glm::vec2 textureOffset);
    void GenerateMesh();
    void GenerateMarchingCubes();

public:
    explicit Chunk(NoiseObject* noiseObject, glm::vec3 pos);
    glm::vec3 pos{};

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Vertex> marchingVertices;
    std::vector<uint32_t> marchingIndices;
};


#endif //B_OBJ_CHUNK_HPP
