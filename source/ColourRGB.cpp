#include "./include/ColourRGB.h"

ColourRGB::ColourRGB(double R, double G, double B) {
	_R = std::max(std::min(R, 1.0), 0.0);
	_G = std::max(std::min(G, 1.0), 0.0);
	_B = std::max(std::min(B, 1.0), 0.0);
};

double ColourRGB::getR() {
	return _R;
};

double ColourRGB::getG() {
	return _G;
};

double ColourRGB::getB() {
	return _B;
};

void ColourRGB::setR(double R) {
	_R = std::max(std::min(R, 1.0), 0.0);
};

void ColourRGB::setG(double G) {
	_G = std::max(std::min(G, 1.0), 0.0);
};

void ColourRGB::setB(double B) {
	_B = std::max(std::min(B, 1.0), 0.0);
};