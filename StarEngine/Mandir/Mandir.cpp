//
// Created by ReSung on 2021-12-13.
//

#include "Mandir.hpp"
#include "../Engine/General/ScopedClock.hpp"


Mandir::Mandir(StarEngine* pEngine) {
    this->engine = pEngine;
    {
        ScopedClock c = ScopedClock("Created new chunk in: ", false, true);
        chunks.push_back(new Chunk(glm::vec2(0,0)));
    }

    this->engine->AddVerticeList(chunks[0]->vertices);
    this->engine->AddIndexList(chunks[0]->indices);
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