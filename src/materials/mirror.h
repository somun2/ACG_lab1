#ifndef MIRROR_H
#define MIRROR_H

#include "material.h"

class Mirror : public Material
{
public:
    Mirror();

    Vector3D getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi) const override;

    bool hasSpecular() const override { return true; }
    bool hasTransmission() const override { return false; }
    bool hasDiffuseOrGlossy() const override { return false; }
    bool isEmissive() const override { return false; }
};

#endif