#include "./include/CustomColor.h"

CustomColor::CustomColor(double R, double G, double B) {
	_R = std::max(std::min(R, 1.0), 0.0);
	_G = std::max(std::min(G, 1.0), 0.0);
	_B = std::max(std::min(B, 1.0), 0.0);
};

double CustomColor::getR() {
	return _R;
};

double CustomColor::getG() {
	return _G;
};

double CustomColor::getB() {
	return _B;
};

void CustomColor::setR(double R) {
	_R = R;
};

void CustomColor::setG(double G) {
	_G = G;
};

void CustomColor::setB(double B) {
	_B = B;
};