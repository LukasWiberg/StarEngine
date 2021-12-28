//
// Created by ReSung on 2021-12-28.
//

#include "BlockMesh.hpp"

BlockMesh* BlockMesh::instance = nullptr;

BlockMesh *BlockMesh::getInstance() {
    if(BlockMesh::instance==nullptr){
        BlockMesh::instance = new BlockMesh();
    }
    return BlockMesh::instance;
}

BlockMesh::BlockMesh() {
    this->planeXPosMesh = planeXPos();
    this->planeXNegMesh = planeXNeg();
    this->planeYPosMesh = planeYPos();
    this->planeYNegMesh = planeYNeg();
    this->planeZPosMesh = planeZPos();
    this->planeZNegMesh = planeZNeg();
}


ModelObject BlockMesh::planeXPos() {
    ModelObject ret{};
    ret.vertices.resize(4);
    ret.vertices[0] = Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0.05)};
    ret.vertices[1] = Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0.05)};
    ret.vertices[2] = Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0)};
    ret.vertices[3] = Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0)};
    ret.indices = {
            2, 1, 0,
            2, 3, 1
    };
    return ret;
}

ModelObject BlockMesh::planeXNeg() {
    ModelObject ret{};
    ret.vertices.resize(4);
    ret.vertices[0] = Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0.05)};
    ret.vertices[1] = Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0.05)};
    ret.vertices[2] = Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0)};
    ret.vertices[3] = Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0)};
    ret.indices = {
            0, 1, 3,
            0, 3, 2
    };
    return ret;
}

ModelObject BlockMesh::planeZPos() {
    ModelObject ret{};
    ret.vertices.resize(4);
    ret.vertices[0] = Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0.05)};
    ret.vertices[1] = Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0)};
    ret.vertices[2] = Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0.05)};
    ret.vertices[3] = Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0)};
    ret.indices = {
            3, 0, 2,
            3, 1, 0
    };
    return ret;
}

ModelObject BlockMesh::planeZNeg() {
    ModelObject ret{};
    ret.vertices.resize(4);
    ret.vertices[0] = Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0.05)};
    ret.vertices[1] = Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0)};
    ret.vertices[2] = Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0.05)};
    ret.vertices[3] = Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0)};
    ret.indices = {
            1, 2, 0,
            1, 3, 2
    };
    return ret;
}

ModelObject BlockMesh::planeYPos() {
    ModelObject ret{};
    ret.vertices.resize(4);
    ret.vertices[0] = Vertex{glm::vec3(0,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0.05)};
    ret.vertices[1] = Vertex{glm::vec3(0,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0.05)};
    ret.vertices[2] = Vertex{glm::vec3(1,1,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0)};
    ret.vertices[3] = Vertex{glm::vec3(1,1,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0)};
    ret.indices = {
            0, 3, 2,
            0, 1, 3
    };
    return ret;
}

ModelObject BlockMesh::planeYNeg() {
    ModelObject ret{};
    ret.vertices.resize(4);
    ret.vertices[0] = Vertex{glm::vec3(0,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0.05)};
    ret.vertices[1] = Vertex{glm::vec3(0,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0.05)};
    ret.vertices[2] = Vertex{glm::vec3(1,0,0), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.05, 0)};
    ret.vertices[3] = Vertex{glm::vec3(1,0,1), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0, 0)};
    ret.indices = {
            3, 1, 0,
            3, 0, 2
    };
    return ret;
}

const ModelObject& BlockMesh::PlaneXPos() {
    return BlockMesh::getInstance()->planeXPosMesh;
}
const  ModelObject& BlockMesh::PlaneXNeg() {
    return BlockMesh::getInstance()->planeXNegMesh;
}

const ModelObject& BlockMesh::PlaneYPos() {
    return BlockMesh::getInstance()->planeYPosMesh;
}
const ModelObject& BlockMesh::PlaneYNeg() {
    return BlockMesh::getInstance()->planeYNegMesh;
}

const ModelObject& BlockMesh::PlaneZPos() {
    return BlockMesh::getInstance()->planeZPosMesh;
}
const ModelObject& BlockMesh::PlaneZNeg() {
    return BlockMesh::getInstance()->planeZNegMesh;
}
