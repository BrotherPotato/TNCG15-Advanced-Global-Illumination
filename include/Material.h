#pragma once

#include "./include/ColourRGB.h"

class Material {
public:
	// använda normal för att bestämma n1 och n2 vid _Transparent
	enum MaterialType { _LambertianReflector, _MirrorReflection, _Transparent, _LightSource }; // Lightsource kanske inte behövs

	Material(MaterialType material = _LambertianReflector, ColourRGB colour = ColourRGB(), float reflectance = 0.01f);

	MaterialType getMaterialType() const;

	ColourRGB getColour() const;
	float getReflectance() { return _reflectance; };

private:
	ColourRGB _ObjectColour;
	MaterialType _ObjectMaterial;
	float _reflectance;

};