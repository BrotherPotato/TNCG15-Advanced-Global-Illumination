#include "./include/Scene.h"

Scene::Scene(){

}


void Scene::createBox(glm::vec3& pos, double width, double length, double height, ColourRGB& colour) {

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
	_Objects.push_back(new Triangle(t0));
	_Objects.push_back(new Triangle(t1));
	_Objects.push_back(new Triangle(t2));
	_Objects.push_back(new Triangle(t3));
	_Objects.push_back(new Triangle(t4));
	_Objects.push_back(new Triangle(t5));
	_Objects.push_back(new Triangle(t6));
	_Objects.push_back(new Triangle(t7));
	_Objects.push_back(new Triangle(t8));
	_Objects.push_back(new Triangle(t9));
	_Objects.push_back(new Triangle(t10));
	_Objects.push_back(new Triangle(t11));
}

void Scene::createPlane(glm::vec3& posBotLeft, glm::vec3& posTopRight, ColourRGB& colour) {
	// typ så om y är upp kommer inte ihåg
	glm::vec3 p0(posBotLeft);
	glm::vec3 p1(posTopRight.x, posBotLeft.y, posTopRight.z);
	glm::vec3 p2(posBotLeft.x, posTopRight.y, posBotLeft.z);
	glm::vec3 p3(posTopRight);

	Triangle t0(p0, p3, p1, colour);
	Triangle t1(p0, p2, p3, colour);

	_Objects.push_back(new Triangle(t0));
	_Objects.push_back(new Triangle(t1));
}

void Scene::createSphere(glm::vec3& pos, double radius, ColourRGB& colour) {
	_Objects.push_back(new Sphere(pos, radius, colour));
}
