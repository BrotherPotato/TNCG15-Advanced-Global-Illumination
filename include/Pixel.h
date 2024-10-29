#pragma once

#include "glm.hpp"


#include <iostream>

#include "./include/ColourRGB.h"

class Pixel
{
public:
	Pixel();
	~Pixel() = default;

	void setColour(ColourRGB colour);
	void addColour(ColourRGB colour);
	ColourRGB getColour() const;
	void validateColour();

	friend std::ostream& operator<< (std::ostream&, const Pixel& currentPixel);

private:
	ColourRGB _colour;
};
