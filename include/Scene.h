#pragma once

// array of objects

// each objects has triangles and a material

#include "Triangle.h"
#include "vector"

class Scene {
public:
	Scene();

	// ist�llet f�r att definiera 12 trianglar... l�gger ocks� till i objects
	void createBox(glm::vec3 pos, double width, double length, double height, CustomColour colour);

	// kallar p� spheres konstruktor, och l�gger till i objects
	void createSphere();

private:
	std::vector<Triangle> a;
	std::vector<Object*> objects; // inneh�ller trianglar och sf�rer
};
