#include "whittedshader.h"

#include "../core/utils.h"
#include "../materials/phong.h"
#include <iostream>
#include <cmath>


WhittedShader::WhittedShader(Vector3D hitColor_, double maxDist_, Vector3D bgColor_) :
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

    const double eps = 1e-4;
    const Vector3D n = its.normal;
    const Vector3D wo = (-r.d).normalized();
    const Vector3D origin = its.itsPoint + n * eps;

    Vector3D Lo = Vector3D(0.0, 0.0, 0.0);

    for (size_t lsIndex = 0; lsIndex < lsList.size(); lsIndex++) {
        LightSource* light = lsList.at(lsIndex);
        Vector3D lsPos = light->sampleLightPosition();
        Vector3D toLight = lsPos - its.itsPoint;
        double lightDist = toLight.length();
        Vector3D wi = toLight/lightDist;

        Intersection itsS;
        if (Utils::getClosestIntersection(Ray(origin, wi), objList, itsS)&&(itsS.itsPoint-origin).length()<lightDist-eps){
            continue;
        }

        double wi_n = std::max(0.0, dot(wi,n));
        Vector3D brdf = its.shape->getMaterial().getReflectance(n, wo, wi);
        Lo += light->getIntensity()*brdf*wi_n;
    }

    return Lo;
}
