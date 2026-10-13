#include "whittedshader.h"
#include "../materials/mirror.h"
#include "../materials/transmissive.h"

#include "../core/utils.h"
#include "../materials/phong.h"
#include <iostream>
#include <cmath>


WhittedShader::WhittedShader(Vector3D bgColor_) :
    Shader(bgColor_)
{
}

Vector3D WhittedShader::computeColor(const Ray& r, const std::vector<Shape*>& objList,
    const std::vector<LightSource*>& lsList) const
{
    Intersection its;
    if (!Utils::getClosestIntersection(r, objList, its)) {
        return bgColor;
    }

    const Vector3D n = its.normal;
    const Vector3D wo = (-r.d);

    
    if (its.shape->getMaterial().hasTransmission()) {

        if (r.depth >= 5) {
            return Vector3D(0.0, 0.0, 0.0);
        }

        Vector3D normal = n;

        // Normal oriented against the incoming ray
        if (dot(r.d, normal) > 0.0) {
            normal = -normal;
        }

        double mu_t = its.shape->getMaterial().getIndexOfRefraction();

        // Determine whether the ray is entering or leaving
        // the sphere, using the original geometric normal.
        if (dot(r.d, n) > 0.0) {
            mu_t = 1.0 / mu_t;
        }

        double n_wo = dot(normal, wo);
        double radicand = 1.0 - mu_t * mu_t * (1.0 - n_wo * n_wo);

        // Total internal reflection
        if (radicand < 0.0) {
            Vector3D wr =Utils::computeReflectionDirection(r.d.normalized(), normal);
            Ray reflectedRay(its.itsPoint,wr,r.depth + 1);
            return computeColor(reflectedRay, objList, lsList);
        }

        // Refraction
        Vector3D wt = -mu_t * wo + normal * (mu_t * n_wo - std::sqrt(radicand));
        wt = wt.normalized();
        Ray transmittedRay(its.itsPoint, wt, r.depth + 1);
        return computeColor( transmittedRay, objList, lsList);
    }





    if (its.shape->getMaterial().hasSpecular()) {
        if (r.depth >= 5) {
            return Vector3D(0.0, 0.0, 0.0);
        }

        Vector3D normal = n;

        if (dot(r.d, normal) > 0.0) {
            normal = -normal;
        }

        Vector3D wr = Utils::computeReflectionDirection(r.d.normalized(), normal).normalized();
        Vector3D reflectedOrigin = its.itsPoint;
        Ray reflectedRay(reflectedOrigin, wr, r.depth + 1);
        return computeColor(reflectedRay, objList, lsList);
    }

    Vector3D Lo = Vector3D(0.0, 0.0, 0.0);

    for (size_t lsIndex = 0; lsIndex < lsList.size(); lsIndex++) {

        LightSource* light = lsList.at(lsIndex);
        Vector3D lsPos = light->sampleLightPosition();
        Vector3D toLight = lsPos - its.itsPoint;
        double lightDist = toLight.length();
        Vector3D wi = toLight.normalized();

        Intersection itsL;
        if (Utils::getClosestIntersection(Ray(its.itsPoint, wi), objList, itsL)&&(itsL.itsPoint- its.itsPoint).length() < lightDist){
            continue;
        }

        double wi_n = std::max(0.0, dot(wi,n));
        Vector3D brdf = its.shape->getMaterial().getReflectance(n, wo, wi);
        Lo += light->getIntensity()*brdf*wi_n;
    }
    double at = 0.2;
    return Lo + at * its.shape->getMaterial().getDiffuseReflectance();
}
