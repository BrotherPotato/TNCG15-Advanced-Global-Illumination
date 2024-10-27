

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
	glm::vec3 boxPos{ glm::vec3(0,0,0) };
	Material lamRed{ Material::_LambertianReflector ,ColourRGB(1,0,0) };
	scene.createBox(boxPos, 50, 50, 50, lamRed);

	// test triangel
	glm::vec3 v0(10, 1, -1);
	glm::vec3 v1(10, -1, 0);
	glm::vec3 v2(10, 1, 1);
	Material lamBlue{ Material::_LambertianReflector ,ColourRGB(0,0,1) };
	scene.createTriangle(v0, v1, v2, lamBlue);

	// light source
	glm::vec3 pbl{ glm::vec3(5, -9, 1) };
	glm::vec3 ptr{ glm::vec3(10, -10, -1) };
	scene.createLightSource(pbl, ptr);

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