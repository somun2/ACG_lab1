
#ifndef TRANSMISSIVE_H
#define TRANSMISSIVE_H

#include "material.h"

class Transmissive : public Material
{
private:
    double mu_t;

public:
    explicit Transmissive(double mu_t_ = 0.7);

    Vector3D getReflectance( const Vector3D& n, const Vector3D& wo, const Vector3D& wi) const override;

    double getIndexOfRefraction() const override;

    bool hasSpecular() const override { return false; }
    bool hasTransmission() const override { return true; }
    bool hasDiffuseOrGlossy() const override { return false; }
    bool isEmissive() const override { return false; }
};

#endif // TRANSMISSIVE_H
