#pragma once

// prev, next ray
// origin, direction,

#include "glm.hpp"
#include <iostream>

class Ray
{
public:
	Ray(glm::vec3& start, glm::vec3& direction, glm::vec3& colour);
	~Ray();
	glm::vec3 shadowRay();
	glm::vec3 bounce();

	glm::vec3 getDirection() const;
	glm::vec3 getStartPos() const;
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos;
	glm::vec3 _direction; //egenv�rdet right?

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	// om vi vill kunnda d�da en ray efter x antal studsar
	int _timeToLive; 

	//slidesen skriver att man ska skapa colourRGB s� prob. needs changing later ocks� double precision
	glm::vec3 _colour; 

	std::shared_ptr<glm::vec3> startingVertexPos;

	//anv�nder _ f�r att visa att det �r klassvariabel.

};

Ray::~Ray()
{
}