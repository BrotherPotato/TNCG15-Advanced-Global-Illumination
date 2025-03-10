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


ColourRGB ColourRGB::mixColours(std::vector<ColourRGB> colours) {

	// Detta �r det korrekta s�ttet att blanda tv� (eller fler) f�rger.
	// https://www.youtube.com/watch?v=LKnqECcg6Gw

	double R = 0;
	double G = 0;
	double B = 0;
	
	for (int i = 0; i < colours.size(); i++) {

		R += pow(colours[i].getR() * 255.0, 2.0);
		G += pow(colours[i].getG() * 255.0, 2.0);
		B += pow(colours[i].getB() * 255.0, 2.0);
	}

	double n = colours.size();
	R = sqrt(R / n) / 255.0;
	G = sqrt(G / n) / 255.0;
	B = sqrt(B / n) / 255.0;

	return ColourRGB{R,G,B};
}

void ColourRGB::mix2Colours(ColourRGB secondCOlour) {

	std::vector<ColourRGB> cols;
	cols.push_back(*this);
	cols.push_back(secondCOlour);
	*this = ColourRGB().mixColours(cols);
}