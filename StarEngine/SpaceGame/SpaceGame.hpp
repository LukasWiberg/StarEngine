//
// Created by lukas on 2023-07-11.
//

#ifndef B_OBJ_SPACEGAME_HPP
#define B_OBJ_SPACEGAME_HPP


#include "../Engine/StarEngine.hpp"

class SpaceGame {
private:
    StarEngine *engine;

public:
    explicit SpaceGame(StarEngine *pEngine);

    void Update(double frameTime);
    void PhysicsUpdate(double frameTime);
};


#endif //B_OBJ_SPACEGAME_HPP
