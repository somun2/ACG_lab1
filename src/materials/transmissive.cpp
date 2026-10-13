
#include "transmissive.h"

Transmissive::Transmissive(double mu_t_)
    : Material(), mu_t(mu_t_)
{
}

Vector3D Transmissive::getReflectance(const Vector3D& n, const Vector3D& wo, const Vector3D& wi) const
{
    return Vector3D(0.0, 0.0, 0.0);
}

double Transmissive::getIndexOfRefraction() const
{
    return mu_t;
}
