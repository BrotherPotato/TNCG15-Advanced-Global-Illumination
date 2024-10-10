

//#include <iostream>
#include "glm.hpp"
#include "./include/main.h"
#include "./include/Camera.h"
#include "./include/Scene.h"
#include "./include/ColourRGB.h"


// camera save to ppm file

int main() {

	std::cout << "hello world";

	// skapa kamera
	Camera a;

	// skapa scen
	Scene s;

	// bygg upp inneh�llet i scenen, bara en box f�r tillf�llet
	glm::vec3 boxPos{ glm::vec3(0,0,10) };
	//ColourRGB boxRed{ ColourRGB(0.5,0,0)};
	Material boxRed{ Material::_LambertianReflector ,ColourRGB(0.5,0,0) };
	s.createBox(boxPos, 1, 1, 1, boxRed);

	// skjut rays
	a.emitRays();

	// rays tillh�r kameran, objekten tillh�r scenen...
	// kolla intersektions?

	// render
	a.writeToPPM();


}