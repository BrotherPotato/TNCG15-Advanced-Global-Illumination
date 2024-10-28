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
		_bounces = prevRay->getBounces() + 1;
	}
	
	_isShadowRay = isShadowRay;

	// jag tänker att när en ray skapas, kollar den direkt vart den ska sluta och studsa vidare
	// det blir typ en kedjereaktion(?)
	// asså om jag skapar en Ray(), ska jag kunna i nästa rad bara kalla på dess slutliga färg
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

	// går till sista rayen i ledet och tar dess färg
	Ray* ptr = this;
	while (ptr->_nextRay != nullptr) {

		// test för att se om man kan endast rita ut de belysta raysen... fungerar inte... ser inga "o" i konsolen :(((
		if (ptr->_nextRay->_isShadowRay && ptr->_nextRay->_lit) {
			//std::cout << "o";
			return ptr->_colour;
		}

		ptr = ptr->_nextRay;

	}
	//return ptr->_colour; // oavsett om pixeln är belyst eller ej, visa färgen... orealistiskt men vi får nåt iaf
	return ColourRGB(); // om pixeln inte är belyst, gör den svart... temporär lösning för att testa lambertian... fungerar inte, bilden blir svart
}

Ray::~Ray() {
	//delete delete?
}

// smitta av lite färg, mindre för varje bounce... tro mig mannen -- vansinne
void Ray::addColour(ColourRGB colour) {
	//_colour.setR((_colour.getR() + colour.getR()) / _bounces);
	//_colour.setG((_colour.getG() + colour.getG()) / _bounces);
	//_colour.setB((_colour.getB() + colour.getB()) / _bounces);
}

// lite osäker hur man vill strukturera intersection delarna
Object* Ray::rayIntersection(glm::vec3& collisionPoint) {

	// go through each object, check ray intersection
	Object* objectHit = nullptr; 
	double closestDist = 1000.0;
	double minDist = 1.0;
	glm::vec3 distance;
	for (Object* a : this->getScene()->getObjects()) {

		if (a->rayIntersection(this)) {

			distance = glm::vec3(getEndPos() - getStartPos());
			
			if (glm::length(distance) < closestDist && glm::length(distance) > minDist) {
				closestDist = glm::length(distance);
				//std::cout << closestDist << " ";
				objectHit = a;
			}
			//objectHit = a; // nu skickas bara den senaste intersecting object, men vi vill ha den närmaste
		}
	}
	if (objectHit != nullptr) objectHit->rayIntersection(this); // för att få tillbaka rätt endPos
	return objectHit;
}

ColourRGB Ray::castRay() { 


	// Russian Roulette

	double chanceToDie = (double)_bounces / (double)_timeToLive;
	double randNum = (rand() % 100 + 1) / 100.0;
	//std::cout << " " << randNum << ":" << chanceToDie << " ";

	if ( randNum < chanceToDie) {
		//std::cout << "dedby" << _bounces << "\n";
		return ColourRGB();
	}

	// #############################################################
	
	glm::vec3 collisionPoint;
	Object* collisionObject = this->rayIntersection(collisionPoint); // collisionPoint sent in as reference so we can change the value directly

	if (collisionObject == nullptr) {
		//std::cout << "miss\n";
		return ColourRGB();
	}
	// den kommer inte förbi den där if-statementet

	//std::cout << "Endpos: " << getEndPos().x << " : " << getEndPos().y << " : " << getEndPos().z << "\n";

	Material materialHit = collisionObject->getMaterial();
	glm::vec3 collisionNormal = collisionObject->getNormal();
	ColourRGB colour = materialHit.getColour();
	
	// dum lösning så att shadowrays inte skapar nya shadowrays
	if (_isShadowRay) {
		
		// shadow rays hittar aldrig light source :(((

		if (materialHit.getMaterialType() == Material::_LightSource) {
			std::cout << "yippee";
			_lit = true;
		}

		return ColourRGB();
	}

	switch (materialHit.getMaterialType())
	{
	case Material::_LambertianReflector:
		//std::cout << "D";

		_colour = materialHit.getColour();

		for(LightSource* l : this->getScene()->getLightSources()) {
			/*objectHit = l.rayIntersection(this)
				if (objectHit) {
					materialHit = a.getMaterial;
				}*/
				//std::cout << "!!SHADOW RAY!!";
			castShadowRay(l);
		}

		//return Ray::castShadowRay(); // either a forloop here or add one in casShadowRay and pass the whole array 


		// skapa random vec3, om den inte är i samma hemisphere som N, byt riktning på den
		glm::vec3 randomDirection{ rand(), rand(), rand() };
		glm::normalize(randomDirection);
		if (glm::dot(randomDirection, collisionNormal) < 0) randomDirection *= -1.0f;

		//Ray::reflect(collisionPoint, randomDirection);

		break;
	case Material::_MirrorReflection:
		//std::cout << "S";

		// perfect reflection
		glm::vec3 reflectionDirection = glm::reflect(_direction, collisionNormal);
		Ray::reflect(collisionPoint, reflectionDirection);

		break;
	case Material::_Transparent:
		//std::cout << "T";

		// random 50% chans
		if ((rand() % 100 + 1) / 100 > 0.5) {
			glm::vec3 reflectionDirection = glm::reflect(_direction, collisionNormal);
			Ray::reflect(collisionPoint, reflectionDirection);
		}
		else {
			// helt ärligt vet inte vad 0.5f gör
			glm::vec3 refractionDirection = glm::refract(_direction, collisionNormal, 0.5f);
			Ray::reflect(collisionPoint, refractionDirection);
		}

		break;
	case Material::_LightSource:
		//std::cout << "LS";

		// om rayen slår ner i en ljuskälla... inga reflections? bara färga av ljuskällans färg?
		_colour = materialHit.getColour();

		break;
	default:
		return ColourRGB();
	}
	
}

ColourRGB Ray::castShadowRay(const LightSource* light) { //maybe list of listsources and objects? pointer to scene istället kommer få kunna nå alla ljus 
	ColourRGB shadowColour = ColourRGB(1, 0, 0);
	
	glm::vec3 shadowRayDirection = light->getPosition() - this->getEndPos(); //venne om detta är korrekt lol
	Ray shadowRay(this->getScene(), this->getEndPos(), shadowRayDirection, shadowColour, this, true);

	Ray* ptrRay = &shadowRay;
	this->setNextRay(ptrRay);

	//std::cout << "LS: " << light->getPosition().x << ":" << light->getPosition().y << ":" << light->getPosition().z << "\n";
	//std::cout << "SR: " << shadowRay.getEndPos().x << ":" << shadowRay.getEndPos().y << ":" << shadowRay.getEndPos().z << "\n\n";

	double maxDistance = glm::length(light->getPosition() - _startPos); //define the maximum distance the shadow ray can travel

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

void Ray::reflect(glm::vec3 collisionPoint, glm::vec3 reflectionDirection) {

	// något sånt för att fixa nästa ray
	Ray* newRay = new Ray(this->getScene(), this->getEndPos(), reflectionDirection, _colour, this);
	this->setNextRay(newRay);

	

}