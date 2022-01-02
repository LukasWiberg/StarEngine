//
// Created by ReSung on 2021-12-13.
//

#include "Mandir.hpp"
#include "../Engine/General/ScopedClock.hpp"
#include "Block/BlockMesh.hpp"
#include "../Engine/Noise/OpenSimplex2S.hpp"


Mandir::Mandir(StarEngine* pEngine) {
    this->engine = pEngine;
    worldGeneratorNoiseObject = new NoiseObject(123543);
    int chunksDiameter = 20;
    {
        ScopedClock c = ScopedClock(" ", false, true);
        int chunkCount = 0;
        for(int x = -chunksDiameter; x<=chunksDiameter; x++) {
            for(int z = -chunksDiameter; z <= chunksDiameter; z++) {
                chunks.push_back(new Chunk(worldGeneratorNoiseObject, glm::vec3(x, -1, z)));
                chunkCount++;
            }
        }
        std::cout << "Created "<< chunkCount << " chunks in:";
    }

    {

        ScopedClock c = ScopedClock("Adding vertex and index lists in: ", false, true);
//        uint32_t t = 0;
        for(auto& chunk : chunks) {
            auto mesh = this->engine->AddMesh(chunk->vertices, chunk->indices);
//            t++;
//            if(t%3==0) {
//                mesh->visible = false;
//            }
        }
    }
}


void Mandir::Update(double frameTime) {
//    std::cout << "Update" << std::endl;
}

void Mandir::PhysicsUpdate(double frameTime) {
//    std::cout << "PhysicsUpdate" << std::endl;
}