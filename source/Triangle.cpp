#include "./include/Triangle.h"
#include "glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL //beh�vs f�r gtx/normal
#include "gtx/normal.hpp" //cross(product) kanske normalize ocks�


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

double Triangle::calcArea() { //hintas p� i lecture 7 
	// SSS triangle area calculation 
	// glm::length() ger skal�ren/magnitued dvs euklidiska avst�ndet
	
	double a = glm::length(_v1 - _v0);
	double b = glm::length(_v2 - _v0);
	double c = glm::length(_v2 - _v1);

	double s = (a + b + c) / 2;

	return sqrt(s * (s - a) * (s - b) * (s - c));
}

//kanske d�ligt namn
bool Triangle::planeIntersection(Ray& ray) const {
	//ber�kna om ray:n �r p�v�g mot eller iv�g fr�n ytan. Lecture 4
	double dotProduct = glm::dot(_normal, ray.getDirection());

	if (dotProduct < 0) {
		return true;
	}
	else return false;
}

//Lecture 4
bool Triangle::rayIntersection(Ray& ray) const {
	//M�ller-Trumbore algorithm for triangles
	
	glm::vec3 T = ray.getStartPos() - _v0;
	glm::vec3 E1 = _v1 - _v0;
	glm::vec3 E2 = _v2 - _v0;
	glm::vec3 D = ray.getDirection();
	glm::vec3 P = glm::cross(D, E2);
	glm::vec3 Q = glm::cross(T, E1);

	//might need epsilon if bit flips tihii :))
	double dotPE1 = glm::dot(P, E1);
	double u = glm::dot(P, T) / dotPE1;
	double v = glm::dot(Q, D) / dotPE1;
	double t = glm::dot(Q, E2) / dotPE1;

	if (u < 0 || v < 0 || t < 0) return false; // n�r den hit, g�r den inte vidare

	// jag t�nker att man h�r kallar p� ray.reflect()
	// s� att ray f�r en ny startposition och direction, l�gger p� lite f�rg fr�n ytan

	// fr�n wikipedia, det �r kanske fel variabler
	glm::vec3 pointOfIntersection = glm::vec3(ray.getStartPos() + ray.getDirection());
	pointOfIntersection.x *= t;
	pointOfIntersection.y *= t;
	pointOfIntersection.z *= t;

	glm::vec3 reflectedDirection;
	
	ray.addColour(getMaterial().getColour());
	ray.reflect(pointOfIntersection, reflectedDirection);

	return true;
}



