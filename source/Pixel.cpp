#include <iostream>
#include "./include/Pixel.h"

Pixel::Pixel() : _colour(ColourRGB(0.30000000000001, 0.2, 1.0)){}; // between 0 and 1

void Pixel::setColour(ColourRGB colour) {
	_colour = colour;
}

void Pixel::addColour(ColourRGB colour) {
	_colour.setR(_colour.getR() + colour.getR());
	_colour.setG(_colour.getG() + colour.getG());
	_colour.setB(_colour.getB() + colour.getB());
}

ColourRGB Pixel::getColour() const {
	return _colour;
}

std::ostream& operator<<(std::ostream& write, const Pixel& currentPixel)
{
	int R = std::round(currentPixel.getColour().getR() * 255.0);
	int G = std::round(currentPixel.getColour().getG() * 255.0);
	int B = std::round(currentPixel.getColour().getB() * 255.0);

	return write << R << " " << G << " " << B << std::endl;
}
