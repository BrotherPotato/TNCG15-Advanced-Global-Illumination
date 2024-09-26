#pragma once

#include "glm.hpp"

class Pixel
{
public:
	Pixel();
	~Pixel();

	void setColour(glm::vec3& colour);
	glm::vec3 getColour() const;

private:
	glm::vec3 _colour;
};
