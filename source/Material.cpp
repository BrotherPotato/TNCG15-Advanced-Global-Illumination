#include "./include/Material.h"
#include "glm.hpp"



Material::Material(MaterialType material = _LambertianReflector, ColourRGB colour = ColourRGB()) {
	_ObjectMaterial = material;
	_ObjectColour = colour;
};
// galen syntax jag vet
Material::MaterialType Material::getMaterial() {
	return _ObjectMaterial;
}

ColourRGB Material::getColour() {
	return _ObjectColour;
}


