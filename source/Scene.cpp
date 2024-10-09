#include "./include/Scene.h"

Scene::Scene(){

}

void Scene::createBox(glm::vec3 pos, double width, double length, double height, CustomColour colour) {

	width /= 2;
	length /= 2;
	height /= 2;

	// alla hörn
	glm::vec3 p0(pos.x - width, pos.y - length, pos.z - height);
	glm::vec3 p1(pos.x + width, pos.y - length, pos.z - height);
	glm::vec3 p2(pos.x - width, pos.y + length, pos.z - height);
	glm::vec3 p3(pos.x + width, pos.y + length, pos.z - height);
	glm::vec3 p4(pos.x - width, pos.y - length, pos.z + height);
	glm::vec3 p5(pos.x + width, pos.y - length, pos.z + height);
	glm::vec3 p6(pos.x - width, pos.y + length, pos.z + height);
	glm::vec3 p7(pos.x + width, pos.y + length, pos.z + height);

	// alla trianglar
	Triangle t0(p0, p3, p1, colour);
	Triangle t1(p0, p2, p3, colour);
	Triangle t2(p1, p4, p0, colour);
	Triangle t3(p1, p5, p4, colour);
	Triangle t4(p4, p2, p0, colour);
	Triangle t5(p4, p6, p2, colour);
	Triangle t6(p1, p3, p7, colour);
	Triangle t7(p1, p7, p5, colour);
	Triangle t8(p7, p2, p6, colour);
	Triangle t9(p7, p3, p2, colour);
	Triangle t10(p4, p5, p7, colour);
	Triangle t11(p4, p7, p6, colour);

	// lägg till i listan
	// funkar inte för tillfället, men ska göra det
	objects.push_back(t0);
	objects.push_back(t1);
	objects.push_back(t2);
	objects.push_back(t3);
	objects.push_back(t4);
	objects.push_back(t5);
	objects.push_back(t6);
	objects.push_back(t7);
	objects.push_back(t8);
	objects.push_back(t9);
	objects.push_back(t10);
	objects.push_back(t11);


}