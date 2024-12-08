#pragma once

// prev, next ray
// origin, direction,

#include "glm.hpp"
#include <iostream>

//#include "./include/Scene.h"
//#include "./include/ColourRGB.h"
//#include "./include/LightSource.h"
#include "./include/Scene.h"
#include "./include/Material.h"
//#include "./include/LightSource.h"

#include <random>


class Scene;
class Object;
class LightSource;

class Ray
{
public:
	Ray(Scene* scene, glm::vec3 start, glm::vec3 direction, ColourRGB colour = ColourRGB(), Ray* prevRay = nullptr, bool isShadowRay = false);
	~Ray();

	Object* rayIntersection();
	
	ColourRGB castRay();
	ColourRGB castShadowRay(LightSource* light);


	//glm::vec3 bounce();

	void setNextRay(Ray* nextRay);

	glm::vec3 getDirection() const;
	glm::vec3 getStartPos() const;
	glm::vec3 getEndPos() const;
	void setEndpos(glm::vec3 pos) { _endPos = pos; };
	int getBounces() const;
	Scene* getScene() const;
	
	//ColourRGB getColour();

	float calcIntensity(LightSource* light) const;
	float oldCalcIntensity();
	ColourRGB sumColours();

	const glm::mat3 toLocalCoord(glm::vec3 normal) {
		//const glm::vec3 Z{ normal };
		//const glm::vec3 X = glm::normalize(_direction - glm::dot(_direction, Z) * Z);
		//const glm::vec3 Y = glm::cross(-X, Z);

		// lec 2 slide 13
		glm::vec3 x_L = glm::normalize(-_direction + glm::dot(normal, _direction) * normal);
		glm::vec3 z_L = glm::normalize(normal);

		glm::vec3 y_L = glm::cross(z_L, x_L);

		return glm::mat3{
			x_L.x, y_L.x, z_L.x,
			x_L.y, y_L.y, z_L.y,
			x_L.z, y_L.z, z_L.z,
		};

		/*return (glm::mat4{
		x_L.x, y_L.x, z_L.x, 0.f,
		x_L.y, y_L.y, z_L.y, 0.f,
		x_L.z, y_L.z, z_L.z, 0.f,
		0.f, 0.f, 0.f, 1.f } *
		glm::mat4{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		-collisionPoint.x, -collisionPoint.y, -collisionPoint.z, 1.f
			});*/
	}
		

	const glm::mat3 toGlobalCoord(glm::vec3 normal) {
		return glm::inverse(toLocalCoord(normal));
	}
	void mirrorReflect(glm::vec3 direction, glm::vec3 normal);
	void transparentRefract(glm::vec3 direction, glm::vec3 normal, float R, float Omega, float R_Omega_Schlicks);


	void createNewRay(glm::vec3 reflectionDirection);
	    
private:
	glm::vec3 _startPos;
	glm::vec3 _endPos; // se Triangle::rayIntersection f�r att hitta d�r endPos definieras
	glm::vec3 _direction;

	//doubly linked list
	Ray* _prevRay;
	Ray* _nextRay;

	// om vi vill kunnda d�da en ray efter x antal studsar
	int _timeToLive = 10; 

	//slidesen skriver att man ska skapa colourRGB s� prob. needs changing later ocks� double precision
	ColourRGB _colour = ColourRGB();

	std::shared_ptr<glm::vec3> _startingVertexPos;

	//anv�nder _ f�r att visa att det �r klassvariabel.


	int _bounces; // b�rja p� 1 annars d�r den, ??? f�r nu ett v�rde i Ray()

	Scene* _scene;

	bool _isShadowRay;
	bool _lit = false;

	static constexpr int _shadowRaysPerRay = 2;
	static constexpr float _airRefractiveIndex = 1.0f;
	static constexpr float _glassRefractiveIndex = 1.5f;

	float _n1 = 1.0f;
	float _n2 = 1.5f;

};

//Ray::~Ray()
//{
//}