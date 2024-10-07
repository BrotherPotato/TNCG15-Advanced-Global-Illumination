#include "./include/Ray.h"


Ray::Ray(glm::vec3& start, glm::vec3& direction, CustomColor& colour) :
	_startPos(start), _direction(direction), _colour(CustomColor{ 0.0 , 0.0 , 0.0 }) {}

glm::vec3 Ray::getDirection() const{
	return _direction;
}
glm::vec3 Ray::getStartPos() const {
	return _startPos;
}

Ray::~Ray()
{

}