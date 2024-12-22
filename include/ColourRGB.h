#pragma once

//#include "algorithm"
#include "glm.hpp"
#include "vector"
// ColourRGB går mellan 0 och 1
class ColourRGB {
public:
	ColourRGB(double intensity = 0);
	ColourRGB(double R, double G, double B);

	~ColourRGB() = default;

	double getR();

	double getG();

	double getB();

	void setR(double R);

	void setG(double G);

	void setB(double B);

	ColourRGB divideColour(int amountOfSamples);
	ColourRGB componentMult(ColourRGB otherColour);
	ColourRGB calcFinalIntenisty(float intensity);
	

	// blandar färger så att alla raysperpixel kan klumpa samman till en slutfärg per pixel
	void addColour(ColourRGB newColour);

	ColourRGB mixColours(std::vector<ColourRGB> colours);

private:
	double _R, _G, _B;
};