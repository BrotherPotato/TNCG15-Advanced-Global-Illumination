#pragma once

#include "./include/ColourRGB.h"

class Material {
public:



private:
	ColourRGB _ObjectColour;
	// använda normal för att bestämma n1 och n2 vid _Transparent
	enum _MaterialType { _LambertianReflector, _MirrorReflection, _Transparent };


};