#pragma once

// array of objects

// each objects has triangles and a material
#include "vector"
#include "glm.hpp"



//#include "./include/ColourRGB.h"
//#include "./include/Material.h"

//#include "./include/Object.h" 
// colourrbg -> material -> objects -> triangles -> spheres ->  

//#include "./include/Triangle.h"
#include "./include/LightSource.h"
#include "./include/Sphere.h"
//class Object;
//class LightSource;

class Scene {
public:
	Scene();

	// istället för att definiera 12 trianglar... lägger också till i objects
	void createBox(glm::vec3& pos, double width, double length, double height, Material& material);

	void createPlane(glm::vec3& posBotLeft, glm::vec3& posTopRight, Material& material);

	// kallar på spheres konstruktor, och lägger till i objects
	void createSphere(glm::vec3& pos, double radius, Material& material);

	void createLightSource(glm::vec3& posBotLeft, glm::vec3& posTopRight, Material& material);

	std::vector<Object*> getObjects() { return _Objects; };
	std::vector<LightSource*> getLightSources() { return _LightSources; };

private:
	//std::vector<Triangle> a;
	std::vector<Object*> _Objects; // innehåller trianglar och sfärer
	std::vector<LightSource*> _LightSources; // Lightsource är trianglar 
};
 