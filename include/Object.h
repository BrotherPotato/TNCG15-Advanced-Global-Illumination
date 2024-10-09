#pragma once

#include <vector>


class  Object {
public:
	// fix intersection functions

private:
	//virtual Material 
	virtual glm::vec3 getNormal() const;
	virtual bool planeIntersection(Ray& ray) const; // tror det är den vi ska ha
};