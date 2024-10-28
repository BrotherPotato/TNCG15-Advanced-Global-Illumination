#include "./include/Sphere.h"
#include "glm.hpp"

#include "./include/Ray.h"


Sphere::Sphere(glm::vec3& pos, double radius, Material& material) {
	_Position = pos;
	_Radius = radius;
	_ObjectMaterial = material;
}

glm::vec3 Sphere::getNormal(Ray* ray) const {


	return glm::vec3();

}

//ColourRGB Sphere::getColour() const {
//	return _ObjectMaterial.getColour();
//}

Material Sphere::getMaterial() const {
	return _ObjectMaterial;
}


bool Sphere::rayIntersection(Ray* ray) const {

	glm::vec3 rayStart{ ray->getStartPos() };
	glm::vec3 rayEnd{ ray->getEndPos() };
	glm::vec3 rayDirectionNormalised = glm::normalize(rayEnd - rayStart);

	glm::vec3 oc = rayStart - glm::vec3(_Position.x, _Position.y, _Position.z);

	double a = glm::dot(rayDirectionNormalised, rayDirectionNormalised);
	double b = glm::dot(oc, rayDirectionNormalised * 2.0f);
	double c = glm::dot(oc, oc) - _Radius * _Radius;
	double d = 0.0;

	bool isInside = false;

	double expInSqrt = glm::pow(b / 2, 2) - a * c;

	if (expInSqrt < 0) { //not intersected
		return false;
	}
	else if (expInSqrt > -0 && expInSqrt < 0) {// one intersection
		d = (-b) / 2;
	}
	else //two intersections
	{

		// Pick the intersection that is closest to the starting point of the ray, while givning a positive d
		d = ((-b) / 2) - glm::sqrt(expInSqrt);
		double otherPossible = ((-b) / 2) + glm::sqrt(expInSqrt);
		if (d < 0 && otherPossible > 0) //intersection ray is coming from inside the object
		{
			d = otherPossible;
			isInside = true; 
		}
	}

	glm::vec3 intersection = rayStart + rayDirectionNormalised.operator*=(d);
	glm::vec3 intersectionPointNormal = glm::normalize(glm::vec3{
		intersection.x - _Position.x,
		intersection.y - _Position.y,
		intersection.z - _Position.z });

	// Flip normal if intersecting from inside object
	if (isInside) {
		intersectionPointNormal *= -1.0;
	}

	if (d < 0) return false; //intersection behind the object 
	
	//osäker vad vi vill ha returnerat
}
