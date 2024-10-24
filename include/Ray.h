#pragma once

// prev, next ray
// origin, direction,

#include "glm.hpp"
#include <iostream>

//#include "./include/Scene.h"
#include "./include/ColourRGB.h"
#include "./include/LightSource.h"


class Scene;
class Object;


class Ray
{
public:
	Ray(Scene* scene, glm::vec3 start, glm::vec3 direction, ColourRGB colour = ColourRGB(), Ray* prevRay = nullptr);
	~Ray();

	Object* rayIntersection(glm::vec3& collisionPoint);
	
	ColourRGB castRay();
	ColourRGB castShadowRay(const LightSource* light);


	//glm::vec3 bounce();

	void setNextRay(Ray* nextRay);

	glm::vec3 getDirection() const;
	glm::vec3 getStartPos() const;
	glm::vec3 getEndPos() const;
	int getBounces() const;
	Scene* getScene() const;
	
	ColourRGB getColour() const;
	void addColour(ColourRGB colour);




	void reflect(glm::vec3 collisionPoint, glm::vec3 reflectionDirection);
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos;
	glm::vec3 _direction;

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	// om vi vill kunnda d�da en ray efter x antal studsar
	int _timeToLive = 25; 

	//slidesen skriver att man ska skapa colourRGB s� prob. needs changing later ocks� double precision
	ColourRGB _colour = ColourRGB();

	std::shared_ptr<glm::vec3> _startingVertexPos;

	//anv�nder _ f�r att visa att det �r klassvariabel.


	int _bounces; // b�rja p� 1 annars d�r den, ??? f�r nu ett v�rde i Ray()

	Scene* _scene;

};

//Ray::~Ray()
//{
//}