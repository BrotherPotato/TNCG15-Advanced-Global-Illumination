#pragma once

#include "./include/ColourRGB.h"

class Material {
public:
	// anv�nda normal f�r att best�mma n1 och n2 vid _Transparent
	enum MaterialType { _LambertianReflector, _MirrorReflection, _Transparent, _LightSource }; // Lightsource kanske inte beh�vs

	Material(MaterialType material = _LambertianReflector, ColourRGB colour = ColourRGB(), float reflectivity = 0.01f);

	MaterialType getMaterialType() const;

	ColourRGB getColour() const;
	float getReflectivity() { return _reflectivity; };

private:
	ColourRGB _ObjectColour;
	MaterialType _ObjectMaterial;
	float _reflectivity;

};