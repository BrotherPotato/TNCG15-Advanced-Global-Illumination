#include "./include/Ray.h"


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColourRGB colour) {
	_startPos = start;
	_direction = direction;
	_colour = colour;

	// jag t�nker att n�r en ray skapas, kollar den direkt vart den ska sluta och studsa vidare
	// det blir typ en kedjereaktion(?)
	// ass� om jag skapar en Ray(), ska jag kunna i n�sta rad bara kalla p� dess slutliga f�rg

}

glm::vec3 Ray::getDirection() const{
	return _direction;
}
glm::vec3 Ray::getStartPos() const {
	return _startPos;
}

Ray::~Ray()
{
	//delete delete?
}

// smitta av lite f�rg, mindre f�r varje bounce... tro mig mannen -- vansinne
void Ray::addColour(ColourRGB colour) {
	_colour.setR((_colour.getR() + colour.getR()) /bounces);
	_colour.setG((_colour.getG() + colour.getG()) / bounces);
	_colour.setB((_colour.getB() + colour.getB()) / bounces);
}


void Ray::reflect(glm::vec3 start, glm::vec3 direction) {

	// g�r n�n check h�r ifall den ens ska studsa, eller om den bara d�r p� plats via Russian Roulette

	bounces++;
	_startPos = start;
	_direction = direction;

	// basically flyttar p� rayen
	// pixlarna kommer fortfarande veta vilka rays som tillh�r varje pixel

}