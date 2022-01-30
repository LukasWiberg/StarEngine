//
// Created by ReSung on 2021-12-27.
//

#include "Chunk.hpp"
#include "../../Engine/General/ScopedClock.hpp"
#include "../Block/BlockMesh.hpp"
#include "../../Libraries/TriangulationTable.cpp"
#include "../../Engine/Mesh/MeshHelper.hpp"

Chunk::Chunk(NoiseObject* noiseObject,  glm::vec3 pos) {
    this->pos = pos;
    double chunkBlockHeightRatio = 0.8;
    for(int x = 0; x<chunkX; x++) {
        for (int z = 0; z < chunkZ; z++) {
            double blockHeightMod = noiseObject->Sample2D((pos.x/10)+((float)x/(chunkX*10)), (pos.z/10)+((float)z/(chunkZ*10)));
            double blockHeight = blockHeightMod*chunkBlockHeightRatio*chunkY;

            for (int y = 0; y < chunkY; y++) {
                blocks[x][y][z] = y>blockHeight
                        ?Block::Air
                        :y>(blockHeight-5)
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


    GenerateMesh();
//    GenerateMarchingCubes();
//    std::cout << "Vertices: [";
//    for(auto v : this->vertices) {
//        std::cout << "(" << v.pos.x << "," << v.pos.y << "," << v.pos.z << ")";
//    }
//    std::cout << "]" << std::endl;
//    std::cout << "Indices: [";
//    for(auto i : this->indices) {
//        std::cout << i << ", ";
//    }
//    std::cout << "]" << std::endl;
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
}

void Chunk::GenerateMesh() {
    {
//        auto c = ScopedClock("Determining visible blocks in: ", false, true);
        MeshData m{};
        for (int x = 0; x < chunkX; x++) {
            for (int y = 0; y < chunkY; y++) {
                for (int z = 0; z < chunkZ; z++) {
                    if (blocks[x][y][z] == Block::Air) {
                        continue;
                    }
                    m.xPos = x != chunkX - 1 && (blocks[x + 1][y][z] == Block::Air);
                    m.xNeg = x != 0 && (blocks[x - 1][y][z] == Block::Air);
                    m.yPos = y != chunkY - 1 && (blocks[x][y + 1][z] == Block::Air);
                    m.yNeg = y != 0 && (blocks[x][y - 1][z] == Block::Air);
                    m.zPos = z != chunkZ - 1 && -(blocks[x][y][z + 1] == Block::Air);
                    m.zNeg = z != 0 && (blocks[x][y][z - 1] == Block::Air);
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
//    auto c = ScopedClock("Generating mesh in: ", false, true);
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

void Chunk::GenerateMarchingCubes() {
    MeshData m{};
//    this->vertices.resize(visibleFaces * 4);
//    this->indices.resize(visibleFaces * 6);
//    uint32_t triangleOffset = 0;
//    for (int x = 0; x < chunkX; x++) {
//        for (int y = 0; y < chunkY; y++) {
//            for (int z = 0; z < chunkZ; z++) {
//                glm::vec3 corners[8] = {
//                        {x,y,z},
//                        {x+1,y,z},
//                        {x+1,y,z+1},
//                        {x,y,z+1},
//                        {x,y+1,z},
//                        {x+1,y+1,z},
//                        {x+1,y+1,z+1},
//                        {x,y+1,z+1}
//                };
//                uint32_t triangulationIndex = 0;
//                for(int i = 0; i<8; i++) {
//                    bool solid = blocks[(int)corners[i].x][(int)corners[i].y][(int)corners[i].z]!=Block::Air;
//                    if(solid) {
//                        triangulationIndex += (uint32_t)pow(2, i);
//                    }
//                }
//                for (int i = 0; triangulation[triangulationIndex][i] != -1; i +=3) {
//                    int a0 = cornerIndexAFromEdge[triangulation[triangulationIndex][i]];
//                    int b0 = cornerIndexBFromEdge[triangulation[triangulationIndex][i]];
//
//                    int a1 = cornerIndexAFromEdge[triangulation[triangulationIndex][i + 1]];
//                    int b1 = cornerIndexBFromEdge[triangulation[triangulationIndex][i + 1]];
//
//                    int a2 = cornerIndexAFromEdge[triangulation[triangulationIndex][i + 2]];
//                    int b2 = cornerIndexBFromEdge[triangulation[triangulationIndex][i + 2]];
//
//                    //TODO Replace color with a proper value, now just use 1,1,1
//                    //TODO Block is currently incorrect, need a smart way to determine what block should be used for the texture, for now just grass
//                    auto a = MeshHelper::InterpolateVertices(corners[a0], corners[b0], 0.5f);
//                    auto b = MeshHelper::InterpolateVertices(corners[a1], corners[b1], 0.5f);
//                    auto c = MeshHelper::InterpolateVertices(corners[a2], corners[b2], 0.5f);
//                    this->vertices.emplace_back(MeshHelper::InterpolateVertices(corners[a0], corners[b0], 0.5f),
//                                                glm::vec3(1, 1, 1), BlockMesh::GetTextureOffset(
//                                    Block::Grass,
//                                    FaceDirection::Side));
//                    this->vertices.emplace_back(MeshHelper::InterpolateVertices(corners[a2], corners[b1], 0.5f),
//                                                glm::vec3(1, 1, 1), BlockMesh::GetTextureOffset(
//                                    Block::Grass,
//                                    FaceDirection::Side));
//                    this->vertices.emplace_back(MeshHelper::InterpolateVertices(corners[a1], corners[b2], 0.5f),
//                                                glm::vec3(1, 1, 1), BlockMesh::GetTextureOffset(
//                                    Block::Grass,
//                                    FaceDirection::Side));
//
//                    this->indices.emplace_back(a0+triangleOffset);
//                    this->indices.emplace_back(a1+triangleOffset);
//                    this->indices.emplace_back(a2+triangleOffset);
//                    this->indices.emplace_back(b0+triangleOffset);
//                    this->indices.emplace_back(b1+triangleOffset);
//                    this->indices.emplace_back(b2+triangleOffset);
//                }
//                triangleOffset=this->vertices.size();
//            }
//        }
//    }



    glm::vec3 corners[8] = {
        {0,0,0},
        {1,0,0},
        {1,0,1},
        {0,0,1},
        {0,1,0},
        {1,1,0},
        {1,1,1},
        {0,1,1}
    };
    uint32_t triangulationIndex = 1;
//
//    for(int i = 0; i<8; i++) {
//        bool solid = blocks[(int)corners[i].x][(int)corners[i].y][(int)corners[i].z]!=Block::Air;
//        if(solid) {
//            triangulationIndex += (uint32_t)pow(2, i);
//        }
//    }
    for (int i = 0; triangulation[triangulationIndex][i] != -1; i +=3) {
        int a0 = cornerIndexAFromEdge[triangulation[triangulationIndex][i]];
        int b0 = cornerIndexBFromEdge[triangulation[triangulationIndex][i]];

        int a1 = cornerIndexAFromEdge[triangulation[triangulationIndex][i + 1]];
        int b1 = cornerIndexBFromEdge[triangulation[triangulationIndex][i + 1]];

        int a2 = cornerIndexAFromEdge[triangulation[triangulationIndex][i + 2]];
        int b2 = cornerIndexBFromEdge[triangulation[triangulationIndex][i + 2]];

        //TODO Replace color with a proper value, now just use 1,1,1
        //TODO Block is currently incorrect, need a smart way to determine what block should be used for the texture, for now just grass
        auto a = MeshHelper::InterpolateVertices(corners[a0], corners[b0], 0.5f);
        auto b = MeshHelper::InterpolateVertices(corners[a1], corners[b1], 0.5f);
        auto c = MeshHelper::InterpolateVertices(corners[a2], corners[b2], 0.5f);
        this->vertices.emplace_back(MeshHelper::InterpolateVertices(corners[a0], corners[b0], 0.5f),
                                    glm::vec3(1, 1, 1), BlockMesh::GetTextureOffset(
                        Block::Grass,
                        FaceDirection::Side));
        this->vertices.emplace_back(MeshHelper::InterpolateVertices(corners[a2], corners[b1], 0.5f),
                                    glm::vec3(1, 1, 1), BlockMesh::GetTextureOffset(
                        Block::Grass,
                        FaceDirection::Side));
        this->vertices.emplace_back(MeshHelper::InterpolateVertices(corners[a1], corners[b2], 0.5f),
                                    glm::vec3(1, 1, 1), BlockMesh::GetTextureOffset(
                        Block::Grass,
                        FaceDirection::Side));

        this->indices.emplace_back(a0);
        this->indices.emplace_back(a1);
        this->indices.emplace_back(a2);
        this->indices.emplace_back(b0);
        this->indices.emplace_back(b1);
        this->indices.emplace_back(b2);
    }
}