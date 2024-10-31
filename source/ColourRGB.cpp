#include "./include/ColourRGB.h"
#include <iostream>

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
	//_R = std::max(std::min(R, 1.0), 0.0);
	_R = R;
};

void ColourRGB::setG(double G) {
	//_G = std::max(std::min(G, 1.0), 0.0);
	_G = G;
};

void ColourRGB::setB(double B) {
	//_B = std::max(std::min(B, 1.0), 0.0);
	_B = B;
};

ColourRGB ColourRGB::divideColour(int amountOfSamples) {
	ColourRGB temp;
	temp.setR(getR() / amountOfSamples);
	temp.setG(getG() / amountOfSamples);
	temp.setB(getB() / amountOfSamples);

	setR(getR() / amountOfSamples);
	setG(getG() / amountOfSamples);
	setB(getB() / amountOfSamples);

	return temp;
}

ColourRGB ColourRGB::calcFinalIntenisty(float intensity) {
	ColourRGB temp;
	temp.setR(glm::clamp(getR() * intensity, 0.0, 1.0));
	temp.setG(glm::clamp(getG() * intensity, 0.0, 1.0));
	temp.setB(glm::clamp(getB() * intensity, 0.0, 1.0));

	setR(glm::clamp(getR() * intensity, 0.0, 1.0));
	setG(glm::clamp(getG() * intensity, 0.0, 1.0));
	setB(glm::clamp(getB() * intensity, 0.0, 1.0));

	

	return temp;
}

void ColourRGB::addColour(ColourRGB newColour) {
	setR(getR() + newColour.getR());
	setG(getG() + newColour.getG());
	setB(getB() + newColour.getB());
}