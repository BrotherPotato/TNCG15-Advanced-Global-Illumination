

//#include <iostream>
#include "glm.hpp"
#include "./include/main.h"
#include "./include/Camera.h"
#include "./include/Scene.h"

int main() {

	// skapa scen
	Scene scene;

	// skapa kamera
	Camera camera = Camera(&scene, 800, 100);

	// Alla lambertian ytors reflektans.
	// Lågt värde = snabbare rendering, mindre färgspridning.
	float reflectivity = 1.0f; // 1.0 kan ge stack overflow om scenen är för vit

	float intensity = 50.0f; // allmän ljusstyrka för ljuskällorna
	ColourRGB lightColour = ColourRGB(1); // Om man vill t.ex. ha varmare ljus

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

	// Cornell type shit
	ColourRGB roofColour = ColourRGB(0, 0, 1);			// Blue
	ColourRGB floorColour = ColourRGB(1, 1, 0);			// Yellow
	ColourRGB backColour = ColourRGB(0, 1, 0);			// Green
	ColourRGB leftColour = ColourRGB(1, 0, 1);			// Purple
	ColourRGB frontColour = ColourRGB(1, 0, 0);			// Red
	ColourRGB rightColour = ColourRGB(0, 1, 1);			// Cyan

	//Roof
	Material RoofBlue{ Material::_LambertianReflector, roofColour, reflectivity };
	scene.createTriangle(T10, T8, T6, RoofBlue); // green in whiteboard
	scene.createTriangle(T10, T2, T8, RoofBlue); // blue in whiteboard
	scene.createTriangle(T10, T4, T2, RoofBlue); // orange in whiteboard
	scene.createTriangle(T4, T0, T2, RoofBlue); // red in whiteboard

	//Floor
	Material FloorGrey{ Material::_LambertianReflector, floorColour, reflectivity };
	scene.createTriangle(T7, T9, T11, FloorGrey); // green in whiteboard
	scene.createTriangle(T9, T3, T11, FloorGrey); // blue in whiteboard
	scene.createTriangle(T3, T5, T11, FloorGrey); // orange in whiteboard
	scene.createTriangle(T3, T1, T5, FloorGrey); // red in whiteboard

	// Wall behind camera
	Material WallBehindBlack{ Material::_LambertianReflector, backColour, reflectivity };
	scene.createTriangle(T10, T7, T11, WallBehindBlack); // green in whiteboard
	scene.createTriangle(T10, T6, T7, WallBehindBlack); // blue in whiteboard
	scene.createTriangle(T7, T6, T8, WallBehindBlack); // orange in whiteboard
	scene.createTriangle(T9, T7, T8, WallBehindBlack); // red in whiteboard

	// Wall left
	Material WallLeftPurple{ Material::_LambertianReflector, leftColour, reflectivity };
	scene.createTriangle(T10, T11, T5, WallLeftPurple); // green in whiteboard
	scene.createTriangle(T5, T4, T10, WallLeftPurple); // magenta in whiteboard

	// Wall right
	Material WallRightCyan{ Material::_LambertianReflector, rightColour, reflectivity };
	scene.createTriangle(T3, T9, T8, WallRightCyan); // green in whiteboard
	scene.createTriangle(T8, T2, T3, WallRightCyan); // magenta in whiteboard

	// Wall infront camera
	Material WallFrontRed{ Material::_LambertianReflector, frontColour, reflectivity };
	scene.createTriangle(T4, T5, T1, WallFrontRed); // green in whiteboard
	scene.createTriangle(T1, T0, T4, WallFrontRed); // blue in whiteboard
	scene.createTriangle(T2, T0, T1, WallFrontRed); // orange in whiteboard
	scene.createTriangle(T1, T3, T2, WallFrontRed); // red in whiteboard

	// Andra objekt i scenen:

	glm::vec3 spherePos1{ 5, 1.75, 1 };
	Material mirror{ Material::_MirrorReflection, ColourRGB(1) };
	scene.createSphere(spherePos1, 1.5, mirror);

	glm::vec3 spherePos2{ 5,-1.75, 1  };
	Material glass{ Material::_Transparent, ColourRGB(1) };
	scene.createSphere(spherePos2, 1.5, glass);

	glm::vec3 squarePos{ 7, -3, -3 };
	Material square{ Material::_LambertianReflector, ColourRGB(1), reflectivity };
	scene.createBox(squarePos, 1.5, 1.5, 1.5, square);

	glm::vec3 tetraPos{ 7, 3, -3 };
	Material tetrahedron{ Material::_LambertianReflector, ColourRGB(1), reflectivity };
	scene.createTetrahedron(tetraPos, 2.5, tetrahedron);

	// Light Sources
	double distanceFromCenter = 1.0;
	double lightHeight = 4.9;
	glm::vec3 L0(6 + distanceFromCenter, distanceFromCenter, lightHeight);
	glm::vec3 L1(6 - distanceFromCenter, distanceFromCenter, lightHeight);
	glm::vec3 L2(6 - distanceFromCenter, -distanceFromCenter, lightHeight);
	glm::vec3 L3(6 + distanceFromCenter, -distanceFromCenter, lightHeight);
	scene.createLightSourceTriangle(L3, L0, L1, lightColour, intensity);
	scene.createLightSourceTriangle(L1, L2, L3, lightColour, intensity);

	// skjut rays
	camera.emitRays();

	// render
	camera.writeToPPM();
}