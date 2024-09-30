#pragma once
#include "Pixel.h"
#include <vector>

#include <fstream>
#include <iostream>


// double array of pixels

class Camera {
public:
	Camera() {
		pixels = {std::vector<std::vector<Pixel>>(pixelsPerSide, std::vector<Pixel>(pixelsPerSide))};
	};


	~Camera() = default;

	void writeToPPM();

private:
	int pixelsPerSide = 800;
	std::vector<std::vector<Pixel>> pixels;



};