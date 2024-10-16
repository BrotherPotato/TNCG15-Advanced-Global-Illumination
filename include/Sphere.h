#pragma once

#include "glm.hpp"
#include "./include/Object.h"
#include "./include/Ray.h"
#include "./include/Material.h"

class Sphere : public Object {
public:
	//Sphere(glm::vec3& pos, double radius, ColourRGB& colour);
	Sphere(glm::vec3& pos, double radius, Material& material);

	// returnar en normal beroende p� inkommande ray
	glm::vec3 getNormal(Ray& ray) const;

	ColourRGB getColour() const;


	bool rayIntersection(Ray& ray) const;

private:
	glm::vec3 _Position;
	double _Radius;
	Material _ObjectMaterial;
};