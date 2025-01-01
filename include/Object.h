#pragma once
#include <iostream>
#include <vector>
//#include <./include/Ray.h>
#include <./include/Material.h>
class Ray; //forward declaraion
class Material;

class  Object {
public:


	virtual glm::vec3 getNormal(Ray* ray) const {
		std::cout << "waa ";
		return glm::vec3();
	}

	virtual bool rayIntersection(Ray* ray) {
		std::cout << "waaaa"; // test f�r att se om just denna funktion kallas, n�r den egentligen aldrig ska anv�ndas.
		return false; 
	};

	virtual Material getMaterial() const { return Material(); };

	virtual bool isSphere() const { return false; };

private:
	bool _sphere = false;
};