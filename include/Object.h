#pragma once

#include <vector>
//#include <./include/Ray.h>
#include <./include/Material.h>
class Ray; //forward declaraion
class Material;

class  Object {
public:
	// fix intersection functions
	//virtual getMaterial ?
	virtual glm::vec3 getNormal() const { return glm::vec3(); };
	//virtual bool planeIntersection(Ray& ray) const; // tror det är den vi ska ha

	virtual bool rayIntersection(Ray* ray) const { return false; };
	virtual Material getMaterial() const;
private:
	
};