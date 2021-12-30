//
// Created by ReSung on 2021-12-27.
//

#include "Chunk.hpp"
#include "../../Engine/Object/Components/Material.hpp"
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
    uint32_t visibleFaces = 0;

    {
//        auto c = ScopedClock("Creating chunk data in: ", false, true);
        for(int x = 0; x<chunkX; x++) {
            for (int y = 0; y < chunkY; y++) {
                for (int z = 0; z < chunkZ; z++) {
                    blocks[x][y][z] = (x==8 || y%5==0)
                            ?Block::Air
                            :y>200
                                ?Block::Dirt
                                :Block::Stone;
                }
            }
        }

        for(int x = 0; x<chunkX; x++) {
            for (int y = 0; y < chunkY; y++) {
                for (int z = 0; z < chunkZ; z++) {
                    if(blocks[x][y][z]!=Block::Dirt) {
                        continue;
                    }
                    blocks[x][y][z] = (y==chunkY-1 || blocks[x][y+1][z] == Block::Air)
                            ?Block::Grass
                            :Block::Dirt;
                }
            }
        }
    }

    {
//        auto c = ScopedClock("Determining visible blocks in: ", false, true);
        MeshData m{};
        for (int x = 0; x < chunkX; x++) {
            for (int y = 0; y < chunkY; y++) {
                for (int z = 0; z < chunkZ; z++) {
                    if (blocks[x][y][z] == Block::Air) {
                        continue;
                    }
                    m.xPos = x == chunkX-1 || blocks[x + 1][y][z] == Block::Air;
                    m.xNeg = x == 0 || blocks[x - 1][y][z] == Block::Air;
                    m.yPos = y == chunkY-1 || blocks[x][y + 1][z] == Block::Air;
                    m.yNeg = y == 0 || blocks[x][y - 1][z] == Block::Air;
                    m.zPos = z == chunkZ-1 || blocks[x][y][z + 1] == Block::Air;
                    m.zNeg = z == 0 || blocks[x][y][z - 1] == Block::Air;
                    uint32_t visibleFacesDiff = m.xPos+m.xNeg+m.yPos+m.yNeg+m.zPos+m.zNeg;
                    if(visibleFacesDiff>0) {
                        visibleFaces += visibleFacesDiff;
                        m.type=blocks[x][y][z];
                        m.pos={x,y,z};
                        meshData.emplace_back(m);
                    }
                }
            }
        }
    }


    {
//        auto c = ScopedClock("Generating mesh in: ", false, true);
        //Resize only once for performance
        this->vertices.resize(visibleFaces * 4);
        this->indices.resize(visibleFaces * 6);
        indexIndex = 0;
        vertexIndex = 0;
        vertexIndexOffset = 0;

        for (auto &mesh: meshData) {
            if(mesh.xPos) {AddModelData(BlockMesh::PlaneXPos(), mesh.pos, BlockMesh::GetTextureOffset(mesh.type, FaceDirection::Side));}
            if(mesh.xNeg) {AddModelData(BlockMesh::PlaneXNeg(), mesh.pos, BlockMesh::GetTextureOffset(mesh.type, FaceDirection::Side));}
            if(mesh.yPos) {AddModelData(BlockMesh::PlaneYPos(), mesh.pos, BlockMesh::GetTextureOffset(mesh.type, FaceDirection::Top));}
            if(mesh.yNeg) {AddModelData(BlockMesh::PlaneYNeg(), mesh.pos, BlockMesh::GetTextureOffset(mesh.type, FaceDirection::Bottom));}
            if(mesh.zPos) {AddModelData(BlockMesh::PlaneZPos(), mesh.pos, BlockMesh::GetTextureOffset(mesh.type, FaceDirection::Side));}
            if(mesh.zNeg) {AddModelData(BlockMesh::PlaneZNeg(), mesh.pos, BlockMesh::GetTextureOffset(mesh.type, FaceDirection::Side));}
        }
    }
}

void Chunk::AddModelData(const ModelObject& model, glm::vec3 modelPos, glm::vec2 textureOffset) {
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
                vertex.texCoord+textureOffset);
    }
    auto d = 1;
}