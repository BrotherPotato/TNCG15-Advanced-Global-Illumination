#pragma once

#include "./include/ColourRGB.h"

class Material {
public:
	// använda normal för att bestämma n1 och n2 vid _Transparent
	enum MaterialType { _LambertianReflector, _MirrorReflection, _Transparent, _LightSource }; // Lightsource kanske inte behövs

	Material(MaterialType material = _LambertianReflector, ColourRGB colour = ColourRGB());

	MaterialType getMaterialType() const;

	ColourRGB getColour() const;

private:
	ColourRGB _ObjectColour;
	MaterialType _ObjectMaterial;
};