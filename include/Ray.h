#pragma once

// prev, next ray
// origin, direction,

#include "glm.hpp"
#include <iostream>

#include "./include/CustomColor.h"


class Ray
{
public:
	Ray(glm::vec3& start, glm::vec3& direction, CustomColor& colour);
	~Ray();
	glm::vec3 shadowRay();
	glm::vec3 bounce();

	glm::vec3 getDirection() const;
	glm::vec3 getStartPos() const;
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos;
	glm::vec3 _direction; //egenvärdet right?

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	// om vi vill kunnda döda en ray efter x antal studsar
	int _timeToLive; 

	//slidesen skriver att man ska skapa colourRGB så prob. needs changing later också double precision
	CustomColor _colour;

	std::shared_ptr<glm::vec3> startingVertexPos;

	//använder _ för att visa att det är klassvariabel.

};

//Ray::~Ray()
//{
//}