#include "normalshader.h"

#include "../core/utils.h"

NormalShader::NormalShader() :
	color(Vector3D(1, 0, 0))
{ }

NormalShader::NormalShader(Vector3D hitColor_, double maxDist_, Vector3D bgColor_) :
	Shader(bgColor_), maxDist(maxDist_), color(hitColor_)
{ }

Vector3D NormalShader::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<LightSource*>& lsList) const
{
    Intersection its;
    bool hasInter = Utils::getClosestIntersection(r, objList, its);
    Vector3D c;
    double hitDistance;
    if (hasInter) {
        c = (its.normal.operator+((1.0,1.0,1.0))).operator/=(2.0);
        return c;
    }
    else {
        return bgColor;
    }
}
