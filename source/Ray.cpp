#include "./include/Ray.h"

// prev and next do not need to be initialized, default nullptr
Ray::Ray(Scene* scene, glm::vec3 start, glm::vec3 direction, ColourRGB colour, Ray* prevRay, bool isShadowRay) {
	_startPos = start;
	_direction = glm::normalize(direction);
	_colour = colour;
	_prevRay = prevRay;
	_scene = scene;
	_nextRay = nullptr;

	if (prevRay == nullptr) {
		_bounces = 1;
	}
	else {
		_bounces = prevRay->getBounces() + 1; // �ndra s� att den endast �kar p� lambertian surfaces
	}
	
	_isShadowRay = isShadowRay;

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

ColourRGB Ray::getColour() {

	// g�r till sista rayen i ledet och tar dess f�rg
	Ray* ptr = this;

	// n�r man kollar direkt p� ljusk�llan
	if (ptr->_lit) return ptr->_colour;

	// resterande rays
	while (ptr != nullptr && ptr->_nextRay != nullptr) {
		
		if (ptr->_nextRay->_isShadowRay && ptr->_nextRay->_lit) return ptr->_colour;
		ptr = ptr->_nextRay;

		// n�r man kollar direkt p� ljusk�llan
		if (ptr->_lit) return ptr->_colour;
	}
	
	return ColourRGB(); 
}

Ray::~Ray() {
	//delete delete?
}

// smitta av lite f�rg, mindre f�r varje bounce... tro mig mannen -- vansinne
void Ray::addColour(ColourRGB colour) {
	//_colour.setR((_colour.getR() + colour.getR()) / _bounces);
	//_colour.setG((_colour.getG() + colour.getG()) / _bounces);
	//_colour.setB((_colour.getB() + colour.getB()) / _bounces);
}

ColourRGB Ray::sumColours() {
	Ray* ptr = this;
	ColourRGB colourSum = ColourRGB();
	bool isLit = false;
	int counter = 0;
	while (ptr->_nextRay != nullptr) {

		colourSum.mixColours(ptr->_colour);
		counter++;

		if (ptr->_nextRay->_isShadowRay && ptr->_nextRay->_lit) {

			isLit = ptr->_nextRay->_lit;
			//return ptr->getColour();
		}
		ptr = ptr->_nextRay;
	}

	if (isLit && counter != 0) {
		colourSum.divideColour(counter);
		return colourSum;
	}

	return ColourRGB();
}

// lite os�ker hur man vill strukturera intersection delarna
Object* Ray::rayIntersection(glm::vec3& collisionPoint) {

	// go through each object, check ray intersection
	Object* objectHit = nullptr; 
	double closestDist = 1000.0;
	double minDist = 0.001;
	glm::vec3 distance;

	// g�r igenom alla objects
	for (Object* a : this->getScene()->getObjects()) {

		if (a->rayIntersection(this)) {

			distance = glm::vec3(getEndPos() - getStartPos());
			
			if (glm::length(distance) < closestDist && glm::length(distance) > minDist) {
				closestDist = glm::length(distance);
				objectHit = a;
			}
		}
	}

	if (objectHit != nullptr) {
		//if (objectHit->getMaterial().getMaterialType() == Material::_LightSource) std::cout << "hooray!";
		objectHit->rayIntersection(this); // f�r att f� tillbaka r�tt endPos
	}

	return objectHit;
}

ColourRGB Ray::castRay() { 


	// Russian Roulette, anv�nds f�r Lambertian studs eller shadowray
	double chanceToDie = (double)_bounces / (double)_timeToLive;
	double randNum = (rand() % 100 + 1) / 100.0;
	bool ded = false;
	if (randNum < chanceToDie) ded = true;

	// #############################################################
	
	glm::vec3 collisionPoint;
	Object* collisionObject = this->rayIntersection(collisionPoint); // collisionPoint sent in as reference so we can change the value directly

	if (collisionObject == nullptr) {
		return ColourRGB();
	}
	// den kommer inte f�rbi den d�r if-statementet

	Material materialHit = collisionObject->getMaterial();
	glm::vec3 collisionNormal = collisionObject->getNormal(this);
	ColourRGB colour = materialHit.getColour();
	
	// dum l�sning s� att shadowrays inte skapar nya shadowrays
	if (_isShadowRay) {
		
		if (materialHit.getMaterialType() == Material::_LightSource) {

			_lit = true;
		}
		return ColourRGB(); // bara s� att den inte forts�tter till switch-case delen
	}

	// #################################################################

	ColourRGB colourFromBounce = materialHit.getColour();
	colourFromBounce = colourFromBounce.divideColour(_bounces);

	switch (materialHit.getMaterialType())
	{
	case Material::_LambertianReflector:
		//std::cout << "D ";

		
		//_colour = colourFromBounce;

		//_colour.setR((_colour.getR() + colourFromBounce.getR())/2.0);
		//_colour.setG((_colour.getG() + colourFromBounce.getG())/2.0);
		//_colour.setB((_colour.getB() + colourFromBounce.getB())/2.0);
		_colour.mixColours(colourFromBounce);

		// Russian Roulette
		if (ded) {

			for (LightSource* l : this->getScene()->getLightSources()) {
				castShadowRay(l);
			}
		}
		else {

			// skapa random vec3, om den inte �r i samma hemisphere som N, byt riktning p� den
			glm::vec3 randomDirection{ rand(), rand(), rand() };
			glm::normalize(randomDirection);
			if (glm::dot(randomDirection, collisionNormal) < 0) randomDirection *= -1.0f;
			Ray::reflect(collisionPoint, randomDirection);
		}
		

		break;
	case Material::_MirrorReflection:
		//std::cout << "S ";

		if (ded) return ColourRGB();

		// perfect reflection
		glm::vec3 reflectionDirection = glm::reflect(_direction, collisionNormal);
		Ray::reflect(collisionPoint, reflectionDirection);

		break;
	case Material::_Transparent:
		//std::cout << "T ";

		if (ded) return ColourRGB();

		// random 50% chans
		if (randNum > 0.5) {
			glm::vec3 reflectionDirection = glm::reflect(_direction, collisionNormal);
			Ray::reflect(collisionPoint, reflectionDirection);
		}
		else {
			// helt �rligt vet inte vad 0.5f g�r
			glm::vec3 refractionDirection = glm::refract(_direction, collisionNormal, 0.5f);
			Ray::reflect(collisionPoint, refractionDirection);
		}

		break;
	case Material::_LightSource:
		//std::cout << "LS ";

		if (ded) return ColourRGB();

		// om rayen sl�r ner i en ljusk�lla... inga reflections? bara f�rga av ljusk�llans f�rg?
		_colour = ColourRGB(1,1,1);
		_lit = true;

		break;
	default:
		return ColourRGB();
	}
	return _colour;
}

ColourRGB Ray::castShadowRay(const LightSource* light) { //maybe list of listsources and objects? pointer to scene ist�llet kommer f� kunna n� alla ljus 
	
	glm::vec3 shadowRayDirection = light->getPosition() - this->getEndPos(); //venne om detta �r korrekt lol
	Ray shadowRay(this->getScene(), this->getEndPos(), shadowRayDirection, ColourRGB(), this, true);

	Ray* ptrRay = &shadowRay;
	this->setNextRay(ptrRay);

	return ColourRGB();
}

void Ray::reflect(glm::vec3 collisionPoint, glm::vec3 reflectionDirection) {

	// n�got s�nt f�r att fixa n�sta ray
	Ray newRay = Ray(this->getScene(), this->getEndPos(), reflectionDirection, _colour, this);

	Ray* newRayPtr = &newRay;
	this->setNextRay(newRayPtr);

	

}