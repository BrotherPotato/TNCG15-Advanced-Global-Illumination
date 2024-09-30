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

	// add try catch or if statement


	render << "P3" << std::endl;
	render << pixelsPerSide << " " << pixelsPerSide << std::endl;
	render << "255" << std::endl;
	int counter = 0;

	for (std::vector<Pixel>& a : pixels)
	{
		for (Pixel b : a) {
			/*if (counter == 255) {
				counter = 0;
			}
			counter++;
			render << counter / 3 << " " << counter / 2 << " " << counter << std::endl;*/
			render << b;
		}
	}

	/*for (size_t i = 0; i < pixelsPerSide; i++)
	{
		for (size_t y = 0; y < pixelsPerSide; y++)
		{
			
		}
	}*/


	render.close();
	std::cout << "JA";
};