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
	Camera(Scene* scene, int resolution) {
		_pixelsPerSide = resolution;
		_pixels = {std::vector<std::vector<Pixel>>(_pixelsPerSide, std::vector<Pixel>(_pixelsPerSide))};
		_scene = scene;
	};


	~Camera() = default;

	void writeToPPM();

	// Loop through all pixels, shoot a ray through each pixel.
	void emitRays(int raysPerPixel);


	std::vector<Ray> getRays() { return _rays; };

	Scene* getScene() { return _scene; };

	void normalizePixelColours();

	void renderRangeOfColums(Scene* scene, int start_colum, int end_colum, int threads_done, int num_threads);
	void render(Scene* scene);

private:
	unsigned _pixelsPerSide = 800;
	std::vector<std::vector<Pixel>> _pixels;
	const glm::vec3 _cameraPosition = glm::vec3(-1.0,0.0,0); // eye poisition enligt slides
	const unsigned _numberOfRaysPerPixel = 100;

	std::vector<Ray> _rays;

	Scene* _scene;
};