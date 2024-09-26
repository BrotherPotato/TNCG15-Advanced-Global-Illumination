#pragma once

#include "glm.hpp"
#include "Ray.h"

class Triangle
{
public:
	Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& colour);
	~Triangle();
	void calcNormal();

	bool rayIntersection(Ray& ray) const;

	glm::vec4 getNormal() const;

private:
	glm::vec3 _v0, _v1, _v2, _normal, _colour;

};

glm::vec3 Triangle::getNormal() const {
	return _normal;
}


// points