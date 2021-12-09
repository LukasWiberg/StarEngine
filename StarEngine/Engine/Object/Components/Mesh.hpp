//
// Created by ReSung on 2021-09-19.
//

#ifndef B_OBJ_MESH_HPP
#define B_OBJ_MESH_HPP


#include "../Component.hpp"

class Mesh: public Component {
private:

public:
    ModelObject *model;
    enum MeshCopyMode {
        Copy,
        Reference
    };

    Mesh(GameObject *gameObject, const char *modelPath);
    Mesh(GameObject *gameObject, ModelObject *model, MeshCopyMode mode);
    ~Mesh();

};


#endif //B_OBJ_MESH_HPP
