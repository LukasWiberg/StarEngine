//
// Created by ReSung on 2021-09-19.
//

#include "Mesh.hpp"

Mesh::Mesh(GameObject *gameObject, const char *modelPath): Component(gameObject) {
    this->model = ModelHelper::LoadModel(modelPath);
}

Mesh::Mesh(GameObject *gameObject, ModelObject *model, MeshCopyMode mode): Component(gameObject) {
    switch(mode) {
        case MeshCopyMode::Copy:
            *this->model = ModelHelper::CopyModel(model);
            break;
        case MeshCopyMode::Reference:
            this->model = model;
            break;
    }
}

Mesh::~Mesh() {
    std::cout << "Yeeting mesh" << std::endl;
}
