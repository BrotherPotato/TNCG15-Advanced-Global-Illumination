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
		//std::cout << "oj";
		_bounces = prevRay->_bounces + 1; // �ndra s� att den endast �kar p� lambertian surfaces
		//std::cout << " bounces:" << _bounces;
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
	
	//return glm::clamp((ptr->_intensity / finalLength), 0.0, 1.0);
	return 0.0;
}

float Ray::calcIntensity(LightSource* light) const {
	glm::vec3 startPoint = getStartPos();
	glm::vec3 endPoint = getEndPos(); //lightsource
	glm::vec3 direction = glm::vec3(endPoint - startPoint);
	float length = glm::length(direction);
	float finalLength = length * length;
	double intensity = light->getIntensity() / finalLength;
	return intensity;				//glm::clamp((_intensity / finalLength), 0.0, 1.0);
}

ColourRGB Ray::sumColours() {

	Ray* ptr = this;
	ColourRGB colourSum = ColourRGB();
	int counter = 0;
	
	// Gå till sista rayen i ledet.
	while (ptr != nullptr) {

		ptr->_colour.componentMult(ptr->_intensity);
		colourSum.addColour(ptr->_colour);

		if (ptr->_nextRay) ptr = ptr->_nextRay;
		else break;
	}

	//counter = ptr->_bounces;
	//if (counter != 0) {
	//	colourSum.divideColour(counter);
	//}

	return colourSum;
}

// lite os�ker hur man vill strukturera intersection delarna
Object* Ray::rayIntersection() {


	// go through each object, check ray intersection
	Object* objectHit = nullptr; 
	double closestDist = 1000.0;
	float minDist = 0.01f;
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
		objectHit->rayIntersection(this); // f�r att f� tillbaka r�tt endPos
	}
	return objectHit;
}

ColourRGB Ray::castRay() { 

	if (_bounces > _timeToLive) return ColourRGB();

	std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution dis(0.0, 1.0);

	double yi = dis(gen);
	//double yi = (double)rand()/RAND_MAX;
	//std::cout << "\n" << yi;
	
	double PI = 3.14159265358979323846;
	float randAzimuth;
	float randInclination;
	float redefAzimuth;
	float redefInclination;

	// #############################################################
	
	//glm::vec3 collisionPoint;
	Object* collisionObject = this->rayIntersection(); // collisionPoint sent in as reference so we can change the value directly

	if (collisionObject == nullptr) {
		return ColourRGB();
	}
	// den kommer inte f�rbi den d�r if-statementet

	_objectHit = collisionObject;
	Material materialHit = collisionObject->getMaterial();
	glm::vec3 collisionNormal = collisionObject->getNormal(this);
	ColourRGB colour = materialHit.getColour();
	ColourRGB shadowRayLightContribution = ColourRGB();
	
	// dum l�sning s� att shadowrays inte skapar nya shadowrays
	if (_isShadowRay) {

		// om den träffade ljus
		if (materialHit.getMaterialType() == Material::_LightSource) {

			_lit = true;
			return ColourRGB();
		}

		// om den inte träffade ljus
		_lit = false;
		return ColourRGB();
	}

	// #################################################################
	ColourRGB colourFromBounce = materialHit.getColour();
	float luminance = (0.2126 * colourFromBounce.getR()) + (0.7152 * colourFromBounce.getG()) + (0.0722 * colourFromBounce.getB());

	float R = _n1 / _n2;
	float Omega = glm::acos(glm::dot(glm::normalize(collisionNormal), -glm::normalize(_direction)));
	float R0_Schlicks = glm::pow(((_n1 - _n2) / (_n1 + _n2)), 2.0f);
	float R_Omega_Schlicks = R0_Schlicks + ((1 - R0_Schlicks) * glm::pow(1 - glm::cos(Omega), 5.0f)); 

	std::vector<ColourRGB> cols;

	switch (materialHit.getMaterialType())
	{
	case Material::_LambertianReflector:	

		// BERÄKNA BELYSNING

		for (int i = 0; i < _shadowRaysPerRay; i++)
		{
			for (LightSource* l : this->getScene()->getLightSources()) {
				shadowRayLightContribution.addColour(castShadowRay(l));
			}
		}
		shadowRayLightContribution.divideColour(_shadowRaysPerRay * std::size(getScene()->getLightSources()));
		_intensity = shadowRayLightContribution.getR();

		// FÄRGLÄGG

		_colour.componentMult(colourFromBounce);
		//_colour.componentMult(shadowRayLightContribution);
		

		// STUDSA VIDARE 

		randAzimuth = 2.0f * PI * yi;
		randInclination = glm::acos(glm::sqrt(1 - yi));
		redefInclination = randInclination / (materialHit.getReflectance());
		redefAzimuth = randAzimuth / (materialHit.getReflectance());

		// (2pi * yi) / rho <= 2pi		yi / rho <= 1		yi <= rho

		// Russian Roulette
		if (redefInclination <= 2.0 * PI) {
			// to cartesian
			const float randomX = glm::cos(redefInclination) * glm::sin(randAzimuth);
			const float randomY = glm::sin(redefInclination) * glm::sin(randAzimuth);
			const float randomZ = glm::cos(randAzimuth);
			glm::vec3 randomDirectionLocal = glm::vec3(randomX, randomY, randomZ);
			glm::vec3 randomDirectionGlobal = toGlobalCoord(collisionNormal) * randomDirectionLocal;
			Ray::createNewRay(randomDirectionGlobal);
		}
		

		break;
	case Material::_MirrorReflection:
		//std::cout << "S ";

		_bounces--; // reflections dont count
		mirrorReflect(_direction, collisionNormal);

		break;
	case Material::_Transparent:
		//std::cout << "T ";

		_bounces--; // refractions dont count
		transparentRefract(_direction, collisionNormal, R, Omega, R_Omega_Schlicks);

		break;
	case Material::_LightSource:
		//std::cout << "LS ";

		_colour = materialHit.getColour();
		_intensity = materialHit.getColour().getR();

		break;
	default:
		return ColourRGB();
	}
	return _colour;
}

