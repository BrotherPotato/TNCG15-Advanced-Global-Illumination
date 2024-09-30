#pragma once

#include "glm.hpp"
#include <iostream>

class Pixel
{
public:
	Pixel();
	~Pixel() = default;

	void setColour(glm::vec3& colour);
	glm::vec3 getColour() const;

	friend std::ostream& operator<< (std::ostream&, const Pixel& currentPixel);

private:
	glm::vec3 _colour;
};
