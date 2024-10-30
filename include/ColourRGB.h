#pragma once

#include "algorithm"
// ColourRGB g�r mellan 0 och 1
class ColourRGB {
public:
	ColourRGB(double R = 0, double G = 0, double B = 0);

	~ColourRGB() = default;

	double getR();

	double getG();

	double getB();

	void setR(double R);

	void setG(double G);

	void setB(double B);

	ColourRGB divideColour(int amountOfSamples);
	ColourRGB calcFinalIntenisty(float intensity);
	

	// blandar f�rger s� att alla raysperpixel kan klumpa samman till en slutf�rg per pixel
	void mixColours(ColourRGB newColour);

private:
	double _R, _G, _B;
};