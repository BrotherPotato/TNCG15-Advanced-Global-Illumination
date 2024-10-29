

//#include <iostream>
#include "glm.hpp"
#include "./include/main.h"
#include "./include/Camera.h"
#include "./include/Scene.h"
//#include "./include/ColourRGB.h"


// camera save to ppm file

int main() {

	std::cout << "hello world\n";

	// skapa scen
	Scene scene;

	// skapa kamera
	Camera camera = Camera(&scene);

	// bygg upp innehållet i scenen, bara en box för tillfället
	//glm::vec3 boxPos{ glm::vec3(10,0,0) };
	//Material lamRed{ Material::_LambertianReflector ,ColourRGB(1,0,0) };
	//scene.createBox(boxPos, 2, 2, 2, lamRed);

	//// test triangel
	//glm::vec3 v0(10, 1, -1);
	//glm::vec3 v1(10, -1, 0);
	//glm::vec3 v2(10, 1, 1);
	//Material lamBlue{ Material::_LambertianReflector ,ColourRGB(0,0,1) };
	//scene.createTriangle(v0, v1, v2, lamBlue);

	//glm::vec3 v3(9, 1, -1);
	//glm::vec3 v4(9, -1, 0);
	//glm::vec3 v5(9, 1, 1);
	////scene.createTriangle(v3, v4, v5, lamRed);

	//// light source
	//glm::vec3 pbl{ glm::vec3(5, -9, 1) };
	//glm::vec3 ptr{ glm::vec3(10, -10, -1) };
	//scene.createLightSource(pbl, ptr);


	// Real scene
	glm::vec3 T0(13, 0, 5);
	glm::vec3 T1(13, 0, -5);
	glm::vec3 T2(10, -6, 5);
	glm::vec3 T3(10, -6, -5);
	glm::vec3 T4(10, 6, 5);
	glm::vec3 T5(10, 6, -5);

	glm::vec3 T6(-3, 0, 5);
	glm::vec3 T7(-3, 0, -5);
	glm::vec3 T8(0, -6, 5);
	glm::vec3 T9(0, -6, -5);
	glm::vec3 T10(0, 6, 5);
	glm::vec3 T11(0, 6, -5);

	//Roof
	Material RoofBlue{ Material::_LambertianReflector ,ColourRGB(0,0,1) };
	scene.createTriangle(T6, T8, T10, RoofBlue); // green in whiteboard
	scene.createTriangle(T8, T2, T10, RoofBlue); // blue in whiteboard
	scene.createTriangle(T2, T4, T10, RoofBlue); // orange in whiteboard
	scene.createTriangle(T2, T0, T4, RoofBlue); // red in whiteboard

	//Floor
	Material FloorGrey{ Material::_LambertianReflector ,ColourRGB(0.3,0.3,0.3) };
	scene.createTriangle(T7, T9, T11, FloorGrey); // green in whiteboard
	scene.createTriangle(T9, T3, T11, FloorGrey); // blue in whiteboard
	scene.createTriangle(T3, T5, T11, FloorGrey); // orange in whiteboard
	scene.createTriangle(T3, T1, T5, FloorGrey); // red in whiteboard

	// Wall behind camera
	Material WallBehindBlack{ Material::_LambertianReflector ,ColourRGB(0,0,0) };
	scene.createTriangle(T10, T7, T11, WallBehindBlack); // green in whiteboard
	scene.createTriangle(T10, T6, T7, WallBehindBlack); // blue in whiteboard
	scene.createTriangle(T7, T6, T8, WallBehindBlack); // orange in whiteboard
	scene.createTriangle(T9, T7, T8, WallBehindBlack); // red in whiteboard

	// Wall left
	Material WallLeftPurple{ Material::_LambertianReflector ,ColourRGB(0.5,0,0.5) };
	scene.createTriangle(T10, T11, T5, WallLeftPurple); // green in whiteboard
	scene.createTriangle(T5, T4, T10, WallLeftPurple); // magenta in whiteboard

	// Wall right
	Material WallRightCyan{ Material::_LambertianReflector ,ColourRGB(0,0.5,0.5) };
	scene.createTriangle(T3, T9, T8, WallRightCyan); // green in whiteboard
	scene.createTriangle(T8, T2, T3, WallRightCyan); // magenta in whiteboard

	// Wall infront camera
	Material WallFrontRed{ Material::_LambertianReflector ,ColourRGB(1,0,0) };
	scene.createTriangle(T4, T5, T1, WallFrontRed); // green in whiteboard
	scene.createTriangle(T1, T0, T4, WallFrontRed); // blue in whiteboard
	scene.createTriangle(T2, T0, T1, WallFrontRed); // orange in whiteboard
	scene.createTriangle(T1, T3, T2, WallFrontRed); // red in whiteboard

	// "transparent"
	//glm::vec3 boxPos{ glm::vec3(5,0,0) };
	//Material lamRed{ Material::_Transparent ,ColourRGB(1,0,0) };
	//scene.createBox(boxPos, 1, 1, 1, lamRed);

	glm::vec3 spherePos{ 5,0,0 };
	Material purpel{ Material::_LambertianReflector, ColourRGB(1,1,1) };
	scene.createSphere(spherePos, 1, purpel);

	// Only lightsource
	glm::vec3 L0(1, 1, 1);
	glm::vec3 L1(1, 1, 1);
	scene.createLightSource(L0, L1);



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