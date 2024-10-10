#pragma once

// prev, next ray
// origin, direction,

#include "glm.hpp"
#include <iostream>

#include "./include/ColourRGB.h"


class Ray
{
public:
	Ray(glm::vec3 start, glm::vec3 direction, ColourRGB colour);
	~Ray();
	glm::vec3 shadowRay();
	glm::vec3 bounce();

	glm::vec3 getDirection() const;
	glm::vec3 getStartPos() const;
	
	ColourRGB getColour() const { return _colour; };
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos;
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

};

//Ray::~Ray()
//{
//}