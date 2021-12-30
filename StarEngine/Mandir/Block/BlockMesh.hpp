//
// Created by ReSung on 2021-12-28.
//

#ifndef B_OBJ_BLOCKMESH_HPP
#define B_OBJ_BLOCKMESH_HPP

#include "../../Engine/General/ModelHelper.hpp"
#include "../../Engine/General/Dictionary.hpp"
#include "Block.hpp"

enum FaceDirection {
    Top = 0,
    Side = 1,
    Bottom = 2
};

class BlockMesh {
private:
    BlockMesh();
    static BlockMesh *instance;
    static ModelObject planeXPos();
    static ModelObject planeXNeg();
    static ModelObject planeZNeg();
    static ModelObject planeZPos();
    static ModelObject planeYNeg();
    static ModelObject planeYPos();
    Dictionary<Block, glm::vec2*> textureOffsets;

    ModelObject planeXPosMesh = planeXPos();
    ModelObject planeXNegMesh = planeXNeg();
    ModelObject planeYPosMesh = planeYPos();
    ModelObject planeYNegMesh = planeYNeg();
    ModelObject planeZPosMesh = planeZPos();
    ModelObject planeZNegMesh = planeZNeg();

public:
    static BlockMesh *getInstance();
    static const ModelObject& PlaneXPos();
    static const ModelObject& PlaneXNeg();
    static const ModelObject& PlaneYPos();
    static const ModelObject& PlaneYNeg();
    static const ModelObject& PlaneZPos();
    static const ModelObject& PlaneZNeg();
    static const glm::vec2& GetTextureOffset(Block block, FaceDirection direction);

//    static void Initialize();
};


#endif //B_OBJ_BLOCKMESH_HPP
