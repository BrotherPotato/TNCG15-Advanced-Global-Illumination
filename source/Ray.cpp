#include "./include/Ray.h"


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColourRGB colour) {
	_startPos = start;
	_direction = direction;
	_colour = colour;

	// jag tänker att när en ray skapas, kollar den direkt vart den ska sluta och studsa vidare
	// det blir typ en kedjereaktion(?)
	// asså om jag skapar en Ray(), ska jag kunna i nästa rad bara kalla på dess slutliga färg

}

glm::vec3 Ray::getDirection() const{
	return _direction;
}
glm::vec3 Ray::getStartPos() const {
	return _startPos;
}
glm::vec3 Ray::getEndPos() const {
	return _endPos;
}

Ray::~Ray()
{
	//delete delete?
}

// smitta av lite färg, mindre för varje bounce... tro mig mannen -- vansinne
void Ray::addColour(ColourRGB colour) {
	_colour.setR((_colour.getR() + colour.getR()) /bounces);
	_colour.setG((_colour.getG() + colour.getG()) / bounces);
	_colour.setB((_colour.getB() + colour.getB()) / bounces);
}

ColourRGB Ray::castShadowRay(const LightSource& light) { //maybe list of listsources and objects?
	ColourRGB shadowColour = ColourRGB(0, 0, 0);
	
	glm::vec3 shadowRayDirection = glm::normalize(light.getPosition() - _startPos); //venne om detta är korrekt lol
	Ray shadowRay(this->getEndPos(), shadowRayDirection, shadowColour );

	double maxDistance = glm::length(light.getPosition() - _startPos); //define the maximum distance the shadow ray can travel

	//for each object in the scene
	//if the shadow ray intersects with an object
	//snodde detta. Hitrecord är bara en struct som håller info om vad som träffades. 
	//HitRecord shadowHit;
	//if (sceneIntersection(shadowRay, shadowHit)) {
	//	// If the hit is closer than the light source, the point is in shadow
	//	if (shadowHit.t < maxDistance) {
	//		return true; // There is an object between the hit point and the light
	//	}
	//}
	




	return shadowColour;
}

void Ray::reflect(glm::vec3 start, glm::vec3 direction) {

	// gör nån check här ifall den ens ska studsa, eller om den bara dör på plats via Russian Roulette

	bounces++;
	_startPos = start;
	_direction = direction;

	// basically flyttar på rayen
	// pixlarna kommer fortfarande veta vilka rays som tillhör varje pixel

}