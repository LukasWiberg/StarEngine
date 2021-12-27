//
// Created by ReSung on 2021-12-13.
//

#include "Mandir.hpp"
#include "../Engine/General/ScopedClock.hpp"


Mandir::Mandir(StarEngine* pEngine) {
    this->engine = pEngine;
    {
        ScopedClock c = ScopedClock("Created new chunks in: ", false, true);
        for(int x = -0; x<=0; x++) {
            for(int z = -0; z <= 0; z++) {
                chunks.push_back(new Chunk(glm::vec3(x, -1, z)));
            }
        }
    }

    {
        ScopedClock c = ScopedClock("Adding vertex and index lists in: ", false, true);
        uint64_t t = 0;
        for(auto& chunk : chunks) {
            this->engine->AddVerticeList(chunk->vertices);
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
    std::cout << "Update" << std::endl;
}

void Mandir::PhysicsUpdate(double frameTime) {
    std::cout << "PhysicsUpdate" << std::endl;
}