//
// Created by ReSung on 2021-12-27.
//

#include "Chunk.hpp"
#include "../../Engine/Object/Components/Material.hpp"
#include "../../Engine/Object/Components/Mesh.hpp"
#include "../../Engine/General/ScopedClock.hpp"
#include "../Block/BlockMesh.hpp"

struct MeshData {
    glm::vec3 pos;
    Block type;
    bool xPos = false, xNeg = false, zPos = false, zNeg = false, yPos = false, yNeg = false;

    std::vector<ModelObject> models;
};

Chunk::Chunk(glm::vec3 pos) {
    this->pos = pos;
    std::vector<MeshData> meshData;

    {
//        auto c = ScopedClock("Creating chunk data in: ", false, true);
        for(int x = 0; x<chunkX; x++) {
            for (int y = 0; y < chunkY; y++) {
                for (int z = 0; z < chunkZ; z++) {
                    blocks[x][y][z] = x==8?Block::Air:y>30?Block::Dirt:Block::Stone;
                }
            }
        }
    }

    {
//        auto c = ScopedClock("Determining visible blocks in: ", false, true);
        for (int x = 0; x < chunkX; x++) {
            for (int y = 0; y < chunkY; y++) {
                for (int z = 0; z < chunkZ; z++) {
                    if (blocks[x][y][z] == Block::Air) {
                        continue;
                    }
                    MeshData m{};
                    m.xPos = x == chunkX-1 || blocks[x + 1][y][z] == Block::Air;
                    m.xNeg = x == 0 || blocks[x - 1][y][z] == Block::Air;
                    m.yPos = y == chunkY-1 || blocks[x][y + 1][z] == Block::Air;
                    m.yNeg = y == 0 || blocks[x][y - 1][z] == Block::Air;
                    m.zPos = z == chunkY-1 || blocks[x][y][z + 1] == Block::Air;
                    m.zNeg = z == 0 || blocks[x][y][z - 1] == Block::Air;

//                    bool xVisible = x == 0 || x == chunkX - 1 || blocks[x - 1][y][z] == Block::Air ||
//                                    blocks[x + 1][y][z] == Block::Air;
//                    bool yVisible = y == 0 || y == chunkY - 1 || blocks[x][y - 1][z] == Block::Air ||
//                                    blocks[x][y + 1][z] == Block::Air;
//                    bool zVisible = z == 0 || z == chunkZ - 1 || blocks[x][y][z - 1] == Block::Air ||
//                                    blocks[x][y][z + 1] == Block::Air;

                    if(m.xPos||m.xNeg||m.yPos||m.yNeg||m.zPos||m.zNeg) {
                        m.type=blocks[x][y][z];
                        m.pos={x,y,z};
                        meshData.emplace_back(m);
//                    std::cout << "Visible: (" << x << "," << y << "," << z << ")" << std::endl;
                    }
                }
            }
        }
    }


    {
//        auto c = ScopedClock("Generating mesh in: ", false, true);
        for (auto &mesh: meshData) {
            if(mesh.xPos) {AddModelData(BlockMesh::PlaneXPos(), mesh.pos);}
            if(mesh.xNeg) {AddModelData(BlockMesh::PlaneXNeg(), mesh.pos);}
            if(mesh.yPos) {AddModelData(BlockMesh::PlaneYPos(), mesh.pos);}
            if(mesh.yNeg) {AddModelData(BlockMesh::PlaneYNeg(), mesh.pos);}
            if(mesh.zPos) {AddModelData(BlockMesh::PlaneZPos(), mesh.pos);}
            if(mesh.zNeg) {AddModelData(BlockMesh::PlaneZNeg(), mesh.pos);}
        }
    }
}

void Chunk::AddModelData(const ModelObject& model, glm::vec3 modelPos) {
    this->vertices.resize(this->vertices.size() + model.vertices.size());
    this->indices.resize(this->indices.size() + model.indices.size());

    for (unsigned int index: model.indices) {
        this->indices[indexIndex++] = vertexIndexOffset + index;
    }
    vertexIndexOffset += (int) model.vertices.size();
    for (auto &vertex: model.vertices) {
        this->vertices[vertexIndex++] = Vertex(
                vertex.pos + modelPos + glm::vec3(
                        (pos.x * chunkX),
                        (pos.y * chunkY),
                        (pos.z * chunkZ)
                ),
                vertex.color,
                vertex.texCoord);
    }
    auto d = 1;
}