#pragma once

#include "glm.hpp"

#include "./include/Object.h"



#include "./include/Material.h" //included in object

#include "./include/Ray.h"

#include <random>

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
	LightSource(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float intensity = 1.0f);

	glm::vec3 getPosition() const {
		return _pos;
	}
	// generate a random point on the triangle
	glm::vec3 getRandomPosition() const {

		// go to local coordinate system
		glm::vec3 E1 = _v1 - _v0;
		glm::vec3 E2 = _v2 - _v0;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution dis(0.0, 1.0);
		// randomize two points s and t
		float s = dis(gen);
		float t = dis(gen);
		// check if the point is inside the triangle
		bool insideTriangle = s + t <= 1;

		//std::cout << "\ns = " << s << "\nt = " << t << "\n s+t = " << s+t;

		glm::vec3 randomPoint;

		if (!insideTriangle) {
			s = 1 - s;
			t = 1 - t;
		}
		//std::cout << "\ns = " << s << "\nt = " << t << "\n s+t = " << s+t << "\n";

		randomPoint = (s * E1) + (t * E2);

		// to world
		return (randomPoint + _v0);

	}

	double getIntensity() const {
		return _intensity;
	}

	bool rayIntersection(Ray* ray) override; // fixa med normal

	void emitPhotons();
private:

	glm::vec3 _v0, _v1, _v2, _normal;
	ColourRGB _lightColour{ 1, 1 ,1 }; //vit default
	double _intensity;
	glm::vec3 _pos; 

	//glm::vec3 _v0, _v1, _v2, _normal;
	//Material _ObjectMaterial = Material::_LightSource;

};

// points