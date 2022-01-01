//
// Created by ReSung on 2022-01-01.
//

#ifndef B_OBJ_NOISEOBJECT_HPP
#define B_OBJ_NOISEOBJECT_HPP


#include "OpenSimplex2S.hpp"

class NoiseObject {
private:
    OpenSimplexEnv *ose;
    OpenSimplexGradients *osg;
public:
    explicit NoiseObject(long seed);

    double Sample2D(double x, double y);
    double Sample3D(double x, double y, double z);
};


#endif //B_OBJ_NOISEOBJECT_HPP
