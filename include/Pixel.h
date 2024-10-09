#pragma once

#include "glm.hpp"


#include <iostream>

#include "./include/CustomColour.h"

class Pixel
{
public:
	Pixel();
	~Pixel() = default;

	void setColour(CustomColour colour);
	void addColour(CustomColour colour);
	CustomColour getColour() const;

	friend std::ostream& operator<< (std::ostream&, const Pixel& currentPixel);

private:
	CustomColour _colour;
};
