#pragma once

#include "glm.hpp"

#include "Material.h"

class LightSource {
public:
	LightSource(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

	void emitPhotons();
private:
	glm::vec3 _v0, _v1, _v2, _normal;
	Material _ObjectMaterial = Material::_LightSource;

};