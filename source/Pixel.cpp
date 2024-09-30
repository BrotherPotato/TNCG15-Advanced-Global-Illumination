#include <iostream>
#include "./include/Pixel.h"

Pixel::Pixel() : _colour(glm::vec3(0.3, 0.2, 1.0)){}; // between 0 and 1

void Pixel::setColour(glm::vec3& colour) {
	_colour = colour;
}

glm::vec3 Pixel::getColour() const {
	return _colour;
}

std::ostream& operator<<(std::ostream& write, const Pixel& currentPixel)
{
	return write << currentPixel.getColour().r * 255.0 << " " << currentPixel.getColour().g * 255.0 << " " << currentPixel.getColour().b * 255.0 << std::endl;
}
