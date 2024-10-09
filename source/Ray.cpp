#include "./include/Ray.h"


Ray::Ray(glm::vec3 start, glm::vec3 direction, CustomColour colour) {
	_startPos = start;
	_direction = direction;
	_colour = CustomColour();
}

glm::vec3 Ray::getDirection() const{
	return _direction;
}
glm::vec3 Ray::getStartPos() const {
	return _startPos;
}

Ray::~Ray()
{

}