#pragma once

#include "glm.hpp"
#include "./include/Object.h"
#include "./include/Ray.h"

class Sphere : public Object {
public:
	Sphere(glm::vec3& pos, double radius, ColourRGB& colour);

	// returnar en normal beroende på inkommande ray
	glm::vec3 calcNormal(Ray& ray);
private:
	glm::vec3 position;
	double radius;
};