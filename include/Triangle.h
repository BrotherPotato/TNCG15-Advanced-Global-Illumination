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

	bool rayIntersection(Ray& ray) const;
	bool planeIntersection(Ray& ray) const;

	glm::vec3 getNormal() const;

	ColourRGB getColour() const;

	Material getMaterial() const override;


	bool intersect(Ray& ray) const;

private:
	glm::vec3 _v0, _v1, _v2, _normal;
	//ColourRGB _colour{ 0,0,0 };
	Material _ObjectMaterial;
};

// points