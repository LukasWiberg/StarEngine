//
// Created by ReSung on 2021-12-27.
//

#include "Chunk.hpp"
#include "../../Engine/Object/Components/Material.hpp"
#include "../../Engine/Object/Components/Mesh.hpp"

Chunk::Chunk(glm::vec3 pos) {
    this->pos = pos;

    for(int x = 0; x<chunkX; x++) {
        for (int y = 0; y < chunkY; y++) {
            for (int z = 0; z < chunkZ; z++) {
                blocks[x][y][z] = x==8?Block::Air:y>30?Block::Dirt:Block::Stone;
            }
        }
    }

    std::vector<glm::vec3> visible{};
    for(int x = 0; x<chunkX; x++) {
        for (int y = 0; y < chunkY; y++) {
            for (int z = 0; z < chunkZ; z++) {
                if(blocks[x][y][z] == Block::Air) {
                    continue;
                }
                bool xVisible = x==0||x==chunkX-1||blocks[x-1][y][z]==Block::Air||blocks[x+1][y][z]==Block::Air;
                bool yVisible = y==0||y==chunkY-1||blocks[x][y-1][z]==Block::Air||blocks[x][y+1][z]==Block::Air;
                bool zVisible = z==0||z==chunkZ-1||blocks[x][y][z-1]==Block::Air||blocks[x][y][z+1]==Block::Air;
                bool b = xVisible||yVisible||zVisible;
                if(b) {
                    visible.emplace_back(x, y, z);
//                    std::cout << "Visible: (" << x << "," << y << "," << z << ")" << std::endl;
                }
            }
        }
    }
    ModelObject* model = ModelHelper::CreateCube();

    this->vertices.resize(model->vertices.size()*visible.size());
    this->indices.resize(model->indices.size()*visible.size());

    int indexIndex = 0;
    int vertexIndex = 0;
    int vertexIndexOffset = (int)model->vertices.size();
    for(auto & i : visible) {
        for(unsigned int index : model->indices) {
            this->indices[indexIndex++] = vertexIndexOffset + index;
        }
        vertexIndexOffset+=(int)model->vertices.size();
        for(auto & vertex : model->vertices) {
            this->vertices[vertexIndex++] = *new Vertex(
            vertex.pos + glm::vec3(
                (pos.x * chunkX) + i.x,
                (pos.y * chunkY) + i.y,
                (pos.z * chunkZ) + i.z
                ),
            vertex.color,
            vertex.texCoord);
        }
    }
//    for(int x = 0; x<chunkX; x++) {
//        for(int y = 0; y<chunkY; y++) {
//            for(int z = 0; z<chunkZ; z++) {
//                for(unsigned int index : mesh->model->indices) {
//                    this->indices[indexIndex++] = vertexIndexOffset + index;
//                }
//                vertexIndexOffset+=(int)mesh->model->vertices.size();
//                for(auto & vertex : mesh->model->vertices) {
//                    this->vertices[vertexIndex++] = *new Vertex(vertex.pos + glm::vec3((int)(pos.x * chunkX) + x, (int)(pos.y * chunkY) + y, (int)(pos.z * chunkZ) + z), vertex.color, vertex.texCoord);
//                }
//                i++;
//            }
//        }
//    }

}

//Chunk::Chunk(glm::vec3 pos) {
//    this->pos = pos;
//    ModelObject* model = ModelHelper::CreateCube();
//    blocks[0] = new GameObject();
//    blocks[0]->AddComponent(new Material(blocks[0], "Resources/Shaders/a-vert.spv", "Resources/Shaders/a-frag.spv"));
//    auto* mesh = new Mesh(blocks[0], model, Mesh::MeshCopyMode::Reference);
//
//    this->vertices.resize(mesh->model->vertices.size()*chunkX*chunkY*chunkZ);
//    this->indices.resize(mesh->model->indices.size()*chunkX*chunkY*chunkZ);
//    int i = 1;
//    int indexIndex = 0;
//    int vertexIndex = 0;
//    int vertexIndexOffset = (int)mesh->model->vertices.size();
//    for(unsigned int index : mesh->model->indices) {
//        this->indices[indexIndex++] = index;
//    }
//
//    for(auto & vertex : mesh->model->vertices) {
//        this->vertices[vertexIndex++] = *new Vertex(vertex.pos + glm::vec3((int)(pos.x * chunkX), (int)(pos.y * chunkY), (int)(pos.z * chunkZ)), vertex.color, vertex.texCoord);
//    }
//
//    for(int x = 0; x<chunkX; x++) {
//        for(int y = 0; y<chunkY; y++) {
//            for(int z = 0; z<chunkZ; z++) {
//                if(x==0&&y==0&&z==0){
//                    continue;
//                }
//                blocks[i] = new GameObject(blocks[0]);
//                blocks[i]->position = glm::vec3(x,y,z);
//                blocks[i]->AddComponent(new Material(blocks[0], "Resources/Shaders/a-vert.spv", "Resources/Shaders/a-frag.spv"));
//                for(unsigned int index : mesh->model->indices) {
//                    this->indices[indexIndex++] = vertexIndexOffset + index;
//                }
//                vertexIndexOffset+=(int)mesh->model->vertices.size();
//                for(auto & vertex : mesh->model->vertices) {
//                    this->vertices[vertexIndex++] = *new Vertex(vertex.pos + glm::vec3((int)(pos.x * chunkX) + x, (int)(pos.y * chunkY) + y, (int)(pos.z * chunkZ) + z), vertex.color, vertex.texCoord);
//                }
//                i++;
//            }
//        }
//    }
//}
