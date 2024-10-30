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
	Ray(Scene* scene, glm::vec3 start, glm::vec3 direction, ColourRGB colour = ColourRGB(), Ray* prevRay = nullptr, bool isShadowRay = false);
	~Ray();

	Object* rayIntersection(glm::vec3& collisionPoint);
	
	ColourRGB castRay();
	ColourRGB castShadowRay(const LightSource* light);


	//glm::vec3 bounce();

	void setNextRay(Ray* nextRay);

	glm::vec3 getDirection() const;
	glm::vec3 getStartPos() const;
	glm::vec3 getEndPos() const;
	void setEndpos(glm::vec3 pos) { _endPos = pos; };
	int getBounces() const;
	Scene* getScene() const;
	
	ColourRGB getColour();
	void addColour(ColourRGB colour);

	float calcIntensity();
	ColourRGB sumColours();

	const glm::mat3 toLocalCoord(glm::vec3 normal) {
		//const glm::vec3 Z{ normal };
		//const glm::vec3 X = glm::normalize(_direction - glm::dot(_direction, Z) * Z);
		//const glm::vec3 Y = glm::cross(-X, Z);

		// lec 2 slide 13
		glm::vec3 x_L = glm::normalize(-_direction + glm::dot(normal, _direction) * normal);
		glm::vec3 z_L = glm::normalize(normal);

		glm::vec3 y_L = glm::cross(z_L, x_L);

		return glm::mat3{
			x_L.x, y_L.x, z_L.x,
			x_L.y, y_L.y, z_L.y,
			x_L.z, y_L.z, z_L.z,
		};

		/*return (glm::mat4{
		x_L.x, y_L.x, z_L.x, 0.f,
		x_L.y, y_L.y, z_L.y, 0.f,
		x_L.z, y_L.z, z_L.z, 0.f,
		0.f, 0.f, 0.f, 1.f } *
		glm::mat4{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		-collisionPoint.x, -collisionPoint.y, -collisionPoint.z, 1.f
			});*/
	}
		

	const glm::mat3 toGlobalCoord(glm::vec3 normal) {
		return glm::inverse(toLocalCoord(normal));
	}


	void reflect(glm::vec3 collisionPoint, glm::vec3 reflectionDirection);
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos; // se Triangle::rayIntersection för att hitta där endPos definieras
	glm::vec3 _direction;

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	// om vi vill kunnda döda en ray efter x antal studsar
	int _timeToLive = 10; 

	//slidesen skriver att man ska skapa colourRGB så prob. needs changing later också double precision
	ColourRGB _colour = ColourRGB();

	std::shared_ptr<glm::vec3> _startingVertexPos;

	//använder _ för att visa att det är klassvariabel.


	int _bounces; // börja på 1 annars dör den, ??? får nu ett värde i Ray()

	Scene* _scene;

	bool _isShadowRay;
	bool _lit = false;

	double _intensity = 1.0;



};

//Ray::~Ray()
//{
//}