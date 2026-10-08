#include "whittedshader.h"

#include "../core/utils.h"
#include "../materials/phong.h"
#include <iostream>
#include <cmath>


WhittedShader::WhittedShader(Vector3D hitColor_, double maxDist_, Vector3D bgColor_) :
    Shader(bgColor_)
{
}

Vector3D WhittedShader::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<LightSource*>& lsList) const
{
    Intersection its;
    bool hasInter = Utils::getClosestIntersection(r, objList, its);
    Vector3D c;
    Vector3D Lo = Vector3D(0.0, 0.0, 0.0);
    
    if (hasInter) {
        Vector3D wo = (-r.d).normalized();
        Vector3D n = its.normal;
        double pi = PI;
        for (size_t lsIndex = 0; lsIndex < lsList.size(); lsIndex++) {
            Vector3D lsPos = lsList.at(lsIndex)->sampleLightPosition();
            Vector3D wi = (lsPos - its.itsPoint).normalized();
            Ray lR = Ray(lsPos, -wi);
			Intersection itsL;
			bool hasInterL = Utils::getClosestIntersection(lR, objList, itsL);
            if (hasInterL && (itsL.itsPoint.x != lsPos.x || itsL.itsPoint.y != lsPos.y || itsL.itsPoint.z != lsPos.z)) {
				printf("Light source %zu is occluded by an object at (%f, %f, %f)\n", lsIndex, itsL.itsPoint.x, itsL.itsPoint.y, itsL.itsPoint.z);
                continue;
            }
            Vector3D brfd = its.shape->getMaterial().getReflectance(n, wo, wi);
            Vector3D Li = lsList.at(lsIndex)->getIntensity()/(4*pi*pow((lsPos - its.itsPoint).length(), 2));
            double wi_n = dot(wi,n);
            Lo += Li * brfd * wi_n;
        }
    }
    else {
        return bgColor;
    }
	//printf("Color: %f, %f, %f\n", Lo.x, Lo.y, Lo.z);
    return Lo; 
}
