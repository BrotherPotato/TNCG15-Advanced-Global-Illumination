#pragma once

// array of objects

// each objects has triangles and a material
#include "vector"
#include "glm.hpp"



//#include "./include/ColourRGB.h"
//#include "./include/Material.h"

#include "./include/Object.h" 
// colourrbg -> material -> objects -> triangles -> spheres ->  
#include "./include/Sphere.h"
#include "./include/Triangle.h"



//#include "./include/LightSource.h"
class Object;
class Material;
class Triangle;
class LightSource;

class Scene {
public:
	Scene();

	// ist�llet f�r att definiera 12 trianglar... l�gger ocks� till i objects
	void createBox(glm::vec3& pos, double width, double length, double height, Material& material);

	void createTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, Material& mat);

	void createPlane(glm::vec3& posBotLeft, glm::vec3& posTopRight, Material& material);

	// kallar p� spheres konstruktor, och l�gger till i objects
	void createSphere(glm::vec3& pos, double radius, Material& material);

	void createLightSource(glm::vec3& posBotLeft, glm::vec3& posTopRight);

	void createLightSourceTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);

	std::vector<Object*>& getObjects() { return _Objects; };
	std::vector<LightSource*>& getLightSources() { return _LightSources; };

	std::vector<Object*>& getOALS();

private:
	//std::vector<Triangle> a;
	std::vector<Object*> _Objects; // inneh�ller trianglar och sf�rer
	std::vector<LightSource*> _LightSources; // Lightsource �r trianglar 


};
 