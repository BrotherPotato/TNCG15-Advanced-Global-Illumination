#pragma once

#include "glm.hpp"


#include <iostream>

#include "./include/CustomColor.h"

class Pixel
{
public:
	Pixel();
	~Pixel() = default;

	void setColour(CustomColor& colour);
	CustomColor getColour() const;

	friend std::ostream& operator<< (std::ostream&, const Pixel& currentPixel);

private:
	CustomColor _colour;
};
