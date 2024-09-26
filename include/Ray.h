#pragma once

// prev, next ray
// origin, direction,

#include "glm.hpp"
#include <iostream>

class Ray
{
public:
	Ray(glm::vec3 start, glm::vec3 direction, glm::vec3 colour);
	~Ray();
	glm::vec3 shadowRay();
	glm::vec3 bounce();
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos;
	glm::vec3 _rayDirection; //egenvärdet right?

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	// om vi vill kunnda döda en ray efter x antal studsar
	int _timeToLive; 

	//slidesen skriver att man ska skapa colourRGB så prob. needs changing later
	glm::vec3 _colour;

	std::shared_ptr<glm::vec3> startingVertexPos;

	//använder _ för att visa att det är klassvariabel.

};

Ray::~Ray()
{
}