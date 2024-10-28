#include "./include/Triangle.h"
#include "glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL //behövs för gtx/normal
#include "gtx/normal.hpp" //cross(product) kanske normalize också


Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const Material& material) :
_v0(v0), _v1(v1), _v2(v2), _ObjectMaterial(material){
	calcNormal();
}

glm::vec3 Triangle::getNormal() const {
	return _normal;
}

ColourRGB Triangle::getColour() const {
	return _ObjectMaterial.getColour();
};

Material Triangle::getMaterial() const {
	return _ObjectMaterial;
};

void Triangle::calcNormal() {
	
	glm::vec3 u = _v1 - _v0;
	glm::vec3 v = _v2 - _v0;

	_normal = glm::normalize(glm::cross(u, v));
}

double Triangle::calcArea() { //hintas på i lecture 7 
	// SSS triangle area calculation 
	// glm::length() ger skalären/magnitud dvs euklidiska avståndet
	
	double a = glm::length(_v1 - _v0);
	double b = glm::length(_v2 - _v0);
	double c = glm::length(_v2 - _v1);

	double s = (a + b + c) / 2;

	return sqrt(s * (s - a) * (s - b) * (s - c));
}

//kanske dåligt namn
bool Triangle::planeIntersection(Ray& ray) const {
	//beräkna om ray:n är påväg mot eller iväg från ytan. Lecture 4
	double dotProduct = glm::dot(_normal, ray.getDirection());

	if (dotProduct < 0) {
		return true;
	}
	else return false;
}

//Lecture 4
bool Triangle::rayIntersection(Ray* ray) const {
	//Möller-Trumbore algorithm for triangles
	
	glm::vec3 T = ray->getStartPos() - _v0;
	glm::vec3 E1 = _v1 - _v0;
	glm::vec3 E2 = _v2 - _v0;
	glm::vec3 D = ray->getDirection();
	glm::vec3 P = glm::cross(D, E2);
	glm::vec3 Q = glm::cross(T, E1);

	//might need epsilon if bit flips tihii :))
	double dotPE1 = glm::dot(P, E1);
	double u = glm::dot(P, T) / dotPE1;
	double v = glm::dot(Q, D) / dotPE1;
	double t = glm::dot(Q, E2) / dotPE1;

	if (u < 0 || u>1 || v < 0 || u+v>1 || t < 0) return false; // når den hit, går den inte vidare

	// om det finns en intersection, sätt endPoint på rayen

	glm::vec3 tDir = ray->getDirection();
	tDir.x *= t;
	tDir.y *= t;
	tDir.z *= t;
	glm::vec3 pointOfIntersection = ray->getStartPos() + tDir; // det blir inte rätt... kuben är på x=50 men den här ger alltid ett lågt x
	ray->setEndpos(pointOfIntersection);

	return true;
}

//____________________________NEW CLASS________________________________//
LightSource::LightSource(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) :
	Triangle(v0, v1, v2, Material(Material::_LightSource)) {

	_pos = glm::vec3( (v0.x + v1.x + v2.x)/3.0 , (v0.y + v1.y + v2.y) / 3.0, (v0.z + v1.z + v2.z) / 3.0);
}

void LightSource::emitPhotons() {

	// shoot em mfs
}


