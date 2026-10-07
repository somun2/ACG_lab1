#include "whittedshader.h"

#include "../core/utils.h"
#include "../materials/phong.h"


WhittedShader::WhittedShader(Vector3D hitColor_, double maxDist_, Vector3D bgColor_) :
    Shader(bgColor_)
{
}

Vector3D WhittedShader::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<LightSource*>& lsList) const
{
    Intersection its;
    bool hasInter = Utils::getClosestIntersection(r, objList, its);
    Vector3D c;
    
    for (size_t lsIndex = 0; lsIndex < lsList.size(); lsIndex++) {
        Vector3D wi = (lsList.at(lsIndex)->sampleLightPosition() - its.itsPoint).normalized();
        Vector3D wo = (lsList.at(lsIndex)->sampleLightPosition() - its.itsPoint).normalized();
    }
    if (hasInter) {

        return c;
    }
    else {
        return bgColor;
    }
}
