#pragma once
#include "Pixel.h"
#include <vector>

#include <fstream>
#include <iostream>

#include <iomanip>



// double array of pixels

class Camera {
public:
	Camera() {
		_pixels = {std::vector<std::vector<Pixel>>(_pixelsPerSide, std::vector<Pixel>(_pixelsPerSide))};
	};


	~Camera() = default;

	void writeToPPM();

private:
	int _pixelsPerSide = 800;
	std::vector<std::vector<Pixel>> _pixels;
	glm::vec3 _cameraPosition = glm::vec3(-1.0,0.0,0);
	int _numberOfRaysPerPixel = 50;



};