#pragma once

#include "glm.hpp"
#include "./include/Object.h"
//#include "./include/Ray.h"
//#include "./include/Material.h"

class Ray;

class Sphere : public Object {
public:
	//Sphere(glm::vec3& pos, double radius, ColourRGB& colour);
	Sphere(glm::vec3& pos, double radius, Material& material);

	// returnar en normal beroende på inkommande ray
	glm::vec3 getNormal(Ray* ray) const override;
	void setNormal(glm::vec3 normal) { _normal = normal; };

	//ColourRGB getColour() const;

	Material getMaterial() const override;


	bool rayIntersection(Ray* ray) override;

private:
	glm::vec3 _Position;
	double _Radius;
	Material _ObjectMaterial;
	glm::vec3 _normal;
};