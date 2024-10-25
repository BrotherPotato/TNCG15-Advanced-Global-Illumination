#pragma once
#include <iostream>
#include <vector>
//#include <./include/Ray.h>
#include <./include/Material.h>
class Ray; //forward declaraion
class Material;

class  Object {
public:


	virtual glm::vec3 getNormal() const { return glm::vec3(); };

	virtual bool rayIntersection(Ray* ray) const {
		std::cout << "waaaa"; // test f�r att se om just denna funktion kallas, n�r den egentligen aldrig ska anv�ndas.
		return false; 
	};

	virtual Material getMaterial() const { return Material(); };
private:
	
};