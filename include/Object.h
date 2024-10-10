#pragma once

#include <vector>
#include "Ray.h"

class  Object {
public:
	// fix intersection functions
	//virtual getMaterial ?
	virtual glm::vec3 getNormal() const { return glm::vec3(); };
	//virtual bool planeIntersection(Ray& ray) const; // tror det är den vi ska ha

	virtual bool rayIntersection(Ray& ray) const { return false; };
private:
	
};