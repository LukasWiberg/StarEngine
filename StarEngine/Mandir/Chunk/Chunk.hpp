//
// Created by ReSung on 2021-12-27.
//

#ifndef B_OBJ_CHUNK_HPP
#define B_OBJ_CHUNK_HPP


#include "glm/vec2.hpp"
#include "../../Engine/Object/GameObject.hpp"
#include "../Block/Block.hpp"

class Chunk {
private:
    static const int chunkX = 16;
    static const int chunkY = 256;
    static const int chunkZ = 16;
//    GameObject* blocks[chunkX*chunkY*chunkZ]{};
    Block blocks[chunkX][chunkY][chunkZ]{};

public:
    explicit Chunk(glm::vec3 pos);
    glm::vec3 pos{};

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};


#endif //B_OBJ_CHUNK_HPP
