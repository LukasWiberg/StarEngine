//
// Created by ReSung on 2021-12-13.
//

#include "Mandir.hpp"
#include "../Engine/General/ScopedClock.hpp"
#include "Block/BlockMesh.hpp"


Mandir::Mandir(StarEngine* pEngine) {
    this->engine = pEngine;
    int chunksDiameter = 2;
    {
        ScopedClock c = ScopedClock(" ", false, true);
        int chunkCount = 0;
        for(int x = -chunksDiameter; x<=chunksDiameter; x++) {
            for(int z = -chunksDiameter; z <= chunksDiameter; z++) {
                chunks.push_back(new Chunk(glm::vec3(x, -1, z)));
                chunkCount++;
            }
        }
        std::cout << "Created "<< chunkCount << " chunks in:";
    }

    {
        ScopedClock c = ScopedClock("Adding vertex and index lists in: ", false, true);
        uint64_t t = 0;
        for(auto& chunk : chunks) {
            this->engine->AddVertexList(chunk->vertices);
            this->engine->AddIndexList(chunk->indices);
            t+=chunk->indices.size();
        }
    }

    {
        ScopedClock c = ScopedClock("RecreateMeshBuffers in: ", false, true);
        this->engine->RecreateMeshBuffers();
    }
}


void Mandir::Update(double frameTime) {
//    std::cout << "Update" << std::endl;
}

void Mandir::PhysicsUpdate(double frameTime) {
//    std::cout << "PhysicsUpdate" << std::endl;
}