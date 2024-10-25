#include "./include/Ray.h"

// prev and next do not need to be initialized, default nullptr
Ray::Ray(Scene* scene, glm::vec3 start, glm::vec3 direction, ColourRGB colour, Ray* prevRay) {
	_startPos = start;
	_direction = glm::normalize(direction);
	_colour = colour;
	_prevRay = prevRay;
	_scene = scene;
	if (prevRay == nullptr) {
		_bounces = 0;
	}
	else {
		_bounces = prevRay->getBounces() + 1;
	}
	
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

ColourRGB Ray::getColour() const {
	return _colour; 
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
	Object* objectHit = nullptr; //ksk memory leak då vi lämnar funktionen med en pointer till värdet i funktionen. 
	for (Object* a : this->getScene()->getObjects()) {

		// den kallar alltid på  Object::rayIntersection  som alltid returnar false, 
		// men vi vill ha  Triangle::rayIntersection  och  Sphere::rayIntersection
		// rekursiv funktion får programmet att crasha (Stack overflow) tror jag -- Magnus
		if (a->rayIntersection(this)) {
			objectHit = a;
		}
		collisionPoint = glm::vec3();
	}
	return objectHit;
}

ColourRGB Ray::castRay() { 

	// russian roulette
	double bounces = _bounces;
	double chanceToDie = bounces / _timeToLive;
	//rand körs en gång och håller värdet tills programmets slut. 
	if ((rand() % 100 + 1) / 100 < chanceToDie) {
		// den e dö

		std::cout << "ded\n";
		return ColourRGB();
	}
	if (bounces == 1) return ColourRGB(); //testing because stack over flow
	
	glm::vec3 collisionPoint;
	Object* collisionObject = this->rayIntersection(collisionPoint); // collisionPoint sent in as reference so we can change the value directly

	if (collisionObject == nullptr) {
		return ColourRGB();
	}

	// den kommer inte förbi den där if-statementet

	Material materialHit = collisionObject->getMaterial();
	glm::vec3 collisionNormal = collisionObject->getNormal();
	ColourRGB colour = materialHit.getColour();
	


	switch (materialHit.getMaterialType())
	{
	case Material::_LambertianReflector:
		
		for(LightSource* l : this->getScene()->getLightSources()) {
			/*objectHit = l.rayIntersection(this)
				if (objectHit) {
					materialHit = a.getMaterial;
				}*/
			std::cout << "Skibidi: Lambert reflect";
			castShadowRay(l);
		}

		//return Ray::castShadowRay(); // either a forloop here or add one in casShadowRay and pass the whole array 


		// skapa random vec3, om den inte är i samma hemisphere som N, byt riktning på den
		glm::vec3 randomDirection{ rand(), rand(), rand() };
		glm::normalize(randomDirection);
		if (glm::dot(randomDirection, collisionNormal) < 0) randomDirection *= -1.0f;

		Ray::reflect(collisionPoint, randomDirection);

		break;
	case Material::_MirrorReflection:

		// perfect reflection
		glm::vec3 reflectionDirection = glm::reflect(_direction, collisionNormal);
		Ray::reflect(collisionPoint, reflectionDirection);

		break;
	case Material::_Transparent:

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

		// om rayen slår ner i en ljuskälla... inga reflections? bara färga av ljuskällans färg?
		_colour = materialHit.getColour();

		break;
	default:
		return ColourRGB();
	}
	
}

ColourRGB Ray::castShadowRay(const LightSource* light) { //maybe list of listsources and objects? pointer to scene istället kommer få kunna nå alla ljus 
	ColourRGB shadowColour = ColourRGB(0, 0, 0);
	
	glm::vec3 shadowRayDirection = glm::normalize(light->getPosition() - _startPos); //venne om detta är korrekt lol
	Ray shadowRay(this->getScene(), this->getEndPos(), shadowRayDirection, shadowColour );

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
	Ray* newRay = new Ray(this->getScene(), collisionPoint, reflectionDirection, _colour, this);
	this->setNextRay(newRay);

	

}