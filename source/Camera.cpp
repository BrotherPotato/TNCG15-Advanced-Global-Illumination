

#include "glm.hpp"
#include "./include/ColourRGB.h"
#include "./include/Ray.h"
#include "./include/Camera.h"
#include <thread>



void Camera::writeToPPM() {

	this->normalizePixelColours();

	//https://en.wikipedia.org/wiki/Netpbm
	/* example from wikipedia
	P3
	# "P3" means this is a RGB color image in ASCII
	# "3 2" is the width and height of the image in pixels
	# "255" is the maximum value for each color
	# This, up through the "255" line below are the header.
	# Everything after that is the image data: RGB triplets.
	# In order: red, green, blue, yellow, white, and black.
	3 2
	255
	255   0   0
	  0 255   0
	  0   0 255
	255 255   0
	255 255 255
	  0   0   0
	*/
	std::ofstream render("../render.ppm");

	if (!render) {
		std::cout << "NEJ";
		return;
	}

	render << "P3" << std::endl;
	render << _pixelsPerSide << " " << _pixelsPerSide << std::endl;
	render << "255" << std::endl;

	std::cout << "Image size:" << _pixels.size() << "x";
	std::cout << _pixels[0].size() << std::endl;

	int counter = 0;
	int onePercentage = _pixelsPerSide * _pixelsPerSide / 100;
	std::cout << "Writing to file:\n";
	std::cout << "<" << std::setw(100) << ">" << std::endl;
	std::cout << "<";


	for (int i = 0; i < _pixels.size(); i++) {

		// 800 kolumner
		for (int j = 0; j < _pixels[i].size(); j++) {
			// flips the image
			render << _pixels[_pixels[i].size() - j - 1][_pixels.size() - i - 1];
			//std::cout << std::setprecision(15) << currentPixel.getColour().getR();
			if (counter >= onePercentage) {
				counter = 0;
				std::cout << "-";
			}

			counter++;
		}
	
	}

	std::cout << ">";

	render.close();
};

void Camera::emitRays() {

	double pixelWidth = 2.0 / (double)_pixelsPerSide; // 0.0025
	double oneless = 1.0 - (1.0 / (double)_pixelsPerSide); // 0.99875

	int counter = 0;
	int onePercentage = _pixelsPerSide * _pixelsPerSide / 100;
	std::cout << "Emitting " << _pixelsPerSide * _pixelsPerSide * _numberOfRaysPerPixel << " rays:\n";
	std::cout << "<" << std::setw(100) << ">" << std::endl;
	std::cout << "<";

	// 800 rader
	for (int i = 0; i < _pixels.size(); i++) {

		// 800 kolumner
		for (int j = 0; j < _pixels[i].size(); j++) {

			glm::vec3 endPos = glm::vec3(0, i * pixelWidth - oneless, j * pixelWidth - oneless); // lecture 4 slide 8
			glm::vec3 dir = endPos - _cameraPosition;

			ColourRGB pixelCol;
			std::vector<ColourRGB> cols;

			// skjut flera rays genom samma pixel
			for (int k = 0; k < _numberOfRaysPerPixel; k++) {
				
				Ray ray{ getScene(), _cameraPosition, dir, ColourRGB(1), nullptr, false };
				pixelCol.addColour(ray.pixelRadiance());
				cols.push_back(ray.pixelRadiance());
			}
			//pixelCol = ColourRGB().mixColours(cols);
			pixelCol.divideColour(_numberOfRaysPerPixel);
			_pixels[i][j].setColour(pixelCol);
			

			if (counter >= onePercentage) {
				counter = 0;
				std::cout << "-";
			}

			counter++;
		}
		
	}
	std::cout << ">" << std::endl;
}

// g�r inte s� mycket d� st�rsta kommer va 1
void Camera::normalizePixelColours() {
	double maxRGBValue = 0;
	// 800 rader
	for (int i = 0; i < _pixels.size(); i++) {

		// 800 kolumner
		for (int j = 0; j < _pixels[i].size(); j++) {
			if (_pixels[i][j].getColour().getR() > maxRGBValue) {
				maxRGBValue = _pixels[i][j].getColour().getR();
			}
			if (_pixels[i][j].getColour().getG() > maxRGBValue) {
				maxRGBValue = _pixels[i][j].getColour().getG();
			}
			if (_pixels[i][j].getColour().getB() > maxRGBValue) {
				maxRGBValue = _pixels[i][j].getColour().getB();
			}		
		}
	}
	std::cout << "normalizePixelColours: " << maxRGBValue << std::endl;
	// 800 rader
	for (int i = 0; i < _pixels.size(); i++) {

		// 800 kolumner
		for (int j = 0; j < _pixels[i].size(); j++) {
			//std::cout << _pixels[i][j].getColour().getR() << " ";
			//_pixels[i][j].getColour().divideColour(maxRGBValue);
			_pixels[i][j].setColour(_pixels[i][j].getColour().divideColour(maxRGBValue));
			//std::cout << _pixels[i][j].getColour().getR() << std::endl;
			_pixels[i][j].validateColour();
		}
	}
}

//##################################################################################################################################################################


void Camera::renderRangeOfColums(Scene* scene, int start_colum, int end_colum, int threads_done, int num_threads) {

	double pixelWidth = 2.0 / (double)_pixelsPerSide; // 0.0025
	double oneless = 1.0 - (pixelWidth / 2.0); // 0.99875
	
	glm::vec3 endPos;

	for (int i = start_colum; i < end_colum; i++) {

		// 800 kolumner
		for (int j = 0; j < _pixels[i].size(); j++) {

			endPos.x = 0;
			endPos.y = i * pixelWidth - oneless;
			endPos.z = j * pixelWidth - oneless;

			glm::vec3 dir = endPos - _cameraPosition;

			ColourRGB pixelCol;
			std::vector<ColourRGB> cols;

			// skjut flera rays genom samma pixel
			for (int k = 0; k < _numberOfRaysPerPixel; k++) {

				Ray ray{ getScene(), _cameraPosition, dir, ColourRGB(1), nullptr, false };
				pixelCol = (ray.pixelRadiance());
				cols.push_back(pixelCol);
			}
			pixelCol = ColourRGB().mixColours(cols);
			_pixels[i][j].setColour(pixelCol);

		}
	}
	std::cout << "THREAD " << std::setw(5) << std::fixed << std::setprecision(1) << threads_done+1 << " DONE!\n";
}


void Camera::render(Scene* scene) {


	int threads_done = 0;

	//unsigned int num_threads = std::thread::hardware_concurrency()-1;
	//if (num_threads == 0) num_threads = 1;

	unsigned int num_threads = 10;
	std::cout << "Rendering using " << num_threads << " threads:\n";
	std::cout << "STARTING...\n";

	std::vector<std::thread> threads;
	threads.reserve(num_threads);

	int startCol = 0;
	int endCol = 0;

	int colums_per_thread = _pixels.size() / num_threads;
	for (unsigned int i = 0; i < num_threads; i++) {

		startCol = i * colums_per_thread;
		endCol = (i + 1) * colums_per_thread;

		//if (i == num_threads - 1) endCol = _pixels.size();
		//else endCol = (i + 1) * colums_per_thread;

		threads.emplace_back(std::thread([=]() {renderRangeOfColums(scene, startCol, endCol, i, num_threads);}));
	}
	for (unsigned int i = 0; i < num_threads; i++) {
		threads[i].join();
	}
	std::cout << "Rendering complete!\n";
}