

//#include <iostream>
//#include "glm.hpp"
#include "./include/main.h"
#include "./include/Camera.h"


// camera save to ppm file

int main() {

	std::cout << "hello world";

	Camera a;
	a.emitRays();
	a.writeToPPM();


}