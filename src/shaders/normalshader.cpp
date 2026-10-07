#include "normalshader.h"

#include "../core/utils.h"

NormalShader::NormalShader(Vector3D bgColor_) :
	Shader(bgColor_)
{ }

Vector3D NormalShader::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<LightSource*>& lsList) const
{
    Intersection its;
    bool hasInter = Utils::getClosestIntersection(r, objList, its);
    Vector3D c;
    if (hasInter) {
        c = (its.normal+((1.0,1.0,1.0)))/=(2.0);
        return c;
    }
    else {
        return bgColor;
    }
}
