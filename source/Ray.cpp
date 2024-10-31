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
		_bounces = prevRay->_bounces + 1; // �ndra s� att den endast �kar p� lambertian surfaces
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

//ColourRGB Ray::getColour() {
//
//	// g�r till sista rayen i ledet och tar dess f�rg
//	Ray* ptr = this;
//
//	// n�r man kollar direkt p� ljusk�llan
//	if (ptr->_lit) return ptr->_colour;
//
//	// resterande rays
//	while (ptr != nullptr && ptr->_nextRay != nullptr) {
//		
//		if (ptr->_nextRay->_isShadowRay && ptr->_nextRay->_lit) return ptr->_colour;
//		ptr = ptr->_nextRay;
//
//		// n�r man kollar direkt p� ljusk�llan
//		if (ptr->_lit) return ptr->_colour;
//	}
//	
//	return ColourRGB(); 
//}

Ray::~Ray() {
	Ray* current = this;
	// make sure no shadow rays are pointing to a deleted object
	while (current->_nextRay) {
		Ray* next = current->_nextRay;
		current->_nextRay = nullptr;
		next->_prevRay = nullptr;
		//delete current;
		current = next;
	}
	
}

float Ray::oldCalcIntensity() { //hit a lightsource
	Ray* ptr = this; 
	float length = 0.0;
	float finalLength = 0.0;

	glm::vec3 startPoint;
	glm::vec3 endPoint;
	glm::vec3 direction;
	
	//read access violation here but I dont know why
	while (ptr) { // goes from lightsource to camera
		startPoint = ptr->getStartPos();
		endPoint = ptr->getEndPos(); //lightsource
		direction = glm::vec3(endPoint - startPoint);
		length = glm::length(direction);
		finalLength += length;

		if (length < 1.0) length += 1; //if very very close

		if (ptr->_prevRay) {
			ptr = ptr->_prevRay;
		}
		else {
			break;
		}
	}
	finalLength = finalLength * finalLength;
	
	//std::cout << "skibidi: " << ptr->_intensity << "dididid " << finalLength << "asdasdasd " << (ptr->_intensity / finalLength) << "\n";

	return glm::clamp((ptr->_intensity / finalLength), 0.0, 1.0);
}

float Ray::calcIntensity() const {
	glm::vec3 startPoint = getStartPos();
	glm::vec3 endPoint = getEndPos(); //lightsource
	glm::vec3 direction = glm::vec3(endPoint - startPoint);
	float length = glm::length(direction);
	float finalLength = length * length;
	return (_intensity / finalLength);				//glm::clamp((_intensity / finalLength), 0.0, 1.0);
}

ColourRGB Ray::sumColours() {

	Ray* ptr = this;
	ColourRGB colourSum = ColourRGB();
	//bool isLit = false;
	int counter = 1;
	// step all the way through 
	while (ptr != nullptr) {

		colourSum.addColour(ptr->_colour.divideColour(counter));
		
		//if (ptr->_lit) { // ptr->_nextRay->_isShadowRay && 
		//
		//	isLit = ptr->_lit;
		//	//return ptr->getColour();
		//}
		if (ptr->_nextRay) {
			ptr = ptr->_nextRay;	
			counter++;
		}
		else {
			break;
		}
	}
	// divide by the last rays number of bounces, reflective objects do not add to the number of bounces since they just pass the radiance over
	colourSum.divideColour(counter);

	return colourSum;
	

	//if (counter != 0 && ptr) {
	//
	//	
	//	//std::cout << "hoo hooo";
	//	//run intensity 
	//	float pixelIntensity = ptr->calcIntensity();
	//	//std::cout << "pixelIntensity: " << pixelIntensity;
	//	colourSum.calcFinalIntenisty(pixelIntensity);
	//	return colourSum;
	//}
	//
	//return ColourRGB();
}

// lite os�ker hur man vill strukturera intersection delarna
Object* Ray::rayIntersection() {


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
	
	double PI = 3.14159265358979323846;
	float randAzimuth;
	float randInclination;
	float redefAzimuth;

	// #############################################################
	
	//glm::vec3 collisionPoint;
	Object* collisionObject = this->rayIntersection(); // collisionPoint sent in as reference so we can change the value directly

	if (collisionObject == nullptr) {
		return ColourRGB();
	}
	// den kommer inte f�rbi den d�r if-statementet

	Material materialHit = collisionObject->getMaterial();
	glm::vec3 collisionNormal = collisionObject->getNormal(this);
	ColourRGB colour = materialHit.getColour();
	ColourRGB shadowRayLightContribution = ColourRGB();
	
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

		_colour.addColour(colourFromBounce);

		// Russian Roulette, anv�nds f�r Lambertian studs eller shadowray
		
		// lec 9 slide 8

		randAzimuth = 2.0f * PI * yi;
		randInclination = glm::acos(glm::sqrt(1 - yi));

		

		redefAzimuth = randAzimuth / _ps;
		

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

			Ray::reflect(randomDirectionGlobal);
			
		}
		else {
			
		}
		// regardless of termination or not, we send x shadow rays to each light source
		
		for (int i = 0; i < _shadowRaysPerRay; i++)
		{
			for (LightSource* l : this->getScene()->getLightSources()) {
				shadowRayLightContribution.addColour(castShadowRay(l));
			}
		}
		//std::cout << "Before: " << shadowRayLightContribution.getR();
		shadowRayLightContribution.divideColour(_shadowRaysPerRay * std::size(getScene()->getLightSources()));
		//std::cout << "After: " << shadowRayLightContribution.getR() << std::endl;
		_colour.componentMult(shadowRayLightContribution);

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
	


	//glm::vec3 shadowRayDirection = light->getPosition() - this->getEndPos(); //venne om detta �r korrekt lol
	//Ray* shadowRay = new Ray(this->getScene(), this->getEndPos(), shadowRayDirection, ColourRGB(), this, true);
	//
	////Ray* ptrRay = &shadowRay;
	//this->setNextRay(shadowRay);
	//
	//return ColourRGB();


	glm::vec3 shadowRayDirection = light->getRandomPosition() - this->getEndPos();
	Ray* shadowRay = new Ray(this->getScene(), this->getEndPos(), shadowRayDirection, ColourRGB(), nullptr, true);
	// _lit is true if the shadow ray hit the lightsource
	if (shadowRay->_lit) {
		//std::cout << "HIT";
		double intensity = shadowRay->calcIntensity();
		delete shadowRay;
		return ColourRGB(intensity);
	}
	
	delete shadowRay;
	return ColourRGB();


}

void Ray::reflect(glm::vec3 reflectionDirection) {

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
	reflect(Do);
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
	reflect(Dref);

}