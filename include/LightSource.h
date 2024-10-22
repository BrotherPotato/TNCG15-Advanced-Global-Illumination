#pragma once

#include "glm.hpp"
#include "Triangle.h"
#include "Material.h"


class LightSource : Triangle {
public:
	LightSource(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

	glm::vec3 getPosition() const{
		return _pos;
	}

	double getIntensity() {
		return _intensity;
	}


	void emitPhotons();
private:

	ColourRGB _lightColour{ 1, 1 ,1 }; //vit default
	double _intensity = 1.0f;
	glm::vec3 _pos{ 0,0,0 }; //vet inte om denna behövs

	//glm::vec3 _v0, _v1, _v2, _normal;
	//Material _ObjectMaterial = Material::_LightSource;

};