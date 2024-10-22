#include "./include/Ray.h"

// prev and next do not need to be initialized, default nullptr
Ray::Ray(Scene* scene, glm::vec3 start, glm::vec3 direction, ColourRGB colour, Ray* prevRay) {
	_startPos = start;
	_direction = direction;
	_colour = colour;
	_prevRay = prevRay;
	_scene = scene;
	if (prevRay == nullptr) {
		_bounces = 0;
	}
	else {
		_bounces = prevRay->getBounces() + 1;
	}
	
	// jag t�nker att n�r en ray skapas, kollar den direkt vart den ska sluta och studsa vidare
	// det blir typ en kedjereaktion(?)
	// ass� om jag skapar en Ray(), ska jag kunna i n�sta rad bara kalla p� dess slutliga f�rg
	castRay();
}

void Ray::setNextRay(Ray* nextRay) {
	_nextRay = nextRay;
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

int Ray::getBounces() const {
	return _bounces;
}

Scene* Ray::getScene() const {
	return _scene;
}

ColourRGB Ray::getColour() const {
	return _colour; 
}

Ray::~Ray() {
	//delete delete?
}

// smitta av lite f�rg, mindre f�r varje bounce... tro mig mannen -- vansinne
void Ray::addColour(ColourRGB colour) {
	_colour.setR((_colour.getR() + colour.getR()) / _bounces);
	_colour.setG((_colour.getG() + colour.getG()) / _bounces);
	_colour.setB((_colour.getB() + colour.getB()) / _bounces);
}

// lite os�ker hur man vill strukturera intersection delarna
Triangle* Ray::rayIntersection(glm::vec3& collisionPoint) {
	// go through each object, check ray intersection
	Triangle* objectHit;
	for (Object* a : this->getScene()->getObjects()) {
		/*if (a->rayIntersection(this)) {
			Triangle = a;
		}*/
		collisionPoint = glm::vec3();
	}
	return objectHit;
}

ColourRGB Ray::castRay() { 
	// g�r n�n check h�r ifall den ens ska studsa, eller om den bara d�r p� plats via Russian Roulette


	glm::vec3 collisionPoint;

	Triangle* collisionTriangle = this->rayIntersection(collisionPoint); // collisionPoint sent in as reference so we can change the value directly

	Material materialHit = collisionTriangle->getMaterial();

	glm::vec3 collisionNormal = collisionTriangle->getNormal();

	ColourRGB colour = materialHit.getColour();
	

	switch (materialHit.getMaterialType())
	{
	case Material::_LambertianReflector:
		
		for(LightSource* l : this->getScene()->getLightSources()) {
			/*objectHit = l.rayIntersection(this)
				if (objectHit) {
					materialHit = a.getMaterial;
				}*/
			castShadowRay(l);
		}

		//return Ray::castShadowRay(); // either a forloop here or add one in casShadowRay and pass the whole array 
		break;
	case Material::_MirrorReflection:

		
		Ray::reflect(this->getDirection(), collisionPoint);

		break;
	case Material::_Transparent:

		break;
	case Material::_LightSource:

		break;
	default:
		return ColourRGB();
	}
	
}

ColourRGB Ray::castShadowRay(const LightSource* light) { //maybe list of listsources and objects? pointer to scene ist�llet kommer f� kunna n� alla ljus 
	ColourRGB shadowColour = ColourRGB(0, 0, 0);
	
	glm::vec3 shadowRayDirection = glm::normalize(light->getPosition() - _startPos); //venne om detta �r korrekt lol
	Ray shadowRay(this->getScene(), this->getEndPos(), shadowRayDirection, shadowColour );

	double maxDistance = glm::length(light->getPosition() - _startPos); //define the maximum distance the shadow ray can travel

	//for each object in the scene
	//if the shadow ray intersects with an object
	//snodde detta. Hitrecord �r bara en struct som h�ller info om vad som tr�ffades. 
	//HitRecord shadowHit;
	//if (sceneIntersection(shadowRay, shadowHit)) {
	//	// If the hit is closer than the light source, the point is in shadow
	//	if (shadowHit.t < maxDistance) {
	//		return true; // There is an object between the hit point and the light
	//	}
	//}
	

	return shadowColour;
}

void Ray::reflect(glm::vec3 rayInDirection, glm::vec3 collisionPoint) {

	
	/*_startPos = start;
	_direction = direction;*/
	glm::vec3 newDirection;

	// n�got s�nt f�r att fixa n�sta ray
	Ray* newRay = new Ray(this->getScene(), collisionPoint, newDirection, ColourRGB(), this);
	this->setNextRay(newRay);

	

}