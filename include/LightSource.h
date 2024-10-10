#pragma once

#include "glm.hpp"

class LightSource : Triangle {

	LightSource(glm::vec3 pos);

	void emitPhotons();

};