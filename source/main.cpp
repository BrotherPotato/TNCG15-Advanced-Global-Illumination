

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
	Camera camera = Camera(&scene, 800);

	// allmän reflektans för diffusa ytor, för hög -> stack overflow, 0.9f är högsta
	// Ju lägre, ju mer spegelliknande blir ytan. Ju högre, ju fler spiralliknande ljuseffekter kommer på ytorna.
	float reflectance = 0.5f;		

	// allmän ljusstyrka för ljuskällorna
	float intensity = 10.0f;		

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
	Material RoofBlue{ Material::_LambertianReflector ,ColourRGB(0,0,1), reflectance };
	scene.createTriangle(T10, T8, T6, RoofBlue); // green in whiteboard
	scene.createTriangle(T10, T2, T8, RoofBlue); // blue in whiteboard
	scene.createTriangle(T10, T4, T2, RoofBlue); // orange in whiteboard
	scene.createTriangle(T4, T0, T2, RoofBlue); // red in whiteboard

	//Floor
	Material FloorGrey{ Material::_LambertianReflector ,ColourRGB(1,1,0), reflectance };
	scene.createTriangle(T7, T9, T11, FloorGrey); // green in whiteboard
	scene.createTriangle(T9, T3, T11, FloorGrey); // blue in whiteboard
	scene.createTriangle(T3, T5, T11, FloorGrey); // orange in whiteboard
	scene.createTriangle(T3, T1, T5, FloorGrey); // red in whiteboard

	// Wall behind camera
	Material WallBehindBlack{ Material::_LambertianReflector ,ColourRGB(0,1,0), reflectance };
	scene.createTriangle(T10, T7, T11, WallBehindBlack); // green in whiteboard
	scene.createTriangle(T10, T6, T7, WallBehindBlack); // blue in whiteboard
	scene.createTriangle(T7, T6, T8, WallBehindBlack); // orange in whiteboard
	scene.createTriangle(T9, T7, T8, WallBehindBlack); // red in whiteboard

	// Wall left
	Material WallLeftPurple{ Material::_LambertianReflector ,ColourRGB(1,0,1), reflectance };
	scene.createTriangle(T10, T11, T5, WallLeftPurple); // green in whiteboard
	scene.createTriangle(T5, T4, T10, WallLeftPurple); // magenta in whiteboard

	// Wall right
	Material WallRightCyan{ Material::_LambertianReflector ,ColourRGB(0,1,1), reflectance };
	scene.createTriangle(T3, T9, T8, WallRightCyan); // green in whiteboard
	scene.createTriangle(T8, T2, T3, WallRightCyan); // magenta in whiteboard

	// Wall infront camera
	Material WallFrontRed{ Material::_LambertianReflector ,ColourRGB(1,0,0), reflectance };
	scene.createTriangle(T4, T5, T1, WallFrontRed); // green in whiteboard
	scene.createTriangle(T1, T0, T4, WallFrontRed); // blue in whiteboard
	scene.createTriangle(T2, T0, T1, WallFrontRed); // orange in whiteboard
	scene.createTriangle(T1, T3, T2, WallFrontRed); // red in whiteboard


	glm::vec3 spherePos1{ 5, 2,0 };
	Material mirr{ Material::_MirrorReflection, ColourRGB(1,1,1) };
	scene.createSphere(spherePos1, 1.5, mirr);

	glm::vec3 spherePos2{ 5,-2,0 };
	Material purpel{ Material::_Transparent, ColourRGB(1,1,1) };
	scene.createSphere(spherePos2, 1.5, purpel);

	double distanceFromCenter = 1;
	double lightHeight = 4.99;
	glm::vec3 L0(5 + distanceFromCenter, distanceFromCenter, lightHeight);
	glm::vec3 L1(5 - distanceFromCenter, distanceFromCenter, lightHeight);
	glm::vec3 L2(5 - distanceFromCenter, -distanceFromCenter, lightHeight);
	glm::vec3 L3(5 + distanceFromCenter, -distanceFromCenter, lightHeight);

	scene.createLightSourceTriangle(L3, L0, L1, intensity);
	scene.createLightSourceTriangle(L1, L2, L3, intensity);



	// skjut rays
	camera.emitRays();
	//camera.render(&scene);

	// render
	camera.writeToPPM();
}

// jag såg en skepnad bortom molnen, strålar skjöts ut ur hans ögon, 
// ett regn av ljus krossade himlavalvet och sprickorna föll ner över skapelsen 
// berg föll samman i högar av damm, människor med, strålarna tog deras liknelse