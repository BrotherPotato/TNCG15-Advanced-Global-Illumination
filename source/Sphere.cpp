#include "./include/Sphere.h"
#include "glm.hpp"

//#include "./include/Ray.h"


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

	return false;
}
