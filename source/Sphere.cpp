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

	// ny kod som faktiskt följer föreläsningarna
	// lec 8 slide 6

	glm::vec3 S = ray->getStartPos();	// rayens ursprungspunkt
	glm::vec3 D = ray->getDirection();	// den nya linjens riktning
	glm::vec3 C = _Position; // sfärens mittpunkt
	float r = _Radius;

	glm::vec3 SsubtractC = S - C;	// linje från ray till sfärens origo

	float c1 = glm::dot(D, D); // D^2
	float c2 = 2.0f * glm::dot(D, SsubtractC);
	float c3 = glm::dot(SsubtractC, SsubtractC) - (r * r);

	float arg = (c2 * c2) - (4.0f * c1 * c3);

	float tmin = 0;
	float t1 = 0;
	float t2 = 0;
	const float epsilon = 0.000001;
	
	//no solution, ray miss, Abs < 0
	if (arg < 0) {
		return false;
	}

	//one solution, ray touches sphere, Abs = 0
	if (arg == 0) {
		tmin = -c2 / (2 * c1);
	}

	//two solutions, Abs > 0
	if (arg > 0) {
		// we use the lowest value of tmin - before sqrt
		t1 = (-c2 - std::sqrt(arg)) / (2.0f * c1);
		t2 = (-c2 + std::sqrt(arg)) / (2.0f * c1);

		if (t1 < t2) tmin = t1;
		else tmin = t2;
	}

	glm::vec3 xr = S + D * tmin;

	if (tmin <= epsilon || tmin > 1000.0f) {
		return false;
	}

	ray->setEndpos(xr);
	setNormal(glm::normalize(xr-C));

	return true;
}
