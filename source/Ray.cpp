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

float Ray::calcIntensity() { //hit a lightsource
	Ray* ptr = this; 
	ptr->_intensity = 1.0;
	float length = 0.0;
	float finalLength = 0.0;
	
	//read access violation here but I dont know why
	while (ptr) { // goes from lightsource to camera
		glm::vec3 startPoint = ptr->getStartPos();
		glm::vec3 endPoint = ptr->getEndPos(); //lightsource
		glm::vec3 direction = glm::vec3(endPoint - startPoint);
		length = glm::length(direction);
		finalLength += length;

		//length = length* length; // squared length

		if (length < 1.0) length += 1; //if very very close
		//ptr->_intensity = ptr->_intensity / length;

		if (ptr->_prevRay) {
			ptr = ptr->_prevRay;
			//if (ptr == nullptr) break;
		}
		else {
			break;
		}
		//std::cout << "\tlength: " << length << std::endl;

		//std::cout << "should be 1: "<< ptr->_intensity << "\nLength: " << length << "\t" << finalLength;
	}
	finalLength = finalLength * finalLength;
	if (!ptr->_prevRay && !ptr->_nextRay) {
		std::cout << " KYS ";
		return 1.0; // 1.0
	}
	//std::cout << "\nskibidi: " << ptr->_intensity / finalLength;

	return (ptr->_intensity / finalLength) ;
}

ColourRGB Ray::sumColours() {

	
	Ray* ptr = this;
	ColourRGB colourSum = ColourRGB();
	bool isLit = false;
	int counter = 0;
	while (ptr != nullptr && !isLit) {

		colourSum.mixColours(ptr->_colour);
		counter++;

		if (ptr->_lit) { // ptr->_nextRay->_isShadowRay && 

			isLit = ptr->_lit;
			//return ptr->getColour();
		}
		else {
			ptr = ptr->_nextRay;	
		}
	}

	if (isLit && counter != 0 && ptr) {

		
		//std::cout << "hoo hooo";
		//run intensity 
		float pixelIntensity = ptr->calcIntensity();
		colourSum.calcFinalIntenisty(pixelIntensity);
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

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis(0.0, 1.0);

	// Russian Roulette, anv�nds f�r Lambertian studs eller shadowray
	double chanceToDie = (double)_bounces / (double)_timeToLive;
	double randNum = dis(gen);
	bool ded = false;
	if (randNum < chanceToDie) ded = true;


	double yi = dis(gen);
	float Ps = 0.8f; // chance to survive
	double PI = 3.14159265358979323846;
	float randAzimuth;
	float randInclination;
	float redefAzimuth;

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

	bool insideObject = glm::dot(_direction, collisionNormal) < 0;
	float n1 = insideObject ? _glassRefractiveIndex : _airRefractiveIndex;
	float n2 = insideObject ? _airRefractiveIndex : _glassRefractiveIndex;
	float R = n1 / n2;

	float Omega = acos(glm::dot(_direction, collisionNormal));

	switch (materialHit.getMaterialType())
	{
	case Material::_LambertianReflector:

		//_colour = colourFromBounce;
		//_colour.setR((_colour.getR() + colourFromBounce.getR())/2.0);
		//_colour.setG((_colour.getG() + colourFromBounce.getG())/2.0);
		//_colour.setB((_colour.getB() + colourFromBounce.getB())/2.0);

		_colour.mixColours(colourFromBounce);

		// Russian Roulette, anv�nds f�r Lambertian studs eller shadowray
		
		// lec 9 slide 8

		randAzimuth = 2.0f * PI * yi;
		randInclination = glm::acos(glm::sqrt(1 - yi));

		

		redefAzimuth = randAzimuth / Ps;
		

		// Russian Roulette
		if (redefAzimuth <= 2.0f * PI) {
			// skapa random vec3, om den inte �r i samma hemisphere som N, byt riktning p� den
			/*glm::vec3 randomDirection{ dis(gen), dis(gen), dis(gen) };
			glm::normalize(randomDirection);
			if (glm::dot(randomDirection, collisionNormal) < 0) randomDirection *= -1.0f;*/

			// to cartesian
			const float randomX = glm::cos(redefAzimuth) * glm::sin(randInclination);
			const float randomY = glm::sin(redefAzimuth) * glm::sin(randInclination);
			const float randomZ = glm::cos(randInclination);

			glm::vec3 randomDirectionLocal = glm::vec3(randomX, randomY, randomZ);
			//glm::vec4 randomDirectionLocal = glm::vec4(randomX, randomY, randomZ, 1);


			glm::vec3 randomDirectionGlobal = toGlobalCoord(collisionNormal) * randomDirectionLocal;
			//glm::vec4 randomDirectionGlobal = toGlobalCoord(collisionNormal, collisionPoint) * randomDirectionLocal;

			Ray::reflect(collisionPoint, randomDirectionGlobal);
			
		}
		else {
			for (LightSource* l : this->getScene()->getLightSources()) {
				castShadowRay(l);
			}
		}

		break;
	case Material::_MirrorReflection:
		//std::cout << "S ";

		_bounces--; // g�r s� att f�rgerna inte m�rknas
		mirrorReflect(_direction, collisionNormal);

		break;
	case Material::_Transparent:
		//std::cout << "T ";

		_bounces--;
		
		// B�de reflection och refraction
		if (sin(Omega) * (R) <= 1) {

			// Antingen eller, f�r vi kan inte faktiskt ha b�da samtidigt.
			if (randNum > 1.0) {
				mirrorReflect(_direction, collisionNormal);
			}
			else {
				transparentRefract(_direction, collisionNormal, R);
			}
		}
		// Bara reflection
		else {
			transparentRefract(_direction, collisionNormal, R);
		}

		break;
	case Material::_LightSource:
		//std::cout << "LS ";

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
	Ray* shadowRay = new Ray(this->getScene(), this->getEndPos(), shadowRayDirection, ColourRGB(), this, true);

	//Ray* ptrRay = &shadowRay;
	this->setNextRay(shadowRay);

	return ColourRGB();
}

void Ray::reflect(glm::vec3 collisionPoint, glm::vec3 reflectionDirection) {

	// n�got s�nt f�r att fixa n�sta ray
	Ray* newRay = new Ray(this->getScene(), this->getEndPos(), reflectionDirection, _colour, this);

	//Ray* newRayPtr = &newRay;
	this->setNextRay(newRay);

	

}


void Ray::mirrorReflect(glm::vec3 direction, glm::vec3 normal) {

	// Lecture 5, Mirror Reflection
	glm::vec3 Di = glm::normalize(direction);
	glm::vec3 N = glm::normalize(normal);
	glm::vec3 Do = Di - (2.0f * glm::dot(Di, N) * N);
	reflect(getEndPos(), Do);
}

void Ray::transparentRefract(glm::vec3 direction, glm::vec3 normal, float R) {

	// Lecture 5, Transparent Refraction
	glm::vec3 Do = glm::normalize(direction);
	glm::vec3 N = glm::normalize(normal);

	float theSquare = 0.0f; // f�rhindra imagin�ra tal
	if ((1.0 - pow(R, 2.0) * pow((1.0 - glm::dot(N, Do)), 2.0)) > 0.0) {
		theSquare = sqrt(1.0 - (pow(R, 2.0) * pow((1.0 - glm::dot(N, Do)), 2.0)));
	}
	//std::cout << theSquare << "\n";

	glm::vec3 Dref = (R * Do) + (N * (-R * glm::dot(N, Do) - theSquare));
	reflect(getEndPos(), Dref);

}