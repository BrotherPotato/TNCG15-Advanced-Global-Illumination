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

ColourRGB Ray::pixelRadiance() {

	// Computing the radiance flow to the eye

	Ray* ptr = this;

	// Gå till sista rayen i ledet.
	while (ptr != nullptr) {
		if (ptr->_nextRay) ptr = ptr->_nextRay;
		else break;
	}
	if (ptr->_objectHit == nullptr) return ColourRGB();

	// You start at the end of the ray path. 
	// It must be on a diffuse (Lambertian) reflector or the light source.
	// The last importance ray becomes the first radiance ray.

	if (ptr->_objectHit->getMaterial().getMaterialType() == Material::_LightSource) {

		// If the endpoint is on a light source, we feed 𝐿𝑒 = (1.0, 1.0, 1.0) of the light source into the ray.
		// If the end point is on the light source, you give it the radiance RGB of the light source.
		ptr->_radiance = ptr->_objectHit->getMaterial().getColour(); 
	} 
	else if (ptr->_objectHit->getMaterial().getMaterialType() == Material::_LambertianReflector) {

		// If the endpoint is on a Lambertian reflector, we compute the direct light and feed this 𝐿𝐷(lecture 7) into the ray.
		// If it is on a diffuse reflector, you use the estimator for the direct light (lecture 7) to get the radiance values for the first radiance ray.
		ptr->_radiance = ptr->_directLight;
	}

	ColourRGB surfaceColour;
	ColourRGB directLight;

	// Gå tillbaka mot ögat.
	while (ptr->_prevRay != nullptr) {

		if (ptr->_prevRay->_objectHit->getMaterial().getMaterialType() == Material::_Transparent ||
			ptr->_prevRay->_objectHit->getMaterial().getMaterialType() == Material::_MirrorReflection) {

			// If it is a mirror or a transparent object (rays have a pointer to the surface), we copy the radiance into it.
			// If it is on a mirror or transparent surface, you copy the radiance RGB of the first radiance ray into the second.
			ptr->_prevRay->_radiance = ptr->_radiance;
		}
		else if (ptr->_prevRay->_objectHit->getMaterial().getMaterialType() == Material::_LambertianReflector) {

			// [Lecture 9]
			// If it is a Lambertian surface, we compute the direct light 𝐿𝐷. 
			// We multiply the radiance of the incoming ray and the surface color componentwise (access through the surface pointer).
			// Add the result to 𝐿𝐷 and copy it into the outgoing radiance ray

			// [Summary]
			// If the surface is a diffuse (Lambertian) reflector, 
			// You multiply the ratio of the importance of the first radiance ray to the second to the radiance of the first importance ray. [???????????????]
			// The color radio is the surface color. The BRDF is already absorbed into the random numbers.
			// You compute direct light (lecture 7) of the intersection point (taking into account the normal and BRDF) 
			// and add the result to the radiance of the second radiance ray

			surfaceColour = ptr->_prevRay->_objectHit->getMaterial().getColour();
			directLight = ptr->_prevRay->_directLight;

			surfaceColour.componentMult(ptr->_radiance);
			directLight.addColour(surfaceColour);

			ptr->_prevRay->_radiance = directLight;
		}

		// You repeat this until you reach the pixel. 
		// You copy the radiance into the pixel radiance and proceed with the next ray path.

		if (ptr->_prevRay != nullptr) ptr = ptr->_prevRay;
		else break;
	}

	return ptr->_radiance;
}

ColourRGB Ray::sumColours() {

	Ray* ptr = this;
	ColourRGB colourSum = ColourRGB();
	ColourRGB col;
	int counter = 0;
	
	// Gå till sista rayen i ledet.
	while (ptr != nullptr) {

		ptr->_colour.mix2Colours(ptr->_directLight);
		ptr->_colour.componentMult(ptr->_directLight);
		if (ptr->_bounces != 0) ptr->_colour.divideColour(ptr->_bounces);
		colourSum.addColour(ptr->_colour);

		if (ptr->_nextRay) ptr = ptr->_nextRay;
		else break;
	}

	counter = ptr->_bounces;
	if (counter != 0) {
		colourSum.divideColour(counter);
	}

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
	_objectHit = collisionObject;

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

	float R = _n1 / _n2;
	float Omega = glm::acos(glm::dot(glm::normalize(collisionNormal), -glm::normalize(_direction)));
	float R0_Schlicks = glm::pow(((_n1 - _n2) / (_n1 + _n2)), 2.0f);
	float R_Omega_Schlicks = R0_Schlicks + ((1 - R0_Schlicks) * glm::pow(1 - glm::cos(Omega), 5.0f)); 

	float rho = materialHit.getReflectance();

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
		

		// FÄRGLÄGG

		_colour.componentMult(colour);
		_importance = _colour;
		_directLight = shadowRayLightContribution;
		//_colour.componentMult(shadowRayLightContribution);
		

		// STUDSA VIDARE 

		randAzimuth = 2.0f * PI * yi;
		randInclination = glm::acos(glm::sqrt(1 - yi));
		redefAzimuth = randAzimuth / rho;

		// (2pi * yi) / rho <= 2pi		yi / rho <= 1		yi <= rho

		// Russian Roulette
		if (_bounces == 1 || yi <= rho) { // Kan inte dö på första intersectionen
			// to cartesian
			float randomX = glm::cos(redefAzimuth) * glm::sin(randInclination);
			float randomY = glm::sin(redefAzimuth) * glm::sin(randInclination);
			float randomZ = glm::cos(randInclination);

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
		_directLight = materialHit.getColour();

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