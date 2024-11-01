#include "./include/Sphere.h"
#include "glm.hpp"

#include "./include/Ray.h"


Sphere::Sphere(glm::vec3& pos, double radius, Material& material) {
	_Position = pos;
	_Radius = radius;
	_ObjectMaterial = material;
}

glm::vec3 Sphere::getNormal(Ray* ray) const {

	glm::normalize(_normal);

	return _normal;

}

//ColourRGB Sphere::getColour() const {
//	return _ObjectMaterial.getColour();
//}

Material Sphere::getMaterial() const {
	return _ObjectMaterial;
}


bool Sphere::rayIntersection(Ray* ray) {

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

	setNormal(intersectionPointNormal);

	if (d < 0) return false; //intersection behind the object 
	
	//std::cout << "SPHERE";
	ray->setEndpos(intersection);
	

	return true;
	//osäker vad vi vill ha returnerat




	// ny kod som faktiskt följer föreläsningarna
	// lec 8 slide 6

	//glm::vec3 rayEnd{ ray->getEndPos() };

	//glm::vec3 S{ ray->getStartPos() };
	//glm::vec3 tempVec = rayEnd - S;
	//glm::vec3 D = glm::normalize(tempVec);
	//if (D.r) {
	//	return false;
	//}
	//glm::vec3 C = _Position;
	//float r = _Radius;

	//glm::vec3 SsubtractC = S - C;

	//float c1 = glm::dot(D, D);
	//float c2 = glm::dot(2.0f * D, SsubtractC);
	//float c3 = glm::dot(SsubtractC, SsubtractC) - r * r;

	//float arg = c2 * c2 - 4.0f * c1 * c3;

	//float tmin = 0;
	//const float epsilon = 0.000001;
	////no solution, ray miss, Abs < 0
	//if (arg < -epsilon) {
	//	return false;
	//}
	////one solution, ray touches sphere, Abs = 0
	//if (abs(arg) <= epsilon) {
	//	tmin = -c2 / (2 * c1);
	//}
	////two solutions, Abs > 0
	//if (abs(arg) > epsilon) {
	//	// we use the lowest value of tmin - before sqrt
	//	tmin = (-c2 - std::sqrt(arg)) / (2.0f * c1);
	//}
	////std::cout << tmin;
	//glm::vec3 xr = S + D * tmin;

	//if (tmin <= epsilon || tmin > 1000.0f) {
	//	return false;
	//}

	//ray->setEndpos(xr);
	//setNormal(glm::normalize(xr-C));

	//return true;
}
