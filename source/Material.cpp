#include "./include/Material.h"
#include "glm.hpp"



Material::Material(MaterialType material, ColourRGB colour, float reflectivity) {
	_ObjectMaterial = material;
	_ObjectColour = colour;
	_reflectivity = reflectivity;
};
// galen syntax jag vet
Material::MaterialType Material::getMaterialType() const {
	return _ObjectMaterial;
}

ColourRGB Material::getColour() const {
	return _ObjectColour;
}


