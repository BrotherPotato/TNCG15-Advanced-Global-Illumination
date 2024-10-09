#include "./include/CustomColour.h"

CustomColour::CustomColour(double R, double G, double B) {
	_R = std::max(std::min(R, 1.0), 0.0);
	_G = std::max(std::min(G, 1.0), 0.0);
	_B = std::max(std::min(B, 1.0), 0.0);
};

double CustomColour::getR() {
	return _R;
};

double CustomColour::getG() {
	return _G;
};

double CustomColour::getB() {
	return _B;
};

void CustomColour::setR(double R) {
	_R = R;
};

void CustomColour::setG(double G) {
	_G = G;
};

void CustomColour::setB(double B) {
	_B = B;
};