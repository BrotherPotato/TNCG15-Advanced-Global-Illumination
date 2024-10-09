#pragma once

// array of objects

// each objects has triangles and a material

#include "Triangle.h"
#include "vector"

class Scene {
public:
	Scene();

	// istället för att definiera 12 trianglar... lägger också till i objects
	void createBox(glm::vec3 pos, double width, double length, double height, CustomColour colour);

	// kallar på spheres konstruktor, och lägger till i objects
	void createSphere();

private:
	std::vector<Triangle> a;
	std::vector<Object*> objects; // innehåller trianglar och sfärer
};
