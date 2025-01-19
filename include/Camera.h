#pragma once
#include "Pixel.h"
#include "Ray.h"
#include <vector>

#include <fstream>
#include <iostream>

#include <iomanip>



// double array of pixels

class Camera {
public:
	Camera(Scene* scene, int resolution, int samples) {
		_pixelsPerSide = resolution;
		_pixels = {std::vector<std::vector<Pixel>>(_pixelsPerSide, std::vector<Pixel>(_pixelsPerSide))};
		_scene = scene;
		_numberOfRaysPerPixel = samples;
	};


	~Camera() = default;

	void writeToPPM();

	// Loop through all pixels, shoot a ray through each pixel.
	void emitRays();

	//std::vector<Ray> getRays() { return _rays; };

	Scene* getScene() { return _scene; };

	void normalizePixelColours();

private:
	unsigned _pixelsPerSide = 800;
	std::vector<std::vector<Pixel>> _pixels;
	const glm::vec3 _cameraPosition = glm::vec3(-1.0,0.0,0); // eye poisition enligt slides
	unsigned _numberOfRaysPerPixel = 1;

	std::vector<Ray> _rays;

	Scene* _scene;
};