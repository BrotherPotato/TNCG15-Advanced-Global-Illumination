

#include "glm.hpp"
#include "./include/ColourRGB.h"
#include "./include/Ray.h"
#include "./include/Camera.h"




void Camera::writeToPPM() {

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

	std::cout << _pixels.size();
	std::cout << _pixels[0].size() << std::endl;

	int counter = 0;
	int onePercentage = 800 * 800 / 100;

	std::cout << "<" << std::setw(100) << ">" << std::endl;
	std::cout << "<";

	for (std::vector<Pixel>& pixelRow : _pixels)
	{
		for (Pixel& currentPixel : pixelRow) {

			render << currentPixel;
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

	int totrays = 0;
	double pixelWidth = 2.0 / (double)_pixelsPerSide; // 0.0025
	double oneless = 1.0 - (1.0 / (double)_pixelsPerSide); // 0.99875

	// 800 rader
	for (int i = 0; i < _pixels.size(); i++) {

		// 800 kolumner
		for (int j = 0; j < _pixels[i].size(); j++) {

			glm::vec3 endPos = glm::vec3(0, i * pixelWidth - oneless, j * pixelWidth - oneless); // lecture 4 slide 8
			glm::vec3 dir = endPos - _cameraPosition;

			ColourRGB pixelCol;

			// skjut flera rays genom samma pixel
			for (int k = 0; k < _numberOfRaysPerPixel; k++) {

				totrays++;
				//std::cout << "\nRay: " << totrays << "\t";

				Ray ray{ getScene(), _cameraPosition, dir, ColourRGB() };

				if (k == 0) pixelCol = ray.getColour();
				else pixelCol.mixColours(ray.getColour());
			}

			_pixels[i][j].setColour(pixelCol);

			// testing testing
			//double ig = i / (double)_pixels.size();
			//double jg = j / (double)_pixels[i].size();
			////std::cout << "\n" << ig << " : " << jg;
			//_pixels[i][j].setColour(CustomColour(ig, jg, 0));
		}
		std::cout << "Row " << i << " done! \n";
	}
}