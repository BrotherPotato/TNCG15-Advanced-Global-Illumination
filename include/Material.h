#pragma once

#include "./include/ColourRGB.h"

class Material {
public:



private:
	ColourRGB _ObjectColour;
	// anv�nda normal f�r att best�mma n1 och n2 vid _Transparent
	enum _MaterialType { _LambertianReflector, _MirrorReflection, _Transparent };


};