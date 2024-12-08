#include "./include/ColourRGB.h"
#include <iostream>


ColourRGB::ColourRGB(double intensity) {
	_R = glm::clamp(intensity, 0.0, 1.0);
	_G = glm::clamp(intensity, 0.0, 1.0);
	_B = glm::clamp(intensity, 0.0, 1.0);
}

ColourRGB::ColourRGB(double R, double G, double B) {
	_R = glm::clamp(R, 0.0, 1.0);
	_G = glm::clamp(G, 0.0, 1.0);
	_B = glm::clamp(B, 0.0, 1.0);
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

	float divisor = (float)amountOfSamples;

	temp.setR(getR() / divisor);
	temp.setG(getG() / divisor);
	temp.setB(getB() / divisor);

	setR(getR() / divisor);
	setG(getG() / divisor);
	setB(getB() / divisor);

	return temp;
}

ColourRGB ColourRGB::componentMult(ColourRGB otherColour) {
	ColourRGB temp;
	temp.setR(getR() * otherColour.getR());
	temp.setG(getG() * otherColour.getG());
	temp.setB(getB() * otherColour.getB());

	setR(getR() * otherColour.getR());
	setG(getG() * otherColour.getG());
	setB(getB() * otherColour.getB());

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

void ColourRGB::mixColour(ColourRGB newColour) {

	// Detta är det korrekta sättet att blanda två färger.
	// https://www.youtube.com/watch?v=LKnqECcg6Gw

	double R = getR() * 255.0;
	double G = getG() * 255.0;
	double B = getB() * 255.0;

	double nR = newColour.getR() * 255;
	double nG = newColour.getG() * 255;
	double nB = newColour.getB() * 255;

	R = sqrt((pow(R, 2.0) + pow(nR, 2.0)) / 2.0);
	G = sqrt((pow(G, 2.0) + pow(nG, 2.0)) / 2.0);
	B = sqrt((pow(B, 2.0) + pow(nB, 2.0)) / 2.0);

	R /= 255.0;
	G /= 255.0;
	B /= 255.0;

	setR(R);
	setG(G);
	setB(B);
}