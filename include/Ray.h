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

	ColourRGB sumColours();




	void reflect(glm::vec3 collisionPoint, glm::vec3 reflectionDirection);
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos; // se Triangle::rayIntersection för att hitta där endPos definieras
	glm::vec3 _direction;

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	// om vi vill kunnda döda en ray efter x antal studsar
	int _timeToLive = 25; 

	//slidesen skriver att man ska skapa colourRGB så prob. needs changing later också double precision
	ColourRGB _colour = ColourRGB();

	std::shared_ptr<glm::vec3> _startingVertexPos;

	//använder _ för att visa att det är klassvariabel.


	int _bounces; // börja på 1 annars dör den, ??? får nu ett värde i Ray()

	Scene* _scene;

	bool _isShadowRay;
	bool _lit = false;

	//std::mt19937 _gen;
	//std::uniform_real_distribution<float> _rng;



};

//Ray::~Ray()
//{
//}