#pragma once

// array of objects

// each objects has triangles and a material

#include "Triangle.h"
#include "Sphere.h"
#include "vector"
#include "CustomColour.h"

class Scene {
public:
	Scene();

	// istället för att definiera 12 trianglar... lägger också till i objects
	void createBox(glm::vec3& pos, double width, double length, double height, ColourRGB& colour);

	void createPlane(glm::vec3& posBotLeft, glm::vec3& posTopRight, ColourRGB& colour);

	// kallar på spheres konstruktor, och lägger till i objects
	void createSphere(glm::vec3& pos, double radius, ColourRGB& colour);


private:
	std::vector<Triangle> a;
	std::vector<Object*> _Objects; // innehåller trianglar och sfärer
};
