#include "./include/Ray.h"


Ray::Ray(glm::vec3& start, glm::vec3& direction, glm::vec3& colour) :
	_startPos(start), _direction(direction), _colour(glm::vec3{ 0.0 , 0.0 , 0.0 }) {}

glm::vec3 Ray::getDirection() const{
	return _direction;
}
glm::vec3 Ray::getStartPos() const {
	return _startPos;
}

Ray::~Ray()
{

}