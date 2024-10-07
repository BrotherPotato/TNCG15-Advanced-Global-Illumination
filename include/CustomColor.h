#pragma once

#include "algorithm"

class CustomColor {
public:
	CustomColor(double R, double G, double B);

	~CustomColor() = default;

	double getR();

	double getG();

	double getB();

	void setR(double R);

	void setG(double G);

	void setB(double B);

private:
	double _R, _G, _B;
};