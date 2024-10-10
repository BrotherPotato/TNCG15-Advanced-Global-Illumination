#include "./include/Sphere.h"
#include "glm.hpp"

#include "./include/Ray.h"


Sphere::Sphere(glm::vec3& pos, double radius, CustomColour& colour) {
	position = pos;
	radius = radius;
}

glm::vec3 Sphere::getNormal(Ray& ray) {


	return glm::vec3();

}



