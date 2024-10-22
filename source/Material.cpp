#include "./include/Material.h"
#include "glm.hpp"



Material::Material(MaterialType material, ColourRGB colour) {
	_ObjectMaterial = material;
	_ObjectColour = colour;
};
// galen syntax jag vet
Material::MaterialType Material::getMaterialType() const {
	return _ObjectMaterial;
}

ColourRGB Material::getColour() const {
	return _ObjectColour;
}


