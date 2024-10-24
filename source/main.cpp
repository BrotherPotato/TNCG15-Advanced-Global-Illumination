

//#include <iostream>
#include "glm.hpp"
#include "./include/main.h"
#include "./include/Camera.h"
#include "./include/Scene.h"
//#include "./include/ColourRGB.h"


// camera save to ppm file

int main() {

	std::cout << "hello world";

	// skapa scen
	Scene scene;

	// skapa kamera
	Camera camera = Camera(&scene);

	// bygg upp innehållet i scenen, bara en box för tillfället
	glm::vec3 boxPos{ glm::vec3(0,0,10) };
	//ColourRGB boxRed{ ColourRGB(0.5,0,0)};
	Material boxRed{ Material::_LambertianReflector ,ColourRGB(0.5,0,0) };
	scene.createBox(boxPos, 1, 1, 1, boxRed);

	// skjut rays
	camera.emitRays();

	// rays tillhör kameran, objekten tillhör scenen...
	// kolla intersektions?

	//for (Ray r : a.getRays()) {
	//	for (Object* o : s.getObjects()) {
	//		
	//	}
	//}

	

	// render
	camera.writeToPPM();
}

// jag såg en skepnad bortom molnen, strålar skjöts ut ur hans ögon, 
// ett regn av ljus krossade himlavalvet och sprickorna föll ner över skapelsen 
// berg föll samman i högar av damm, människor med, strålarna tog deras liknelse