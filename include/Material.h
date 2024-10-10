#pragma once

#include "./include/ColourRGB.h"

class Material {
public:
	// använda normal för att bestämma n1 och n2 vid _Transparent
	enum MaterialType { _LambertianReflector, _MirrorReflection, _Transparent, _LightSource };

	Material(MaterialType material = _LambertianReflector, ColourRGB colour = ColourRGB());

	MaterialType getMaterial() const;

	ColourRGB getColour() const;

private:
	ColourRGB _ObjectColour;
	MaterialType _ObjectMaterial;
};