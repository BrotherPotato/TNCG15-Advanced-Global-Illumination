#pragma once

#include "algorithm"

class CustomColour {
public:
	CustomColour(double R = 0, double G = 0, double B = 0);

	~CustomColour() = default;

	double getR();

	double getG();

	double getB();

	void setR(double R);

	void setG(double G);

	void setB(double B);

private:
	double _R, _G, _B;
};