#include <iostream>
#include "./include/Pixel.h"

Pixel::Pixel() : _colour(glm::vec3(0.0, 0.0, 0.0)){};

void Pixel::setColour(glm::vec3& colour) {
	_colour = colour;
}

glm::vec3 Pixel::getColour() const {
	return _colour;
}