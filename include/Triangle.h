#pragma once

#include "glm.hpp"

#include "./include/Object.h"



#include "./include/Material.h" //included in object

#include "./include/Ray.h"

class ColourRGB;
class Material;

// �ndra color till material sen
class Triangle : public Object
{
public:
	//Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const ColourRGB& colour);
	Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const Material& material);
	//~Triangle();
	void calcNormal();
	double calcArea();

	bool rayIntersection(Ray* ray) override;
	bool planeIntersection(Ray& ray) const;

	glm::vec3 getNormal(Ray* ray) const override;

	ColourRGB getColour() const;

	Material getMaterial() const override;


	bool intersect(Ray& ray) const;

private:
	glm::vec3 _v0, _v1, _v2, _normal;
	//ColourRGB _colour{ 0,0,0 };
	Material _ObjectMaterial;
};

//____________________________NEW CLASS________________________________//

class LightSource : public Triangle { // light ska ha en triangöe inte ärva
public:
	LightSource(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

	glm::vec3 getPosition() const {
		return _pos;
	}

	double getIntensity() {
		return _intensity;
	}

	bool rayIntersection(Ray* ray) override;

	void emitPhotons();
private:

	glm::vec3 _v0, _v1, _v2, _normal;
	ColourRGB _lightColour{ 1, 1 ,1 }; //vit default
	double _intensity = 1.0f;
	glm::vec3 _pos; 

	//glm::vec3 _v0, _v1, _v2, _normal;
	//Material _ObjectMaterial = Material::_LightSource;

};

// points