ColourRGB Ray::castShadowRay(LightSource* light) { 

	glm::vec3 shadowRayDirection = light->getRandomPosition() - this->getEndPos();
	Ray* shadowRay = new Ray(this->getScene(), this->getEndPos(), shadowRayDirection, ColourRGB(), nullptr, true);

	// _lit is true if the shadow ray hit the lightsource
	if (shadowRay->_lit) {
		double intensity = shadowRay->calcIntensity(light);
		delete shadowRay;
		//std::cout << "\nIntensity = " << intensity;
		return ColourRGB(intensity);
	}
	
	delete shadowRay;
	return ColourRGB();
}

void Ray::createNewRay(glm::vec3 reflectionDirection) {

	Ray* newRay = new Ray(this->getScene(), this->getEndPos(), reflectionDirection, _colour, this, false);
	this->setNextRay(newRay);
}

void Ray::mirrorReflect(glm::vec3 direction, glm::vec3 normal) {
	direction = -direction;

	// Lecture 5, Mirror Reflection
	glm::vec3 Drefl = direction - (2.0f * glm::dot(direction, normal) * normal);
	createNewRay(-Drefl);
}

void Ray::transparentRefract(glm::vec3 direction, glm::vec3 normal, float R, float Omega, float R_Omega_Schlicks) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis(0.0, 1.0);
	double randNum = dis(gen);

	direction = -direction;

	// Lecture 5, Transparent Refraction
	float k = (1.0 - pow(R, 2.0) * pow((1.0 - glm::dot(normal, direction)), 2.0));
	// Lecture 9, slide 15
	
	
	if (glm::sin(Omega) * R <= 1) {

		if (randNum < R_Omega_Schlicks) { // BRDF

			// left case reflection
			mirrorReflect(-direction, -normal);
		}
		else {
			// left case refraction
			glm::vec3 Drefr = (R * direction) + (normal * (-R * glm::dot(normal, direction) - sqrt(k)));
			std::swap(_n1, _n2); // vi går igenom mediet, alltså byts n1 och n2
			createNewRay(Drefr);
		}
	}
	else {
		//std::cout << "YIPPR";
		mirrorReflect(-direction, -normal);
	}
}