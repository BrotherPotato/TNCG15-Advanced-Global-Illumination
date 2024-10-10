#pragma once

#include "./include/ColourRGB.h"

class Material {
public:
	// anv�nda normal f�r att best�mma n1 och n2 vid _Transparent
	enum MaterialType { _LambertianReflector, _MirrorReflection, _Transparent, _LightSource };

	Material(MaterialType material = _LambertianReflector, ColourRGB colour = ColourRGB());

	MaterialType getMaterial();

	ColourRGB getColour();

private:
	ColourRGB _ObjectColour;
	MaterialType _ObjectMaterial;
};