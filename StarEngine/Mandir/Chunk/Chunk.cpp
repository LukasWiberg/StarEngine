//
// Created by ReSung on 2021-12-27.
//

#include "Chunk.hpp"
#include "../../Engine/Object/Components/Material.hpp"
#include "../../Engine/Object/Components/Mesh.hpp"

Chunk::Chunk(glm::vec2 pos) {
    ModelObject* model = ModelHelper::CreateCube();
    blocks[0] = new GameObject();
    Material* mat = blocks[0]->AddComponent(new Material(blocks[0], "Resources/Shaders/a-vert.spv", "Resources/Shaders/a-frag.spv"));
    auto* mesh = new Mesh(blocks[0], model, Mesh::MeshCopyMode::Reference);
    Mesh* meshRef = blocks[0]->AddComponent<Mesh>(mesh);

    this->vertices.resize(mesh->model->vertices.size()*chunkX*chunkY*chunkZ);
    this->indices.resize(mesh->model->indices.size()*chunkX*chunkY*chunkZ);
    int i = 1;
    int indexIndex = 0;
    int vertexIndex = 0;
    int vertexIndexOffset = mesh->model->vertices.size();
    for(int j = 0; j<mesh->model->indices.size(); j++) {
        this->indices[indexIndex++] = mesh->model->indices[j];
    }

    for(int j = 0; j<mesh->model->vertices.size(); j++) {
        this->vertices[vertexIndex++] = mesh->model->vertices[j];
    }

    for(int x = 0; x<chunkX; x++) {
        for(int y = 0; y<chunkY; y++) {
            for(int z = 0; z<chunkZ; z++) {
                if(x==0&&y==0&&z==0){
                    continue;
                }
                blocks[i] = new GameObject(blocks[0]);
                blocks[i]->position = glm::vec3(x,y,z);
                blocks[i]->AddComponent(new Material(blocks[0], "Resources/Shaders/a-vert.spv", "Resources/Shaders/a-frag.spv"));
                for(int j = 0; j<mesh->model->indices.size(); j++) {
                    this->indices[indexIndex++] = vertexIndexOffset + mesh->model->indices[j];
                }
                vertexIndexOffset+=mesh->model->vertices.size();
                for(int j = 0; j<mesh->model->vertices.size(); j++) {
                    this->vertices[vertexIndex++] = *new Vertex(mesh->model->vertices[j].pos+glm::vec3(x, y, z), mesh->model->vertices[j].color, mesh->model->vertices[j].texCoord);
                }
                i++;
            }
        }
    }
}
