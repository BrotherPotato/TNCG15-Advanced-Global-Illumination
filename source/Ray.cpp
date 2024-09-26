#include "./include/Ray.h"


Ray::Ray(glm::vec3 start, glm::vec3 direction, glm::vec3 colour) :
	_startPos(start), _rayDirection(direction), _colour(glm::vec3{ 0.0 , 0.0 , 0.0 }) {}

Ray::~Ray()
{
}