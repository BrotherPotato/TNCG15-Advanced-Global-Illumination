#pragma once

#include "./include/ColourRGB.h"

class Material {
public:
	// anv�nda normal f�r att best�mma n1 och n2 vid _Transparent
	enum MaterialType { _LambertianReflector, _MirrorReflection, _Transparent, _LightSource }; // Lightsource kanske inte beh�vs

	Material(MaterialType material = _LambertianReflector, ColourRGB colour = ColourRGB());

	MaterialType getMaterialType() const;

	ColourRGB getColour() const;

private:
	ColourRGB _ObjectColour;
	MaterialType _ObjectMaterial;
};