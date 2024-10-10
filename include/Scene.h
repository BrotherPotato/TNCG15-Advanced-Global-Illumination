#pragma once

// array of objects

// each objects has triangles and a material

#include "Triangle.h"
#include "Sphere.h"
#include "vector"
#include "ColourRGB.h"
#include "LightSource.h"

class Scene {
public:
	Scene();

	// ist�llet f�r att definiera 12 trianglar... l�gger ocks� till i objects
	void createBox(glm::vec3& pos, double width, double length, double height, ColourRGB& colour);

	void createPlane(glm::vec3& posBotLeft, glm::vec3& posTopRight, ColourRGB& colour);

	// kallar p� spheres konstruktor, och l�gger till i objects
	void createSphere(glm::vec3& pos, double radius, ColourRGB& colour);

	void createLightSource(glm::vec3& posBotLeft, glm::vec3& posTopRight, ColourRGB& colour);

private:
	std::vector<Triangle> a;
	std::vector<Object*> _Objects; // inneh�ller trianglar och sf�rer
	std::vector<LightSource*> _LightSources; // Lightsource �r trianglar 
};
 