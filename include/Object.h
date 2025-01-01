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
		std::cout << "waaaa"; // test för att se om just denna funktion kallas, när den egentligen aldrig ska användas.
		return false; 
	};

	virtual Material getMaterial() const { return Material(); };

	virtual bool isSphere() const { return false; };

private:
	bool _sphere = false;
};