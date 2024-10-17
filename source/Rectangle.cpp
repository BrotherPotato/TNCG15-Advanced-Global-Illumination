#include "./include/Rectangle.h"
#include "./include/Triangle.h"
#include "glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL //beh�vs f�r gtx/normal
#include "gtx/normal.hpp" //cross(product) kanske normalize ocks�


Rectangle::Rectangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const Material& material) :
_v0(v0), _v1(v1), _v2(v2), _v3(v3), _ObjectMaterial(material) {
	calcNormal();
}

glm::vec3 Rectangle::getNormal() const {
	return _normal;
}

ColourRGB Rectangle::getColour() const {
	return _ObjectMaterial.getColour();
};

Material Rectangle::getMaterial() const {
	return _ObjectMaterial;
};
 
void Rectangle::calcNormal() { //Should work for rectangle as well

	/*
   v0-----------v3
    |           |
    |           |
   v1-----------v2
	*/
	
	glm::vec3 u = _v1 - _v0;
	glm::vec3 v = _v2 - _v0;

	_normal = glm::normalize(glm::cross(u, v)); 
}

double Rectangle::calcArea() { //hintas p� i lecture 7 
	// glm::length() ger skal�ren/magnitued dvs euklidiska avst�ndet
		/*
   v0-----------v3
	|           |
	|           |
   v1-----------v2
	*/

	double a = glm::length(_v1 - _v0); //height
	double b = glm::length(_v3 - _v0); //width
	
	return a*b;
}

//kanske d�ligt namn
bool Rectangle::planeIntersection(Ray& ray) const {
	//ber�kna om ray:n �r p�v�g mot eller iv�g fr�n ytan. Lecture 4
	double dotProduct = glm::dot(_normal, ray.getDirection());

	if (dotProduct < 0) {
		return true;
	}
	else return false;
}

//Lecture 4
bool Rectangle::rayIntersection(Ray& ray) const {
	//M�ller-Trumbore algorithm for Rectangle
	/*
   v0-----------v3
	|           |
	|           |
   v1-----------v2
	*/

	//MAKE THE TRINGLE AND MAKE IT WORK FOR RECTINGLE EZPZ
	Triangle t1(_v0, _v1, _v2, _ObjectMaterial);
	Triangle t2(_v2, _v3, _v0, _ObjectMaterial);

	if (t1.rayIntersection(ray) || t2.rayIntersection(ray)) {
		return true;
	}
	else return false;

}



