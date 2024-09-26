#include "./include/Triangle.h"
#include "glm.hpp"
#include "gtx/normal.hpp" //cross(product)


Triangle::Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& colour) :
_v0(v0), _v1(v0), _v2(v0), _colour(colour){
	calcNormal();
}

void Triangle::calcNormal() {
	
	glm::vec3 u = _v1 - _v0;
	glm::vec3 v = _v2 - _v0;

	_normal = glm::normalize(glm::cross(u, v));

}