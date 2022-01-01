//
// Created by ReSung on 2021-12-13.
//

#ifndef B_OBJ_MANDIR_HPP
#define B_OBJ_MANDIR_HPP

class Mandir;
#include "../Engine/StarEngine.hpp"
#include "Chunk/Chunk.hpp"
#include "../Engine/Noise/NoiseObject.hpp"

class Mandir {
private:
    StarEngine *engine;
    std::vector<Chunk*> chunks;
    NoiseObject* worldGeneratorNoiseObject;

public:
    explicit Mandir(StarEngine *pEngine);

    void Update(double frameTime);
    void PhysicsUpdate(double frameTime);
};


#endif //B_OBJ_MANDIR_HPP
