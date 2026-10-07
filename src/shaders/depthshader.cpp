#include "depthshader.h"
#include "../core/utils.h"

DepthShader::DepthShader() :
    color(Vector3D(1, 0, 0))
{ }

DepthShader::DepthShader(Vector3D hitColor_, double maxDist_, Vector3D bgColor_) :
    Shader(bgColor_), maxDist(maxDist_), color(hitColor_)
{ }

Vector3D DepthShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<LightSource*> &lsList) const
{
    Intersection its;
	bool hasInter = Utils::getClosestIntersection(r, objList, its);
    double c;
    double hitDistance;
    if (hasInter) {
        hitDistance = (its.itsPoint-(r.o)).length();
        c = 1-(hitDistance / maxDist);
		if (c < 0) {
			c = 0;
		}
		return Vector3D(0, c, 0);
    }
    else {
        return bgColor;
    }
}
