//
// Created by ReSung on 2022-01-01.
//

#include "NoiseObject.hpp"

NoiseObject::NoiseObject(long seed) {
    ose = initOpenSimplex();
    osg = newOpenSimplexGradients(ose, seed);
}

double NoiseObject::Sample2D(double x, double y) {
    return (noise2(ose, osg, x, y)+1)/2;
}

double NoiseObject::Sample3D(double x, double y, double z) {
    return (noise3_XYBeforeZ(ose, osg, x, y, z)+1)/2;
}