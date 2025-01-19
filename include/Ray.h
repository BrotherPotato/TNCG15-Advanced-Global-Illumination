#pragma once

// prev, next ray
// origin, direction,

#include "glm.hpp"
#include <iostream>

//#include "./include/Scene.h"
//#include "./include/ColourRGB.h"
//#include "./include/LightSource.h"
#include "./include/Scene.h"
#include "./include/Material.h"
//#include "./include/LightSource.h"

#include <random>


class Scene;
class Object;
class LightSource;

class Ray
{
public:
	Ray(Scene* scene, glm::vec3 start, glm::vec3 direction, ColourRGB importance, Ray* prevRay, bool isShadowRay);
	~Ray();

	Object* rayIntersection();
	
	ColourRGB castRay();
	ColourRGB castShadowRay(LightSource* light);

	void setNextRay(Ray* nextRay);

	glm::vec3 getDirection() const;
	glm::vec3 getStartPos() const;
	glm::vec3 getEndPos() const;
	void setEndpos(glm::vec3 pos) { _endPos = pos; };
	int getBounces() const;
	Scene* getScene() const;
	

	float calcIntensity(LightSource* light) const;
	float oldCalcIntensity();
	ColourRGB sumColours();
	ColourRGB pixelRadiance();

	const glm::mat3 toLocalCoord(glm::vec3 normal) {

		// lec 2 slide 13
		glm::vec3 x_L = glm::normalize(-_direction + glm::dot(normal, _direction) * normal);
		glm::vec3 z_L = glm::normalize(normal);
		glm::vec3 y_L = glm::cross(z_L, x_L);

		return glm::mat3{
			x_L.x, y_L.x, z_L.x,
			x_L.y, y_L.y, z_L.y,
			x_L.z, y_L.z, z_L.z,
		};

	}
		

	const glm::mat3 toGlobalCoord(glm::vec3 normal) {
		return glm::inverse(toLocalCoord(normal));
	}
	void mirrorReflect(glm::vec3 direction, glm::vec3 normal);
	void transparentRefract(glm::vec3 direction, glm::vec3 normal, float R, float Omega, float R_Omega_Schlicks);


	void createNewRay(glm::vec3 reflectionDirection);
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos; // se Triangle::rayIntersection
	glm::vec3 _direction;

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	//slidesen skriver att man ska skapa colourRGB s� prob. needs changing later ocks� double precision
	ColourRGB _importance = ColourRGB(1);
	ColourRGB _radiance = ColourRGB(0);
	ColourRGB _directLight = ColourRGB(0);
	Object* _objectHit;

	bool _refracting = false; // om en ray slutar på mirror och refraktar, gör denna true

	std::shared_ptr<glm::vec3> _startingVertexPos;

	int _bounces;

	Scene* _scene;

	bool _isShadowRay;
	bool _lit = false; // om en shadowray träffade ljus

	static constexpr int _shadowRaysPerRay = 1;

	float _n1 = 1.0f; // för luft, men dessa två värden byter plats om rayen färdas genom ett av dem
	float _n2 = 1.5f; // för glas

};

//Ray::~Ray()
//{
//}