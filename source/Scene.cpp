#include "./include/Scene.h"

Scene::Scene(){

}

void Scene::createTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, Material& mat) {

	Triangle tri(v0, v1, v2, mat);
	_Objects.push_back(new Triangle(tri));

}

void Scene::createBox(glm::vec3& pos, double width, double length, double height, Material& material) {

	width /= 2;
	length /= 2;
	height /= 2;

	// alla h�rn
	glm::vec3 p0(pos.x - width, pos.y - length, pos.z - height);
	glm::vec3 p1(pos.x + width, pos.y - length, pos.z - height);
	glm::vec3 p2(pos.x - width, pos.y + length, pos.z - height);
	glm::vec3 p3(pos.x + width, pos.y + length, pos.z - height);
	glm::vec3 p4(pos.x - width, pos.y - length, pos.z + height);
	glm::vec3 p5(pos.x + width, pos.y - length, pos.z + height);
	glm::vec3 p6(pos.x - width, pos.y + length, pos.z + height);
	glm::vec3 p7(pos.x + width, pos.y + length, pos.z + height);

	// alla trianglar
	Triangle t0(p0, p3, p1, material);
	Triangle t1(p0, p2, p3, material);
	Triangle t2(p1, p4, p0, material);
	Triangle t3(p1, p5, p4, material);
	Triangle t4(p4, p2, p0, material);
	Triangle t5(p4, p6, p2, material);
	Triangle t6(p1, p3, p7, material);
	Triangle t7(p1, p7, p5, material);
	Triangle t8(p7, p2, p6, material);
	Triangle t9(p7, p3, p2, material);
	Triangle t10(p4, p5, p7, material);
	Triangle t11(p4, p7, p6, material);

	// l�gg till i listan
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

void Scene::createTetrahedron(glm::vec3& pos, double size, Material& material) {
	float halfSize = size / 2.0f;

	// Calculate the vertices
	glm::vec3 p0 = glm::vec3(pos.x - halfSize, pos.y, pos.z - halfSize); //Back
	glm::vec3 p1 = glm::vec3(pos.x + halfSize, pos.y + halfSize, pos.z - halfSize); //Left
	glm::vec3 p2 = glm::vec3(pos.x + halfSize, pos.y - halfSize, pos.z - halfSize); //Right
	glm::vec3 p3 = glm::vec3(pos.x, pos.y, pos.z + halfSize); //Top
	_Objects.push_back(new Triangle(p0, p1, p2, material));//bottom
	_Objects.push_back(new Triangle(p0, p2, p3, material)); //right
	_Objects.push_back(new Triangle(p1, p3, p2, material)); //back
	_Objects.push_back(new Triangle(p0, p3, p1, material)); //left
}

void Scene::createPlane(glm::vec3& posBotLeft, glm::vec3& posTopRight, Material& material) {
	// z �r upp, skiss finns p� whiteboard v�nster om COORDSYSTEWM
	glm::vec3 p0(posBotLeft);
	glm::vec3 p1(posTopRight.x, posTopRight.y, posBotLeft.z);
	glm::vec3 p2(posBotLeft.x, posBotLeft.y, posTopRight.z);
	glm::vec3 p3(posTopRight);

	Triangle t0(p0, p3, p1, material);
	Triangle t1(p0, p2, p3, material);

	_Objects.push_back(new Triangle(t0));
	_Objects.push_back(new Triangle(t1));
}

void Scene::createSphere(glm::vec3& pos, double radius, Material& material) {
	_Objects.push_back(new Sphere(pos, radius, material));
}

void Scene::createLightSource(glm::vec3& posBotLeft, glm::vec3& posTopRight) {
	// z �r upp, skiss finns p� whiteboard v�nster om COORDSYSTEWM
	glm::vec3 p0(posBotLeft);
	glm::vec3 p1(posTopRight.x, posTopRight.y, posBotLeft.z);
	glm::vec3 p2(posBotLeft.x, posBotLeft.y, posTopRight.z);
	glm::vec3 p3(posTopRight);

	LightSource t0(p0, p3, p1, ColourRGB(1));
	LightSource t1(p0, p2, p3, ColourRGB(1));

	_LightSources.push_back(new LightSource(t0));
	_LightSources.push_back(new LightSource(t1));

	_Objects.push_back(new LightSource(t0));
	_Objects.push_back(new LightSource(t1));
}

void Scene::createLightSourceTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, ColourRGB colour, float intensity) {
	LightSource tri(v0, v1, v2, colour, intensity);
	_LightSources.push_back(new LightSource(tri));
	_Objects.push_back(new LightSource(tri));
}

std::vector<Object*>& Scene::getOALS() {

	std::vector<Object*> objs = _Objects;

	for (LightSource* l : _LightSources) {
		
		objs.push_back(l);
	}

	return objs;

}