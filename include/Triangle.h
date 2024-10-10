#pragma once

#include "glm.hpp"
#include "Ray.h"
#include "./include/Object.h"
#include "./include/Material.h"

// �ndra color till material sen
class Triangle : public Object
{
public:
	Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const ColourRGB& colour);
	//~Triangle();
	void calcNormal();

	bool rayIntersection(Ray& ray) const;
	bool planeIntersection(Ray& ray) const;

	glm::vec3 getNormal() const;

private:
	glm::vec3 _v0, _v1, _v2, _normal;
	ColourRGB _colour; // flytta in i Material sen
	Material _ObjectMaterial;
};

// points