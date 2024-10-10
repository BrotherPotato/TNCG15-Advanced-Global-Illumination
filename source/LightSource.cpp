#include "./include/LightSource.h"

LightSource::LightSource(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) : 
	Triangle(v0, v1, v2, ColourRGB()) {
	
} 

void LightSource::emitPhotons() {

	// shoot em mfs
}

