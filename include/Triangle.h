#pragma once

#include "glm.hpp"
#include "Ray.h"

class Triangle
{
public:
	Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, CustomColor& color);
	~Triangle();
	void calcNormal();

	bool rayIntersection(Ray& ray) const;
	bool planeIntersection(Ray& ray) const;

	glm::vec3 getNormal() const;

private:
	glm::vec3 _v0, _v1, _v2, _normal;
	CustomColor _color;

};

// points